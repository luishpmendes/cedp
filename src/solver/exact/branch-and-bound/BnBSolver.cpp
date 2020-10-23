#include "BnBSolver.hpp"
#include "../../metaheuristic/grasp/GRASPSolver.hpp"
#include "gurobi_c++.h"
#include <algorithm>

/*
 * Constructs a new solver.
 *
 * @param instance                the new solver's instance.
 * @param timeLimit               the new solver's time limit.
 * @param seed                    the seed for the new solver's pseudo-random
 *                                numbers generator.
 * @param warmStartPercentageTime the percentage of time to find a warm start
 *                                solution.
 * @param m                       the number of values for the GRASP's threshold
 *                                parameter.
 * @param k                       The number of iterations between each update
 *                                in the GRASP's threshold parameter
 *                                probabilities.
 */
BnBSolver::BnBSolver(const Instance & instance,
                     unsigned int timeLimit,
                     unsigned int seed,
                     double warmStartPercentageTime,
                     unsigned int m,
                     unsigned int k)
    : CEDPSolver::CEDPSolver(instance, timeLimit, seed),
      warmStartPercentageTime(warmStartPercentageTime),
      m(m),
      k(k) {}

/*
 * Constructs a new empty solver.
 */
BnBSolver::BnBSolver() : CEDPSolver::CEDPSolver() {}

/*
 * Returns the percentage of time to find a warm start solution.
 *
 * @return the percentage of time to find a warm start solution.
 */
double BnBSolver::getWarmStartPercentageTime() const {
    return this->warmStartPercentageTime;
}

/*
 * Returns the number of values for the GRASP's threshold parameter.
 *
 * @return the number of values for the GRASP's threshold parameter.
 */
unsigned int BnBSolver::getM() const {
    return this->m;
}

/*
 * Returns the number of iterations between each update in the GRASP's threshold parameter.
 *
 * @return the number of iterations between each update in the GRASP's threshold parameter.
 */
unsigned int BnBSolver::getK() const {
    return this->k;
}

/*
 * Solve this solver's instance.
 */
void BnBSolver::solve() {
    this->startTime = std::chrono::steady_clock::now();

    unsigned int graspTimeLimit =
        round(this->warmStartPercentageTime*this->timeLimit);

    if (graspTimeLimit > 0) {
        GRASPSolver solver(this->instance,
                           round(this->warmStartPercentageTime*this->timeLimit),
                           this->seed,
                           this->m,
                           this->k);

        solver.solve();

        this->bestPrimalSolution = solver.getBestPrimalSolution();

        if (this->bestPrimalSolution.isFeasible()) {
            this->solutionsCounter++;
            this->bestPrimalBound = this->bestPrimalSolution.getValue();
        }
    }

    GRBEnv * env = 0;

    try {
        env = new GRBEnv();
        GRBModel model = GRBModel(* env);

        std::vector<std::vector<GRBVar> > x (this->instance.getLG().n(), 
                std::vector<GRBVar> (this->instance.getM()));
        std::vector<std::vector<GRBVar> > y (this->instance.getLG().n(), 
                std::vector<GRBVar> (this->instance.getM()));
        std::vector<std::vector<GRBVar> > z (
                2 * this->instance.getGPrime().m(), 
                std::vector<GRBVar> (this->instance.getM()));

        std::set<Vertex> vertices = this->instance.getLG().getVertices();

        /* ∀ e ∈ U′ */
        for (const Vertex & e : vertices) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            /* ∀ j ∈ {1, ..., m} */
            for (unsigned int j = 0; j < this->instance.getM(); j++) {
                unsigned int obj = this->instance.getC(eId, j);

                /* x_{e, j} ∈ {0, 1} */
                x[eId - 1][j] = model.addVar(0.0, 1.0, obj, GRB_BINARY, "x_" + 
                        std::to_string(eId - 1) + "_" + std::to_string(j));
            }
        }

        /* ∀ {e′, e} ∈ A′\A */
        for (const Vertex & e : vertices) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            /* ∀ j ∈ {1, ..., m} */
            for (unsigned int j = 0; j < this->instance.getM(); j++) {
                /* y_{{e′, e}, j} ∈ {0, 1} */
                y[eId - 1][j] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "x_" + 
                        std::to_string(eId - 1) + "_" + std::to_string(j));
            }
        }

        /* ∀ {e, f} ∈ A′ */
        for (const Edge & ef : this->instance.getGPrime().getEdges()) {
            unsigned int efId = this->instance.getGPrime().getEdgeId(ef);

            /* ∀ j ∈ {1, ..., m} */
            for (unsigned int j = 0; j < this->instance.getM(); j++) {
                /* y_{e, f, j} ∈ [0, |U|] */
                z[efId - 1][j] = model.addVar(0.0, this->instance.getLG().n(), 
                        0.0, GRB_CONTINUOUS, "y_" + std::to_string(efId - 1) + 
                        "_" + std::to_string(j));

                /* y_{f, e, j} ∈ [0, |U|] */
                z[this->instance.getGPrime().m() + efId - 1][j] = model.addVar(
                        0.0, this->instance.getLG().n(), 0.0, GRB_CONTINUOUS, 
                        "y_" + std::to_string(this->instance.getGPrime().m() + 
                            efId - 1) + "_" + std::to_string(j));
            }
        }

        model.update();

        /* obj = ∑_{e ∈ U}{∑_{j = 1}^{m}{c_{e, j} * x_{e, j}}} */
        model.set(GRB_IntAttr_ModelSense, GRB_MAXIMIZE);

        /* ∀ e ∈ U */
        for (const Vertex & e : vertices) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            /* ∑_{j = 1}^{m}{x_{e, j}} = 1 */
            GRBLinExpr constr01 = 0.0;

            for (unsigned int j = 0; j < this->instance.getM(); j++) {
                constr01 += x[eId - 1][j];
            }

            model.addConstr(constr01 == 1, "c_01_" + std::to_string(eId - 1));
        }

        /* ∀ j ∈ {1, ..., m} */
        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            /*
             * 2 * ∑_{e ∈ U}{d_{e} * x_{e, j}} <= 
             * min{D, ((2 * (1 + B)) / m) * ∑_{e ∈ U}{d_{e}}
             */
            GRBLinExpr constr02 = 0.0;

            for (const Vertex & e : vertices) {
                unsigned int eId = this->instance.getLG().getVertexId(e);

                constr02 += 2.0 * e.w * x[eId - 1][j];
            }

            double rhs = this->instance.getMaximumDemand();

            model.addConstr(constr02 <= rhs, "c_02_" + std::to_string(j));
        }

        /* ∀ j ∈ {1, ..., m} */
        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            /* 
             * 2 * ∑_{e ∈ U}{d_{e} * x_{e, j}} >= 
             * ((2 * (1 - B)) / m) * ∑_{e ∈ U}{d_{e}}
             */
            GRBLinExpr constr03 = 0.0;

            for (const Vertex & e : vertices) {
                unsigned int eId = this->instance.getLG().getVertexId(e);

                constr03 += 2.0 * e.w * x[eId - 1][j];
            }

            double rhs = this->instance.getMinimumDemand();

            model.addConstr(constr03 >= rhs, "c_03_" + std::to_string(j));
        }

        /* ∀ j ∈ {1, ..., m} */
        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            /* ∑_{e ∈  U}{y_{{e′, e}, j}} = 1 */
            GRBLinExpr constr04 = 0.0;

            for (const Vertex & e : vertices) {
                unsigned int eId = this->instance.getLG().getVertexId(e);

                constr04 += y[eId - 1][j];
            }

            model.addConstr(constr04 == 1, "c_04_" + std::to_string(j));
        }


        /* ∀ j ∈ {1, ..., m} */
        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            /* ∀ e ∈ U */
            for (const Vertex & e : vertices) {
                unsigned int eId = this->instance.getLG().getVertexId(e);

                /* x_{e, j} - y_{{e′, e}, j} >= 0 */
                GRBLinExpr constr05 = x[eId - 1][j] - y[eId - 1][j];
                model.addConstr(constr05 >= 0.0, "c_05_" + 
                        std::to_string(eId) + "_" + std::to_string(j));
            }
        }

        /* ∀ j ∈ {1, ..., m} */
        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            /* ∀ e ∈ U */
            for (std::set<Vertex>::iterator eIt = vertices.begin(); 
                    eIt != vertices.end(); eIt++) {
                unsigned int eId = this->instance.getLG().getVertexId(*eIt);

                /* ∀ f ∈ U, f > e */
                for (std::set<Vertex>::iterator fIt = std::next(eIt); 
                        fIt != vertices.end(); fIt++) {
                    unsigned int fId = 
                        this->instance.getLG().getVertexId(*fIt);

                    GRBLinExpr constr06 = x[eId - 1][j] - y[eId - 1][j] + 
                        y[fId - 1][j];
                    model.addConstr(constr06 <= 1.0, "c_06_" + 
                            std::to_string(fId) + "_" + std::to_string(eId) + 
                            "_" + std::to_string(j));
                }
            }
        }

        /* ∑_{j = 1}^{m}{∑_{e ∈ U}{z_{e′, e, j}}} = |U| */
        GRBLinExpr constr07 = 0.0;

        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            for (const Edge & ePrimeE : 
                    this->instance.getGPrime().getIncidentEdges(
                        this->instance.getEPrime())) {
                unsigned int ePrimeEId = 
                    this->instance.getGPrime().getEdgeId(ePrimeE);
                Vertex e = ePrimeE.u;

                if (e == this->instance.getEPrime()) {
                    e = e.v;
                }

                if (this->instance.getEPrime() < e) {
                    constr07 += z[ePrimeEId - 1][j];
                } else {
                    constr07 += z[this->instance.getGPrime().m() + ePrimeEId - 1][j];
                }
            }
        }

        model.addConstr(constr07 == this->instance.getLG().n(), "c_07");

        unsigned int M = 0;
        double sumD = 0;
        std::vector<Vertex> verticesVector (vertices.begin(), vertices.end());
        std::sort(verticesVector.begin(), verticesVector.end(), 
                Vertex::weightComparator);

        for (M = 0; M < verticesVector.size() && 
                sumD < this->instance.getMaximumDemand(); M++) {
            sumD += verticesVector[M].w;
        }

        while (sumD > this->instance.getMaximumDemand()) {
            M--;
            sumD -= verticesVector[M].w;
        }

        if (M >= verticesVector.size()) {
            M--;
        }

        /* ∀ j ∈ {1, ..., m} */
        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            for (const Vertex & e : vertices) {
                unsigned int eId = this->instance.getLG().getVertexId(e);
                unsigned int ePrimeEId = this->instance.getGPrime().getEdgeId(
                        this->instance.getEPrime(), e);

                /* z_{e′, e, j} - |U| y_{{e′, e}, j} <= 0 */
                GRBLinExpr constr08 = 0.0;

                if (e > this->instance.getEPrime()) {
                    constr08 += z[ePrimeEId - 1][j];
                } else {
                    constr08 += z[this->instance.getGPrime().m() + ePrimeEId - 1][j];
                }

                constr08 -= M * y[eId - 1][j];

                model.addConstr(constr08 <= 0, "c_08_" + std::to_string(eId) 
                        + "_" + std::to_string(j));
            }
        }

        /* ∀ j ∈ {1, ..., m} */
        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            /* ∀ e ∈ U */
            for (const Vertex & e : vertices) {
                unsigned int eId = this->instance.getLG().getVertexId(e);

                /* ∀ {e, f} ∈ σ_{L(G)}({e}) */
                for (const Edge & ef : this->instance.getLG().getIncidentEdges(e)) {
                    unsigned int efId = this->instance.getLG().getEdgeId(ef);
                    Vertex f = ef.u;

                    if (f == e) {
                        f = ef.v;
                    }

                    unsigned int fId = this->instance.getLG().getVertexId(f);

                    /* z_{e, f, j} - |U| * x_{e, j} <= 0 */
                    GRBLinExpr constr09 = 0.0;

                    if (e < f) {
                        constr09 += z[efId - 1][j];
                    } else {
                        constr09 += z[this->instance.getGPrime().m() + efId - 1][j];
                    }

                    constr09 -= M * x[eId - 1][j];

                    model.addConstr(constr09 <= 0, "c_09_" + 
                            std::to_string(fId) + "_" + std::to_string(eId) + 
                            "_" + std::to_string(j));
                }
            }
        }

        /* ∀ j ∈ {1, ..., m} */
        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            /* ∀ e ∈ U */
            for (const Vertex & e : vertices) {
                unsigned int eId = this->instance.getLG().getVertexId(e);

                /* ∀ {e, f} ∈ σ_{L(G)}({e}) */
                for (const Edge & ef : this->instance.getLG().getIncidentEdges(e)) {
                    unsigned int efId = this->instance.getLG().getEdgeId(ef);
                    Vertex f = ef.u;

                    if (f == e) {
                        f = ef.v;
                    }

                    unsigned int fId = this->instance.getLG().getVertexId(f);

                    /* z_{f, e, j} - |U| * x_{e, j} <= 0 */
                    GRBLinExpr constr10 = 0.0;

                    if (f < e) {
                        constr10 += z[efId - 1][j];
                    } else {
                        constr10 += z[this->instance.getGPrime().m() + efId - 1][j];
                    }

                    constr10 -= M * x[eId - 1][j];

                    model.addConstr(constr10 <= 0, "c_10_" + 
                            std::to_string(eId) + "_" + std::to_string(fId) + 
                            "_" + std::to_string(j));
                }
            }
        }

        /* ∀ j ∈ {1, ..., m} */
        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            /* ∀ e ∈ U */
            for (Vertex e : vertices) {
                unsigned int eId = this->instance.getLG().getVertexId(e);
                /*
                 * ∑_{f ∈ σ_{G′}(e)}{z_{e, f, j}} - 
                 * ∑_{f ∈ σ_{G′}(e)}{y_{f, e, j}} + x_{e, j} = 0 
                 */
                GRBLinExpr constr11 = 0.0;

                for (const Edge & ef : this->instance.getGPrime().getIncidentEdges(e)) {
                    unsigned int efId = this->instance.getGPrime().getEdgeId(ef);
                    Vertex f = ef.u;

                    if (f == e) {
                        f = ef.v;
                    }

                    if (f < e) {
                        constr11 -= z[efId - 1][j];
                    } else {
                        constr11 -= z[this->instance.getGPrime().m() + efId - 1][j];
                    }
                }

                for (const Edge & ef : this->instance.getGPrime().getIncidentEdges(e)) {
                    unsigned int efId = this->instance.getGPrime().getEdgeId(ef);
                    Vertex f = ef.u;

                    if (f == e) {
                        f = ef.v;
                    }

                    if (e < f) {
                        constr11 += z[efId - 1][j];
                    } else {
                        constr11 += z[this->instance.getGPrime().m() + efId - 1][j];
                    }
                }

                constr11 += x[eId - 1][j];

                model.addConstr(constr11 == 0, "c_11_" +  std::to_string(eId) 
                        + "_" + std::to_string(j));
            }
        }

        for (const Vertex & e : vertices) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            for (unsigned int j = 0; j < this->instance.getM(); j++) {
                x[eId - 1][j].set(GRB_DoubleAttr_Start, 0.0);
            }
        }


        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            for (const Edge & e : this->bestPrimalSolution.getDistrict(j)) {
                unsigned int eId = this->instance.getG().getEdgeId(e);

                x[eId - 1][j].set(GRB_DoubleAttr_Start, 1.0);
            }
        }

        unsigned int elapsedTime = this->getElapsedTime();
        unsigned int remainingTime = 0;

        if (this->timeLimit > elapsedTime) {
            remainingTime = this->timeLimit - elapsedTime;
        }

        model.set(GRB_DoubleParam_TimeLimit, ((double) remainingTime));
        model.set(GRB_IntParam_OutputFlag, 0);
        model.set(GRB_IntParam_Threads, 1);

        model.update();

        model.optimize();

        this->bestDualBound = model.get(GRB_DoubleAttr_ObjBound);

        if (model.get(GRB_IntAttr_SolCount) > 0) {
            std::vector<std::set<Edge> > districts (this->instance.getM());

            for (unsigned int j = 0; j < this->instance.getM(); j++) {
                for (const Edge & e : this->instance.getG().getEdges()) {
                    unsigned int eId = this->instance.getG().getEdgeId(e);

                    if (x[eId - 1][j].get(GRB_DoubleAttr_X) >= 0.5) {
                        districts[j].insert(e);
                    }
                }
            }

            Solution solution = Solution(this->instance, districts);

            this->solutionsCounter++;

            double primalBound = solution.getValue();

            if (this->bestPrimalBound < primalBound) {
                this->bestPrimalBound = primalBound;
                this->bestPrimalSolution = solution;
            }
        }
    } catch (GRBException e) {
        std::cerr << "Error code = " << e.getErrorCode() << std::endl;
        std::cerr << e.getMessage() << std::endl;
    } catch (...) {
        std::cerr << "Error during optimization" << std::endl;
    }

    this->solvingTime = this->getElapsedTime();
}

