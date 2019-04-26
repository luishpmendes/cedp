#include "LinearRelaxationSolver.hpp"
#include "gurobi_c++.h"

/*
 * Constructs a new solver.
 *
 * @param instance  the new solver's instance.
 * @param timeLimit the new solver's time limit.
 * @param seed      the seed for the new solver's pseudo-random numbers generator.
 */
LinearRelaxationSolver::LinearRelaxationSolver(const Instance & instance, 
        unsigned int timeLimit, unsigned int seed) : CEDPSolver::CEDPSolver(
            instance, timeLimit, seed) {}

/*
 * Constructs a new empty solver.
 */
LinearRelaxationSolver::LinearRelaxationSolver() : CEDPSolver::CEDPSolver() {}

/*
 * Solve this solver's instance.
 */
void LinearRelaxationSolver::solve() {
    this->startTime = std::chrono::steady_clock::now();

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

        /* ∀ e ∈ U′ */
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            /* ∀ j ∈ {1, ..., m} */
            for (unsigned int j = 0; j < this->instance.getM(); j++) {
                unsigned int obj = 0;

                if (this->instance.getLG().hasVertex(e)) {
                    obj = this->instance.getC(eId, j);
                }

                /* x_{e, j} ∈ {0, 1} */
                x[eId - 1][j] = model.addVar(0.0, 1.0, obj, GRB_CONTINUOUS, 
                        "x_" + std::to_string(eId - 1) + "_" + 
                        std::to_string(j));
            }
        }

        /* ∀ {e′, e} ∈ A′\A */
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            /* ∀ j ∈ {1, ..., m} */
            for (unsigned int j = 0; j < this->instance.getM(); j++) {
                /* y_{{e′, e}, j} ∈ {0, 1} */
                y[eId - 1][j] = model.addVar(0.0, 1.0, 0.0, GRB_CONTINUOUS, 
                        "x_" + std::to_string(eId - 1) + "_" + 
                        std::to_string(j));
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

        /* max{∑_{e ∈ U}{∑_{j = 1}^{m}{c_{e, j} * x_{e, j}}}} */
        model.set(GRB_IntAttr_ModelSense, GRB_MAXIMIZE);

        /* ∀ e ∈ U */
        for (const Vertex & e : this->instance.getLG().getVertices()) {
            unsigned int eId = this->instance.getLG().getVertexId(e);

            /* ∑_{j = 1}^{m}{x_{e, j}} = 1 */
            GRBLinExpr constr1 = 0.0;

            for (unsigned int j = 0; j < this->instance.getM(); j++) {
                constr1 += x[eId - 1][j];
            }

            model.addConstr(constr1 == 1, "c_1_" + std::to_string(eId - 1));
        }

        /* ∀ j ∈ {1, ..., m} */
        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            /*
             * 2 * ∑_{e ∈ U}{d_{e} * x_{e, j}} <= 
             * min{D, ((2 * (1 + B)) / m) * ∑_{e ∈ U}{d_{e}}
             */
            GRBLinExpr constr2 = 0.0;

            for (const Vertex & e : this->instance.getLG().getVertices()) {
                unsigned int eId = this->instance.getLG().getVertexId(e);

                constr2 += 2.0 * e.w * x[eId - 1][j];
            }

            double rhs = this->instance.getMaximumDemand();

            model.addConstr(constr2 <= rhs, "c_02_" + std::to_string(j));
        }

        /* ∀ j ∈ {1, ..., m} */
        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            /* ∑_{e ∈ U}{d_{e} * x_{e, j}} >= ((2 * (1 - B)) / m) * ∑_{e ∈ U}{d_{e}} */
            GRBLinExpr constr3 = 0.0;

            for (const Vertex & e : this->instance.getLG().getVertices()) {
                unsigned int eId = this->instance.getLG().getVertexId(e);

                constr3 += 2.0 * e.w * x[eId - 1][j];
            }

            double rhs = this->instance.getMinimumDemand();

            model.addConstr(constr3 >= rhs, "c_3_" + std::to_string(j));
        }

        /* ∀ j ∈ {1, ..., m} */
        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            /* ∑_{e ∈  U}{y_{{e′, e}, j}} = 1 */
            GRBLinExpr constr4 = 0.0;

            for (const Vertex & e : this->instance.getLG().getVertices()) {
                unsigned int eId = this->instance.getLG().getVertexId(e);

                constr4 += y[eId - 1][j];
            }

            model.addConstr(constr4 == 1, "c_4_" + std::to_string(j));
        }

        /* ∑_{j = 1}^{m}{∑_{e ∈ U}{z_{e′, e, j}}} = |U| */
        GRBLinExpr constr5 = 0.0;

        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            for (const Edge & ePrimeE : 
                    this->instance.getGPrime().getIncidentEdges(this->instance.getEPrime())) {
                unsigned int ePrimeEId = this->instance.getGPrime().getEdgeId(ePrimeE);
                Vertex e = ePrimeE.u;

                if (e == this->instance.getEPrime()) {
                    e = e.v;
                }

                if (this->instance.getEPrime() < e) {
                    constr5 += z[ePrimeEId - 1][j];
                } else {
                    constr5 += z[this->instance.getGPrime().m() + ePrimeEId - 1][j];
                }
            }
        }

        model.addConstr(constr5 == this->instance.getLG().n(), "c_5");

        /* ∀ j ∈ {1, ..., m} */
        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            for (const Vertex & e : this->instance.getLG().getVertices()) {
                unsigned int eId = this->instance.getLG().getVertexId(e);
                unsigned int ePrimeEId = this->instance.getGPrime().getEdgeId(
                        this->instance.getEPrime(), e);

                /* z_{e′, e, j} - |U| y_{{e′, e}, j} <= 0 */
                GRBLinExpr constr6 = 0.0;

                if (e > this->instance.getEPrime()) {
                    constr6 += z[ePrimeEId - 1][j];
                } else {
                    constr6 += z[this->instance.getGPrime().m() + ePrimeEId - 1][j];
                }

                constr6 -= this->instance.getLG().n() * y[eId - 1][j];

                model.addConstr(constr6 <= 0, "c_6_" + std::to_string(eId) 
                        + "_" + std::to_string(j));
            }
        }

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

                    unsigned int fId = this->instance.getLG().getVertexId(f);

                    /* z_{e, f, j} - |U| * x_{e, j} <= 0 */
                    GRBLinExpr constr7 = 0.0;

                    if (e < f) {
                        constr7 += z[efId - 1][j];
                    } else {
                        constr7 += z[this->instance.getGPrime().m() + efId - 1][j];
                    }

                    constr7 -= this->instance.getLG().n() * x[eId - 1][j];

                    model.addConstr(constr7 <= 0, "c_7_" + 
                            std::to_string(fId) + "_" + std::to_string(eId) + 
                            "_" + std::to_string(j));
                }
            }
        }

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

                    unsigned int fId = this->instance.getLG().getVertexId(f);

                    /* z_{f, e, j} - |U| * x_{e, j} <= 0 */
                    GRBLinExpr constr8 = 0.0;

                    if (f < e) {
                        constr8 += z[efId - 1][j];
                    } else {
                        constr8 += z[this->instance.getGPrime().m() + efId - 1][j];
                    }

                    constr8 -= this->instance.getLG().n() * x[eId - 1][j];

                    model.addConstr(constr8 <= 0, "c_8_" + 
                            std::to_string(eId) + "_" + std::to_string(fId) + 
                            "_" + std::to_string(j));
                }
            }
        }

        /* ∀ j ∈ {1, ..., m} */
        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            /* ∀ e ∈ U */
            for (Vertex e : this->instance.getLG().getVertices()) {
                unsigned int eId = this->instance.getLG().getVertexId(e);
                /*
                 * ∑_{f ∈ σ_{G′}(e)}{z_{f, e, j}} - 
                 * ∑_{f ∈ σ_{G′}(e)}{y_{e, f, j}} - x_{e, j} = 0 
                 */
                GRBLinExpr constr9 = 0.0;

                for (const Edge & ef : this->instance.getGPrime().getIncidentEdges(e)) {
                    unsigned int efId = this->instance.getGPrime().getEdgeId(ef);
                    Vertex f = ef.u;

                    if (f == e) {
                        f = ef.v;
                    }

                    if (f < e) {
                        constr9 += z[efId - 1][j];
                    } else {
                        constr9 += z[this->instance.getGPrime().m() + efId - 1][j];
                    }
                }

                for (const Edge & ef : this->instance.getGPrime().getIncidentEdges(e)) {
                    unsigned int efId = this->instance.getGPrime().getEdgeId(ef);
                    Vertex f = ef.u;

                    if (f == e) {
                        f = ef.v;
                    }

                    if (e < f) {
                        constr9 -= z[efId - 1][j];
                    } else {
                        constr9 -= z[this->instance.getGPrime().m() + efId - 1][j];
                    }
                }

                constr9 -= x[eId - 1][j];

                model.addConstr(constr9 == 0, "c_9_" +  std::to_string(eId) 
                        + "_" + std::to_string(j));
            }
        }

        unsigned int elapsedTime = this->getElapsedTime();
        unsigned int remainingTime = 0;

        if (this->timeLimit > elapsedTime) {
            remainingTime = this->timeLimit - elapsedTime;
        }

        model.set(GRB_DoubleParam_TimeLimit, remainingTime);
        model.set(GRB_IntParam_OutputFlag, 0);
        model.set(GRB_IntParam_Threads, 1);

        model.update();

        model.optimize();


        if (model.get(GRB_IntAttr_Status) == GRB_OPTIMAL) {
            this->bestDualBound = model.get(GRB_DoubleAttr_ObjVal);

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

            if (!solution.isFeasible()) {
                elapsedTime = this->getElapsedTime();
                remainingTime = 0;

                if (this->timeLimit > elapsedTime) {
                    remainingTime = this->timeLimit - elapsedTime;
                }

                solution = SolutionFixer::fixSolution(solution, remainingTime);
            }


            if (solution.isFeasible()) {
                this->solutionsCounter++;

                elapsedTime = this->getElapsedTime();
                remainingTime = 0;

                if (this->timeLimit > elapsedTime) {
                    remainingTime = this->timeLimit - elapsedTime;
                }

                solution = this->lsHeuristic.improveSolution(solution, remainingTime);

                double primalBound = solution.getValue();

                if (this->bestPrimalBound < primalBound) {
                    this->bestPrimalBound = primalBound;
                    this->bestPrimalSolution = solution;
                }
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

