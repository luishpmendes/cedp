#include "LagrangianHeuristicSolver1.hpp"
#include <cfloat>
#include <fstream>

/*
 * Constructs a new solver.
 *
 * @param instance  the new solver's instance.
 * @param timeLimit the new solver's time limit.
 * @param seed      the seed for the new solver's pseudo-random numbers generator.
 * @param N         the new solver's π updating parameter.
 */
LagrangianHeuristicSolver1::LagrangianHeuristicSolver1(
        const Instance & instance, unsigned int timeLimit, unsigned int seed, 
        unsigned int N) : CEDPSolver::CEDPSolver(instance, timeLimit, seed), 
    N(N) {}

/*
 * Constructs a new empty solver.
 */
LagrangianHeuristicSolver1::LagrangianHeuristicSolver1() : CEDPSolver::CEDPSolver() {}

/*
 * Solve the first Lagrangian relaxation subproblem with the current set of multipliers.
 *
 * @param dp     the map that stores the optimal value of the subproblems.
 * @param cTilde the Lagrangian costs.
 * @param eId    the id of the edge been considered.
 * @param dTilde the residual capacity of each district.
 *
 * @return the optimal value of the first Lagrangian relaxation subproblem 
 *         with the current set of multipliers.
 */
double LagrangianHeuristicSolver1::solveLagrangianRelaxationSubproblem1(
        std::map<std::pair<unsigned int, std::vector<double> >, 
        std::pair<unsigned int, double>> & dp, 
        const std::vector<std::vector<double> > & cTilde, unsigned int eId, 
        const std::vector<double> & dTilde) {
    if (CEDPSolver::areTerminationCriteriaMet()) {
        dp[std::make_pair(eId, dTilde)] = std::make_pair(this->instance.getM(), DBL_MAX);
        return DBL_MAX;
    }

    if (dp.find(std::make_pair(eId, dTilde)) != dp.end()) {
        return dp.at(std::make_pair(eId, dTilde)).second;
    }

    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        /* If ∃ j ∈ {1, ..., m} such that d^{~}_{j} < 0 */
        if (dTilde[j] < 0) {
            dp[std::make_pair(eId, dTilde)] = std::make_pair(this->instance.getM(), -DBL_MAX);
            return -DBL_MAX;
        }
    }

    if (eId == 0) {
        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            /* 
             * If eId = 0 && ∃ j ∈ {1, ..., m} such that d^{~}_{j} > 
             * min{D, (2(1+B)/m)∑_{e ∈ E}{d^{~}_{e}}} - (2(1-B)/m)∑_{e ∈ E}{d^{~}_{e}}
             */
            if (dTilde[j] > this->instance.getMaximumDemand() - 
                    this->instance.getMinimumDemand()) {
                dp[std::make_pair(eId, dTilde)] = std::make_pair(
                        this->instance.getM(), -DBL_MAX);
                return -DBL_MAX;
            }
        }

        /* 
         * If eId = 0 && ∀ j ∈ {1, ..., m} such that 0 ≤ d^{~}_{j} ≤ 
         * min{D, (2(1+B)/m)∑_{e ∈ E}{d^{~}_{e}}} - (2(1-B)/m)∑_{e ∈ E}{d^{~}_{e}}
         */
        dp[std::make_pair(eId, dTilde)] = std::make_pair(this->instance.getM(), 0.0);
        return 0.0;
    }

    /* Otherwise */
    double maxValue = -DBL_MAX;
    unsigned int j = this->instance.getM();

    for (unsigned int k = 0; k < this->instance.getM(); k++) {
        std::vector<double> dPrime (dTilde);
        dPrime[k] -= 2 * this->instance.getG().getEdgeById(eId).w;
        double value = this->solveLagrangianRelaxationSubproblem1(dp, cTilde, eId - 1, dPrime);

        if (value > -DBL_MAX) {
            value += cTilde[eId - 1][k];
        }

        if (maxValue < value) {
            maxValue = value;
            j = k;
        }
    }

    dp[std::make_pair(eId, dTilde)] = std::make_pair(j, maxValue);
    return maxValue;
}

/*
 * Solve the second Lagrangian relaxation subproblem with the current set of multipliers.
 *
 * @return the optimal value of the second Lagrangian relaxation subproblem 
 *         with the current set of multipliers.
 */
double LagrangianHeuristicSolver1::solveLagrangianRelaxationSubproblem2() {
    double dualBound2 = this->lambda2;

    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        dualBound2 += this->lambda1[j];
    }

    this->y = std::vector<std::vector<bool> > (this->instance.getLG().n(), 
            std::vector<bool> (this->instance.getM(), false));

    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);
            double aux = ((double) this->instance.getLG().n()) * 
                this->lambda3[eId - 1][j] - this->lambda1[j];

            if (aux > 0.0) {
                this->y[eId - 1][j] = true;
                dualBound2 += aux;
            } else {
                this->y[eId - 1][j] = false;
            }
        }
    }

    this->z = std::vector<std::vector<double> > (
            2 * this->instance.getGPrime().m(), std::vector<double> (
                this->instance.getM(), 0.0));

    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);
            unsigned int ePrimeEid = this->instance.getGPrime().getEdgeId(
                    this->instance.getEPrime(), e);

            if (e < this->instance.getEPrime()) {
                ePrimeEid += this->instance.getGPrime().m();
            }

            double aux = (this->lambda2 / ((double) this->instance.getLG().n())) 
                + this->lambda3[eId - 1][j] + this->lambda6[eId - 1][j];

            if (aux < 0.0) {
                this->z[ePrimeEid - 1][j] = this->instance.getLG().n();
            } else {
                this->z[ePrimeEid - 1][j] = 0.0;
            }

            dualBound2 -= this->z[ePrimeEid - 1][j] * aux;
        }
    }

    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);
            unsigned int eEprimeId = this->instance.getGPrime().getEdgeId(e, 
                    this->instance.getEPrime());

            if (e > this->instance.getEPrime()) {
                eEprimeId += this->instance.getGPrime().m();
            }

            double aux = this->lambda6[eId - 1][j];

            if (aux > 0.0) {
                this->z[eEprimeId - 1][j] = this->instance.getLG().n();
            } else {
                this->z[eEprimeId - 1][j] = 0.0;
            }

            dualBound2 += this->z[eEprimeId - 1][j] * aux;
        }
    }

    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            for (const Edge & ef : this->instance.getLG().getIncidentEdges(e)) {
                unsigned int efId = this->instance.getLG().getEdgeId(ef);
                Vertex f = ef.u;

                if (f == e) {
                    f = ef.v;
                }

                double aux = this->lambda6[eId - 1][j] - this->lambda4[efId - 1][j];

                if (e > f) {
                    efId += this->instance.getGPrime().m();
                }

                if (aux > 0.0) {
                    this->z[efId - 1][j] = this->instance.getLG().n();
                } else {
                    this->z[efId - 1][j] = 0.0;
                }

                dualBound2 += this->z[efId - 1][j] * aux;
            }
        }
    }

    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            for (const Edge & ef : this->instance.getLG().getIncidentEdges(e)) {
                unsigned int efId = this->instance.getLG().getEdgeId(ef);
                Vertex f = ef.u;

                if (f == e) {
                    f = ef.v;
                }

                double aux = this->lambda5[efId - 1][j] + this->lambda6[eId - 1][j];

                if (f > e) {
                    efId += this->instance.getGPrime().m();
                }

                if (aux < 0.0) {
                    this->z[efId - 1][j] = this->instance.getLG().n();
                } else {
                    this->z[efId - 1][j] = 0.0;
                }

                dualBound2 -= this->z[efId - 1][j] * aux;
            }
        }
    }

    return dualBound2;
}

/*
 * Solve the Lagrangian relaxation subproblem with the current set of multipliers.
 *
 * @return the optimal value of the Lagrangian relaxation subproblem with the 
 *         current set of multipliers.
 */
double LagrangianHeuristicSolver1::solveLagrangianRelaxationSubproblem() {
    std::vector<std::vector<double> > cTilde (this->instance.getLG().n(), 
            std::vector<double> (this->instance.getM(), 0.0));
    std::vector<double> dTilde (this->instance.getM(), this->instance.getMaximumDemand());

    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            cTilde[eId - 1][j] = this->instance.getC(eId, j) + this->lambda6[eId - 1][j];

            double aux = 0.0;

            for (const Edge & ef : this->instance.getLG().getIncidentEdges(e)) {
                unsigned int efId = this->instance.getLG().getEdgeId(ef);

                aux += this->lambda4[efId - 1][j] + this->lambda5[efId - 1][j];
            }

            cTilde[eId - 1][j] += ((double) this->instance.getLG().n()) * aux;
        }
    }

    std::map<std::pair<unsigned int, std::vector<double> >, 
        std::pair<unsigned int, double> > dp;
    double dualBound1 = this->solveLagrangianRelaxationSubproblem1(dp, cTilde, 
            this->instance.getG().getMaxEid(), dTilde);

    if (!CEDPSolver::areTerminationCriteriaMet()) {
        this->currentSolution = Solution(this->instance);

        for (unsigned int eId = this->instance.getG().getMaxEid(); eId > 0; eId--) {
            unsigned int j = dp.at(std::make_pair(eId, dTilde)).first;

            this->currentSolution.setEdgeDistrict(eId, j);

            dTilde[j] -= 2 * this->instance.getG().getEdgeById(eId).w;
        }
    }

    this->x = this->currentSolution.getX();

    double dualBound2 = this->solveLagrangianRelaxationSubproblem2();

    if (dualBound1 <= -DBL_MAX) {
        return dualBound1;
    }

    return dualBound1 + dualBound2;
}

/*
 * Define subgradients for the relaxed constraints.
 */
void LagrangianHeuristicSolver1::defineSubgradients() {
    this->subgradient1 = std::vector<double> (this->instance.getM());

    /* ∀ j ∈ {1, ..., m} */
    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        /* subgradient^{1}_{j} = 1.0 - ∑_{e ∈ U}{y_{{e', e}, j}} */
        this->subgradient1[j] = 1.0;

        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            this->subgradient1[j] -= this->y[eId - 1][j];
        }
    }

    /* subgradient^{2} = 1.0 - ∑_{j = 1}^{m}{∑_{e ∈ U}{z_{e', e, j}/|U|}} */
    this->subgradient2 = 1.0;

    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int ePrimeEid = this->instance.getGPrime().getEdgeId(
                    this->instance.getEPrime(), e);

            if (e < this->instance.getEPrime()) {
                ePrimeEid += this->instance.getGPrime().m();
            }

            this->subgradient2 -= this->z[ePrimeEid - 1][j] / 
                ((double) this->instance.getLG().n());
        }
    }

    this->subgradient3 = std::vector<std::vector<double> > (
            this->instance.getLG().n(), std::vector<double> (
                this->instance.getM()));

    /* ∀ j ∈ {1, ..., m} */
    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        /* ∀ e ∈ U */
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);
            unsigned int ePrimeEid = this->instance.getGPrime().getEdgeId(
                    this->instance.getEPrime(), e);

            if (e < this->instance.getEPrime()) {
                ePrimeEid += this->instance.getGPrime().m();
            }

            /* subgradient^{3}_{e, j} = |U|y_{{e', e}, j} - z_{e', e, j} */
            this->subgradient3[eId - 1][j] = 
                ((double) this->instance.getLG().n()) * this->y[eId - 1][j] - 
                this->z[ePrimeEid - 1][j];

            /* if λ^{3}_{e, j} = 0.0 && subgradient^{3}_{e, j} < 0 */
            if (fabs(this->lambda3[eId - 1][j]) < 1E-5 && 
                    this->subgradient3[eId - 1][j] < 0.0) {
                /* subgradient^{3}_{e, j} = 0.0 */
                this->subgradient3[eId - 1][j] = 0.0;
            }
        }
    }

    this->subgradient4 = std::vector<std::vector<double> > (
            this->instance.getLG().m(), std::vector<double> (
                this->instance.getM()));

    /* ∀ j ∈ {1, ..., m} */
    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        /* ∀ e ∈ U */
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            /* ∀ {e, f} ∈ σ_{L(G)}({e}) */
            for (const Edge & ef : this->instance.getLG().getIncidentEdges(e)) {
                unsigned int efId = this->instance.getLG().getEdgeId(ef);
                Vertex f = ef.u;

                if (f == e) {
                    f = ef.v;
                }

                /* subgradient^{4}_{{e, f}, j} = |U|x_{e, j} - z_{e, f, j} */
                this->subgradient4[efId - 1][j] = 
                    ((double) this->instance.getLG().n()) * this->x[eId - 1][j];

                if (e < f) {
                    this->subgradient4[efId - 1][j] -= this->z[efId - 1][j];
                } else {
                    this->subgradient4[efId - 1][j] -= 
                        this->z[this->instance.getGPrime().m() + efId - 1][j];
                }

                /* if λ^{4}_{{e, f}, j} = 0.0 && subgradient^{4}_{{e, f}, j} < 0 */
                if (fabs(this->lambda4[efId - 1][j]) < 1E-5 && 
                        this->subgradient4[efId - 1][j] < 0.0) {
                    /* subgradient^{4}_{{e, f}, j} = 0.0 */
                    this->subgradient4[efId - 1][j] = 0.0;
                }
            }
        }
    }

    this->subgradient5 = std::vector<std::vector<double> > (
            this->instance.getLG().m(), std::vector<double> (
                this->instance.getM()));

    /* ∀ j ∈ {1, ..., m} */
    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        /* ∀ e ∈ U */
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            /* ∀ {e, f} ∈ σ_{L(G)}({e}) */
            for (const Edge & ef : this->instance.getLG().getIncidentEdges(e)) {
                unsigned int efId = this->instance.getLG().getEdgeId(ef);
                Vertex f = ef.u;

                if (f == e) {
                    f = ef.v;
                }

                /* subgradient^{5}_{{e, f}, j} = |U|x_{e, j} - z_{f, e, j} */
                this->subgradient5[efId - 1][j] = 
                    ((double) this->instance.getLG().n()) * this->x[eId - 1][j];

                if (f < e) {
                    this->subgradient5[efId - 1][j] -= this->z[efId - 1][j];
                } else {
                    this->subgradient5[efId - 1][j] -= 
                        this->z[this->instance.getGPrime().m() + efId - 1][j];
                }

                /* if λ^{5}_{{e, f}, j} = 0.0 && subgradient^{5}_{{e, f}, j} < 0 */
                if (fabs(this->lambda5[efId - 1][j]) < 1E-5 && 
                        this->subgradient5[efId - 1][j] < 0.0) {
                    /* subgradient^{5}_{{e, f}, j} = 0.0 */
                    this->subgradient5[efId - 1][j] = 0.0;
                }
            }
        }
    }

    this->subgradient6 = std::vector<std::vector<double> > (
            this->instance.getLG().n(), std::vector<double> (
                this->instance.getM()));

    /* ∀ j ∈ {1, ..., m} */
    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        /* ∀ e ∈ U */
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            /*
             * subgradient^{6}_{e, j} = x_{e, j} 
             * + ∑_{{e, f} ∈ σ_{G'}({e})}{z_{e, f, j}} 
             * - ∑_{{e, f} ∈ σ_{G'}({e})}{z_{f, e, j}}
             */
            this->subgradient6[eId - 1][j] = this->x[eId - 1][j];

            for (const Edge & ef : this->instance.getGPrime().getIncidentEdges(e)) {
                unsigned int efId = this->instance.getGPrime().getEdgeId(ef);
                Vertex f = ef.u;

                if (f == e) {
                    f = ef.v;
                }

                if (e < f) {
                    this->subgradient6[eId - 1][j] += this->z[efId - 1][j];
                    this->subgradient6[eId - 1][j] -= 
                        this->z[this->instance.getGPrime().m() + efId - 1][j];
                } else {
                    this->subgradient6[eId - 1][j] += 
                        this->z[this->instance.getGPrime().m() + efId - 1][j];
                    this->subgradient6[eId - 1][j] -= this->z[efId - 1][j];
                }
            }
        }
    }
}

/*
 * Define a step size T.
 */
void LagrangianHeuristicSolver1::defineStepSize() {
    double numerator = this->PI * (1.05 * this->bestDualBound - 
            ((double) this->bestPrimalBound));
    double denominator = 0.0;

    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        denominator += this->subgradient1[j] * this->subgradient1[j];
    }

    denominator += this->subgradient2 * this->subgradient2;

    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            denominator += this->subgradient3[eId - 1][j] * this->subgradient3[eId - 1][j];
        }
    }

    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            for (const Edge & ef : this->instance.getLG().getIncidentEdges(e)) {
                unsigned int efId = this->instance.getLG().getEdgeId(ef);

                denominator += this->subgradient4[efId - 1][j] * 
                    this->subgradient4[efId - 1][j];
            }
        }
    }

    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            for (const Edge & ef : this->instance.getLG().getIncidentEdges(e)) {
                unsigned int efId = this->instance.getLG().getEdgeId(ef);

                denominator += this->subgradient5[efId - 1][j] * 
                    this->subgradient5[efId - 1][j];
            }
        }
    }

    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            denominator += this->subgradient6[eId - 1][j] * this->subgradient6[eId - 1][j];
        }
    }

    this->T = numerator / denominator;
}

/*
 * Update the Lagrangian multipliers.
 */
void LagrangianHeuristicSolver1::updateLagrangianMultipliers() {
    /* ∀ j ∈ {1, ..., m} */
    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        /* λ^{1}_{j} = λ^{1}_{j} + T * subgradient^{1}_{j} */
        this->lambda1[j] += this->T * this->subgradient1[j];
    }

    /* λ^{2} = λ^{2} + T * subgradient^{2} */
    this->lambda2 += this->T * this->subgradient2;

    /* ∀ j ∈ {1, ..., m} */
    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        /* ∀ e ∈ U */
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            /* λ^{3}_{e, j} = max{0, λ^{3}_{e, j} + T * subgradient^{3}_{e, j}} */
            this->lambda3[eId - 1][j] += this->T * this->subgradient3[eId - 1][j];

            if (this->lambda3[eId - 1][j] < 0.0) {
                this->lambda3[eId - 1][j] = 0.0;
            }
        }
    }

    /* ∀ j ∈ {1, ..., m} */
    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        /* ∀ e ∈ U */
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            /* ∀ {e, f} ∈ σ_{L(G)}({e}) */
            for (const Edge & ef : this->instance.getLG().getIncidentEdges(e)) {
                unsigned int efId = this->instance.getLG().getEdgeId(ef);

                /*
                 * λ^{4}_{{e, f}, j} = max{0, 
                 * λ^{4}_{{e, f}, j} + T * subgradient^{4}_{{e, f}, j}}
                 */
                this->lambda4[efId - 1][j] += this->T * this->subgradient4[efId - 1][j];

                if (this->lambda4[efId - 1][j] < 0.0) {
                    this->lambda4[efId - 1][j] = 0.0;
                }
            }
        }
    }

    /* ∀ j ∈ {1, ..., m} */
    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        /* ∀ e ∈ U */
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            /* ∀ {e, f} ∈ σ_{L(G)}({e}) */
            for (const Edge & ef : this->instance.getLG().getIncidentEdges(e)) {
                unsigned int efId = this->instance.getLG().getEdgeId(ef);

                /*
                 * λ^{5}_{{e, f}, j} = max{0, 
                 * λ^{5}_{{e, f}, j} + T * subgradient^{5}_{{e, f}, j}}
                 */
                this->lambda5[efId - 1][j] += this->T * this->subgradient5[efId - 1][j];

                if (this->lambda5[efId - 1][j] < 0.0) {
                    this->lambda5[efId - 1][j] = 0.0;
                }
            }
        }
    }

    /* ∀ j ∈ {1, ..., m} */
    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        /* ∀ e ∈ U */
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            /* λ^{6}_{e, j} = λ^{6}_{e, j} + T * subgradient^{6}_{e, j} */
            this->lambda6[eId - 1][j] += this->T * this->subgradient6[eId - 1][j];
        }
    }
}

/*
 * Verifies whether this solver's termination criteria have been met.
 *
 * @return true if this solver's termination criteria have been met; false otherwise.
 */
bool LagrangianHeuristicSolver1::areTerminationCriteriaMet() const {
    if (CEDPSolver::areTerminationCriteriaMet()) {
        return true;
    }

    /* Verifies whether π is small enough */
    if (this->PI <= 0.005) {
        return true;
    }

    /* Verifies whether the current solution is optimal */
    /* ∀ j ∈ {1, ..., m} */
    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        unsigned int sumYePrimeEj = 0;

        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            if (this->y[eId - 1][j]) {
                sumYePrimeEj++;
            }
        }

        /* if ∑_{e ∈ U}{y_{{e', e}, j}} ≠ 1 */
        if (sumYePrimeEj != 1) {
            return false;
        }
    }

    double sumZePrimeEj = 0.0;

    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            Edge ePrimeE = Edge(this->instance.getEPrime(), e);
            unsigned int ePrimeEid = this->instance.getGPrime().getEdgeId(ePrimeE);

            sumZePrimeEj += this->z[ePrimeEid - 1][j];
        }
    }

    /* if ∑_{j = 1}^{m}{∑_{e ∈ U}{z_{e', e, j}}} ≠ |U| */
    if (fabs(sumZePrimeEj - ((double) this->instance.getLG().n())) > 1E-5) {
        return false;
    }

    /* ∀ j ∈ {1, ..., m} */
    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        /* ∀ e ∈ U */
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);
            Edge ePrimeE = Edge(this->instance.getEPrime(), e);
            unsigned int ePrimeEid = this->instance.getGPrime().getEdgeId(ePrimeE);

            /* if z_{e', e, j} - |U|y_{{e', e}, j} > 0 */
            if (this->y[eId - 1][j]) {
                if (this->z[ePrimeEid - 1][j] - ((double) this->instance.getLG().n()) > 0.0) {
                    return false;
                }
            } else {
                if (this->z[ePrimeEid - 1][j] > 0.0) {
                    return false;
                }
            }
        }
    }

    /* ∀ j ∈ {1, ..., m} */
    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        /* ∀ e ∈ U */
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            /* ∀ {e, f} ∈ σ_{L(G)}({e}) */
            for (const Edge & ef : this->instance.getGPrime().getIncidentEdges(e)) {
                unsigned int efId = this->instance.getGPrime().getEdgeId(ef);
                Vertex f = ef.u;

                if (f == e) {
                    f = ef.v;
                }

                if (e > f) {
                    efId += this->instance.getGPrime().m();
                }

                /* if z_{e, f, j} - |U|x_{e, j} > 0 */
                if (this->x[eId - 1][j]) {
                    if (this->z[efId - 1][j] - ((double) this->instance.getLG().n()) > 0.0) {
                        return false;
                    }
                } else {
                    if (this->z[efId - 1][j] > 0.0) {
                        return false;
                    }
                }
            }
        }
    }

    /* ∀ j ∈ {1, ..., m} */
    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        /* ∀ e ∈ U */
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            /* ∀ {e, f} ∈ σ_{L(G)}({e}) */
            for (const Edge & ef : this->instance.getGPrime().getIncidentEdges(e)) {
                unsigned int efId = this->instance.getGPrime().getEdgeId(ef);
                Vertex f = ef.u;

                if (f == e) {
                    f = ef.v;
                }

                if (e < f) {
                    efId += this->instance.getGPrime().m();
                }

                /* if z_{f, e, j} - |U|x_{e, j} > 0 */
                if (this->x[eId - 1][j]) {
                    if (this->z[efId - 1][j] - ((double) this->instance.getLG().n()) > 0.0) {
                        return false;
                    }
                } else {
                    if (this->z[efId - 1][j] > 0.0) {
                        return false;
                    }
                }
            }
        }
    }

    /* ∀ j ∈ {1, ..., m} */
    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        /* ∀ e ∈ U */
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);
            double sumZefj = 0.0;
            double sumZfej = 0.0;

            for (const Edge & ef : this->instance.getGPrime().getIncidentEdges(e)) {
                unsigned int efId = this->instance.getGPrime().getEdgeId(ef);
                Vertex f = ef.u;

                if (f == e) {
                    f = ef.v;
                }

                if (e < f) {
                    sumZefj += this->z[efId - 1][j];
                    sumZfej += this->z[this->instance.getGPrime().m() + efId - 1][j];
                } else {
                    sumZefj += this->z[this->instance.getGPrime().m() + efId - 1][j];
                    sumZfej += this->z[efId - 1][j];
                }
            }

            /*
             * if ∑_{{e, f} ∈ σ_{G'}({e})}{z_{f, e, j}} 
             *  - ∑_{{e, f} ∈ σ_{G'}({e})}{z_{e, f, j}} 
             *  - x_{e, j} ≠ 0
             */
            if (this->x[eId - 1][j]) {
                if (fabs(sumZfej - sumZefj - 1.0) > 1E-5) {
                    return false;
                }
            } else {
                if (fabs(sumZfej - sumZefj) > 1E-5) {
                    return false;
                }
            }
        }
    }

    /* ∀ j ∈ {1, ..., m} */
    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        /* ∀ e ∈ U */
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            /* if λ^{3}_{e, j} > 0 */
            if (this->lambda3[eId - 1][j] > 0.0) {
                Edge ePrimeE = Edge(this->instance.getEPrime(), e);
                unsigned int ePrimeEid = this->instance.getGPrime().getEdgeId(ePrimeE);

                /* if z_{e', e, j} - |U|y_{{e', e}, j} ≠ 0 */
                if (this->y[eId - 1][j]) {
                    if (fabs(this->z[ePrimeEid - 1][j] - 
                                ((double) this->instance.getLG().n())) > 1E-5) {
                        return false;
                    }
                } else {
                    if (fabs(this->z[ePrimeEid - 1][j]) > 1E-5) {
                        return false;
                    }
                }
            }
        }
    }

    /* ∀ j ∈ {1, ..., m} */
    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        /* ∀ e ∈ U */
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            /* ∀ {e, f} ∈ σ_{L(G)}({e}) */
            for (const Edge & ef : this->instance.getGPrime().getIncidentEdges(e)) {
                unsigned int efId = this->instance.getGPrime().getEdgeId(ef);

                /* if λ^{4}_{{e, f}, j} > 0 */
                if (this->lambda4[efId - 1][j] > 0.0) {
                    Vertex f = ef.u;

                    if (f == e) {
                        f = ef.v;
                    }

                    if (e > f) {
                        efId += this->instance.getGPrime().m();
                    }

                    /* if z_{e, f, j} - |U|x_{e, j} ≠ 0 */
                    if (this->x[eId - 1][j]) {
                        if (fabs(this->z[efId - 1][j] - 
                                    ((double) this->instance.getLG().n())) > 1E-5) {
                            return false;
                        }
                    } else {
                        if (fabs(this->z[efId - 1][j]) > 1E-5) {
                            return false;
                        }
                    }
                }
            }
        }
    }

    /* ∀ j ∈ {1, ..., m} */
    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        /* ∀ e ∈ U */
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            /* ∀ {e, f} ∈ σ_{L(G)}({e}) */
            for (const Edge & ef : this->instance.getGPrime().getIncidentEdges(e)) {
                unsigned int efId = this->instance.getGPrime().getEdgeId(ef);

                /* if λ^{5}_{{e, f}, j} > 0 */
                if (this->lambda5[efId - 1][j] > 0.0) {
                    Vertex f = ef.u;

                    if (f == e) {
                        f = ef.v;
                    }

                    if (e < f) {
                        efId += this->instance.getGPrime().m();
                    }

                    /* if z_{f, e, j} - |U|x_{e, j} ≠ 0 */
                    if (this->x[eId - 1][j]) {
                        if (fabs(this->z[efId - 1][j] - 
                                    ((double) this->instance.getLG().n())) > 1E-5) {
                            return false;
                        }
                    } else {
                        if (fabs(this->z[efId - 1][j]) > 1E-5) {
                            return false;
                        }
                    }
                }
            }
        }
    }

    return true;
}

/*
 * Returns this solver's π updating parameter.
 *
 * @return this solver's π updating parameter.
 */
unsigned int LagrangianHeuristicSolver1::getN() {
    return this->N;
}

/*
 * Solve this solver's instance.
 */
void LagrangianHeuristicSolver1::solve() {
    this->startTime = std::chrono::steady_clock::now();

    this->iterationsCounter = 0;
    this->bestSolutionIteration = 0;
    this->bestSolutionTime = 0;
    this->notPartitionSolutionsCounter = 0;
    this->notConnectedSolutionsCounter = 0;
    this->notRespectsCapacitySolutionsCounter = 0;
    this->notBalancedSolutionsCounter = 0;
    this->notFeasibleSolutionsCounter = 0;
    this->fixedSolutionsCounter = 0;

    /* Set π=2 initially */
    this->PI = 2.0;

    /* Initialize the primal bound from some heuristic for the problem */
    this->bestPrimalSolution = this->gcHeuristic.constructSolution(round(
                0.05 * ((double) this->timeLimit)));

    if (!this->bestPrimalSolution.isFeasible()) {
        this->bestPrimalSolution = SolutionFixer::fixSolution(
                this->bestPrimalSolution, round(
                    0.05 * ((double) this->timeLimit)));
    }

    if (this->bestPrimalSolution.isFeasible()) {
        this->solutionsCounter++;
        this->bestPrimalBound = this->bestPrimalSolution.getValue();
        this->bestSolutionIteration = this->iterationsCounter;
        this->bestSolutionTime = this->getElapsedTime();
    }

    /* Decide upon an initial set of Lagrangian multipliers */
    /* λ^{1}_{j} = 1.0, ∀ j ∈ {1, ..., m} */
    this->lambda1 = std::vector<double> (this->instance.getM(), 1.0);
    /* λ^{2} = 1.0 */
    this->lambda2 = 1.0;
    /* λ^{3}_{e, j} 1.0, ∀ e ∈ U, j ∈ {1, ..., m} */
    this->lambda3 = std::vector<std::vector<double> > (
            this->instance.getLG().n(), std::vector<double> (
                this->instance.getM(), 1.0));
    /* λ^{4}_{{e, f}, j} = 1.0, ∀ {e, f} ∈ A, j ∈ {1, ..., m} */
    this->lambda4 = std::vector<std::vector<double> > (
            this->instance.getLG().m(), std::vector<double> (
                this->instance.getM(), 1.0));
    /* λ^{5}_{{e, f}, j} = 1.0, ∀ {e, f} ∈ A, j ∈ {1, ..., m */
    this->lambda5 = std::vector<std::vector<double> > (
            this->instance.getLG().m(), std::vector<double> (
                this->instance.getM(), 1.0));
    /* λ^{6}_{e, j} = 1.0, ∀ e ∈ U, j ∈ {1, ..., m} */
    this->lambda6 = std::vector<std::vector<double> > (
            this->instance.getLG().n(), std::vector<double> (
                this->instance.getM(), 1.0));

    unsigned int iterationsWithoutImprovment = 0;

    do {
        this->iterationsCounter++;

        /* Solve the Lagrangian relaxation subproblem with the current set of multipliers */
        double dualBound = this->solveLagrangianRelaxationSubproblem();

        if (CEDPSolver::areTerminationCriteriaMet()) {
            break;
        }

        if (this->bestDualBound > dualBound) {
            this->bestDualBound = dualBound;
            iterationsWithoutImprovment = 0;
        } else {
            iterationsWithoutImprovment++;
        }

        bool isFeasible = true;

        if (!this->currentSolution.isPartition()) {
            isFeasible = false;
            this->notPartitionSolutionsCounter++;
        }

        if (!this->currentSolution.isConnected()) {
            isFeasible = false;
            this->notConnectedSolutionsCounter++;
        }

        if (!this->currentSolution.respectsCapacity()) {
            isFeasible = false;
            this->notRespectsCapacitySolutionsCounter++;
        }

        if (!this->currentSolution.isBalanced()) {
            isFeasible = false;
            this->notBalancedSolutionsCounter++;
        }


        if (!isFeasible) {
            this->notFeasibleSolutionsCounter++;

            unsigned int elapsedTime = this->getElapsedTime();
            unsigned int remainingTime = 0;

            if (this->timeLimit > elapsedTime) {
                remainingTime = this->timeLimit - elapsedTime;
            }

            this->currentSolution = SolutionFixer::fixSolution(
                    this->currentSolution, remainingTime);
        }

        if (this->currentSolution.isFeasible()) {
            this->solutionsCounter++;

            if (!isFeasible) {
                this->fixedSolutionsCounter++;
            }

            unsigned int elapsedTime = this->getElapsedTime();
            unsigned int remainingTime = 0;

            if (this->timeLimit > elapsedTime) {
                remainingTime = this->timeLimit - elapsedTime;
            }

            this->currentSolution = this->lsHeuristic.improveSolution(
                    this->currentSolution, remainingTime);

            double primalBound = this->currentSolution.getValue();

            if (this->bestPrimalBound < primalBound) {
                this->bestPrimalBound = primalBound;
                this->bestPrimalSolution = this->currentSolution;
                this->bestSolutionIteration = this->iterationsCounter;
                this->bestSolutionTime = this->getElapsedTime();
            }
        }

        /* Define subgradients for the relaxed constraints */
        this->defineSubgradients();
        /* Define a step size T */
        this->defineStepSize();
        /* Update the Lagrangian multipliers */
        this->updateLagrangianMultipliers();

        /* If bestDualBound has no improved in the last N subgradient iterations */
        if (iterationsWithoutImprovment >= this->N) {
            /* then halve π */
            this->PI /= 2.0;
            iterationsWithoutImprovment = 0;
        }
    } while (!this->areTerminationCriteriaMet());

    this->solvingTime = this->getElapsedTime();
}

/*
 * Write this solver's statistics into the specified output stream.
 *
 * @param os the output stream to write into.
 */
void LagrangianHeuristicSolver1::write(std::ostream & os) const {
    CEDPSolver::write(os);
    os << "Total iterations: " << this->iterationsCounter << std::endl;
    os << "Best solution iteration: " << this->bestSolutionIteration << std::endl;
    os << "Best solution time: " << this->bestSolutionTime << std::endl;
    os << "Solutions that are not partition: " << 
        this->notPartitionSolutionsCounter << std::endl;
    os << "Solutions that are not connected: " << 
        this->notConnectedSolutionsCounter << std::endl;
    os << "Solutions that do not respects the capacity: " << 
        this->notRespectsCapacitySolutionsCounter << std::endl;
    os << "Solutions that are not balanced: " << this->notBalancedSolutionsCounter << std::endl;
    os << "Solutions that are not feasible: " << this->notFeasibleSolutionsCounter << std::endl;
    os << "Solutions that were fixed: " << this->fixedSolutionsCounter << std::endl;
    os << "N: " << this->N << std::endl;
    os << "PI: " << this->PI << std::endl;
    os << "Step size: " << this->T << std::endl;
}

/*
 * Write this solver's statistics into the specified file.
 *
 * @param filename the file to write into.
 */
void LagrangianHeuristicSolver1::write(const char * filename) const {
    std::ofstream ofs;
    ofs.open(filename);

    if (ofs.is_open()) {
        this->write(ofs);
        ofs.close();
    } else {
        throw "File not created.";
    }
}

/*
 * Write this solver's statistics into the specified file.
 *
 * @param filename the file to write into.
 */
void LagrangianHeuristicSolver1::write(const std::string & filename) const {
    this->write(filename.c_str());
}

/*
 * Write this solver's statistics into the standard output stream.
 */
void LagrangianHeuristicSolver1::write() const {
    this->write(std::cout);
}

