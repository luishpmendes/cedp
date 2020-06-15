#include "BnBSolver.hpp"
#include "gurobi_c++.h"
#include <algorithm>

/*
 * Constructs a new solver.
 *
 * @param instance  the new solver's instance.
 * @param timeLimit the new solver's time limit.
 * @param seed      the seed for the new solver's pseudo-random numbers generator.
 */
BnBSolver::BnBSolver(const Instance & instance, unsigned int timeLimit, 
        unsigned int seed) : CEDPSolver::CEDPSolver(instance, timeLimit, seed) {}

/*
 * Constructs a new empty solver.
 */
BnBSolver::BnBSolver() : CEDPSolver::CEDPSolver() {}

/*
 * Solve this solver's instance.
 */
void BnBSolver::solve() {
    this->startTime = std::chrono::steady_clock::now();

    GRBEnv * env = 0;

    try {
        env = new GRBEnv();
        GRBModel model = GRBModel(* env);

        std::vector<std::vector<GRBVar> > x (this->instance.getLG().n(), std::vector<GRBVar>
                (this->instance.getM()));
        std::vector<GRBVar> y (this->instance.getLG().n());
        std::vector<std::vector<GRBVar> > z (2 * this->instance.getGPrime().m(), std::vector<GRBVar>
                (this->instance.getM()));

        std::set<Vertex> vertices = this->instance.getLG().getVertices();

        /* ∀ e ∈ U′ */
        for (const Vertex & e : vertices) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            /* ∀ j ∈ {1, ..., m} */
            for (unsigned int j = 0; j < this->instance.getM(); j++) {
                unsigned int obj = this->instance.getC(eId, j);

                /* x_{e, j} ∈ {0, 1} */
                x[eId - 1][j] = model.addVar(0.0, 1.0, obj, GRB_BINARY, "x_" + std::to_string(eId -
                            1) + "_" + std::to_string(j));
            }
        }

        /* ∀ e ∈ U */
        for (const Vertex & e : vertices) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

                /* y_{e} ∈ {0, 1} */
                y[eId - 1] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "x_" + std::to_string(eId -
                            1));
        }

        /* ∀ {e, f} ∈ A′ */
        for (const Edge & ef : this->instance.getGPrime().getEdges()) {
            unsigned int efId = this->instance.getGPrime().getEdgeId(ef);

            /* ∀ j ∈ {1, ..., m} */
            for (unsigned int j = 0; j < this->instance.getM(); j++) {
                /* z_{e, f, j} ∈ [0, |U|] */
                z[efId - 1][j] = model.addVar(0.0, this->instance.getLG().n(), 0.0, GRB_CONTINUOUS,
                        "z_" + std::to_string(efId - 1) + "_" + std::to_string(j));

                /* z_{f, e, j} ∈ [0, |U|] */
                z[this->instance.getGPrime().m() + efId - 1][j] = model.addVar(0.0,
                        this->instance.getLG().n(), 0.0, GRB_CONTINUOUS, "z_" +
                        std::to_string(this->instance.getGPrime().m() + efId - 1) + "_" +
                        std::to_string(j));
            }
        }

        model.update();

        /* obj = ∑_{e ∈ U}{∑_{j = 1}^{m}{c_{e, j} * x_{e, j}}} */
        model.set(GRB_IntAttr_ModelSense, GRB_MAXIMIZE);

        /* ∀ e ∈ U */
        for (const Vertex & e : vertices) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            /* ∑_{j = 1}^{m}{x_{e, j}} = 1 */
            GRBLinExpr lhs1 = 0.0;

            for (unsigned int j = 0; j < this->instance.getM(); j++) {
                lhs1 += x[eId - 1][j];
            }

            model.addConstr(lhs1 == 1, "c_1_" + std::to_string(eId - 1));
        }

        /* ∀ j ∈ {1, ..., m} */
        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            /*
             * 2 * ∑_{e ∈ U}{d_{e} * x_{e, j}} <= 
             * min{D, ((2 * (1 + B)) / m) * ∑_{e ∈ U}{d_{e}}
             */
            GRBLinExpr lhs2 = 0.0;

            for (const Vertex & e : vertices) {
                unsigned int eId = this->instance.getLG().getVertexId(e);

                lhs2 += 2.0 * e.w * x[eId - 1][j];
            }

            model.addConstr(lhs2 <= this->instance.getMaximumDemand(), "c_2_" + 
                    std::to_string(j));
        }

        /* ∀ j ∈ {1, ..., m} */
        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            /* 
             * 2 * ∑_{e ∈ U}{d_{e} * x_{e, j}} >= 
             * ((2 * (1 - B)) / m) * ∑_{e ∈ U}{d_{e}}
             */
            GRBLinExpr lhs3 = 0.0;

            for (const Vertex & e : vertices) {
                unsigned int eId = this->instance.getLG().getVertexId(e);

                lhs3 += 2.0 * e.w * x[eId - 1][j];
            }

            model.addConstr(lhs3 >= this->instance.getMinimumDemand(), "c_3_" + 
                    std::to_string(j));
        }

        /* ∑_{e ∈  U}{y_{e}} = m */
        GRBLinExpr lhs4 = 0.0;

        for (const Vertex & e : vertices) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            lhs4 += y[eId - 1];
        }

        model.addConstr(lhs4 == this->instance.getM(), "c_4");

        /* ∑_{j = 1}^{m}{∑_{e ∈ U}{z_{e′, e, j}}} = |U| */
        GRBLinExpr lhs5 = 0.0;

        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            for (const Edge & ePrimeE :
                    this->instance.getGPrime().getIncidentEdges(this->instance.getEPrime())) {
                unsigned int ePrimeEId = this->instance.getGPrime().getEdgeId(ePrimeE);
                Vertex e = ePrimeE.u;

                if (e == this->instance.getEPrime()) {
                    e = e.v;
                }

                if (this->instance.getEPrime() < e) {
                    lhs5 += z[ePrimeEId - 1][j];
                } else {
                    lhs5 += z[this->instance.getGPrime().m() + ePrimeEId - 1][j];
                }
            }
        }

        model.addConstr(lhs5 == this->instance.getLG().n(), "c_5");

        unsigned int M = 0;
        double sumD = 0;
        std::vector<Vertex> verticesVector (vertices.begin(), vertices.end());
        std::sort(verticesVector.begin(), verticesVector.end(), Vertex::weightComparator);

        for (M = 0; M < verticesVector.size() && sumD < this->instance.getMaximumDemand(); M++) {
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
                unsigned int ePrimeEId =
                    this->instance.getGPrime().getEdgeId(this->instance.getEPrime(), e);

                /* z_{e′, e, j} - |U| y_{e} <= 0 */
                GRBLinExpr lhs6 = 0.0;

                if (e > this->instance.getEPrime()) {
                    lhs6 += z[ePrimeEId - 1][j];
                } else {
                    lhs6 += z[this->instance.getGPrime().m() + ePrimeEId - 1][j];
                }

                lhs6 -= M * y[eId - 1];

                model.addConstr(lhs6 <= 0, "c_6_" + std::to_string(eId) + "_" + 
                        std::to_string(j));
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
                    GRBLinExpr lhs7 = 0.0;

                    if (e < f) {
                        lhs7 += z[efId - 1][j];
                    } else {
                        lhs7 += z[this->instance.getGPrime().m() + efId - 1][j];
                    }

                    lhs7 -= M * x[eId - 1][j];

                    model.addConstr(lhs7 <= 0, "c_7_" + std::to_string(fId) + "_" +
                            std::to_string(eId) + "_" + std::to_string(j));
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
                    GRBLinExpr lhs8 = 0.0;

                    if (f < e) {
                        lhs8 += z[efId - 1][j];
                    } else {
                        lhs8 += z[this->instance.getGPrime().m() + efId - 1][j];
                    }

                    lhs8 -= M * x[eId - 1][j];

                    model.addConstr(lhs8 <= 0, "c_8_" + std::to_string(eId) + "_" +
                            std::to_string(fId) + "_" + std::to_string(j));
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
                 * ∑_{f ∈ σ_{G′}(e)}{z_{f, e, j}} + x_{e, j} = 0 
                 */
                GRBLinExpr lhs9 = 0.0;

                for (const Edge & ef : this->instance.getGPrime().getIncidentEdges(e)) {
                    unsigned int efId = this->instance.getGPrime().getEdgeId(ef);
                    Vertex f = ef.u;

                    if (f == e) {
                        f = ef.v;
                    }

                    if (f < e) {
                        lhs9 -= z[efId - 1][j];
                    } else {
                        lhs9 -= z[this->instance.getGPrime().m() + efId - 1][j];
                    }
                }

                for (const Edge & ef : this->instance.getGPrime().getIncidentEdges(e)) {
                    unsigned int efId = this->instance.getGPrime().getEdgeId(ef);
                    Vertex f = ef.u;

                    if (f == e) {
                        f = ef.v;
                    }

                    if (e < f) {
                        lhs9 += z[efId - 1][j];
                    } else {
                        lhs9 += z[this->instance.getGPrime().m() + efId - 1][j];
                    }
                }

                lhs9 += x[eId - 1][j];

                model.addConstr(lhs9 == 0, "c_9_" +  std::to_string(eId) + "_" + 
                        std::to_string(j));
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

        if (model.get(GRB_IntAttr_Status) == GRB_OPTIMAL) {
            this->bestDualBound = model.get(GRB_DoubleAttr_ObjBound);

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

