#include "BnCSolver.hpp"
#include "BnCSolverCallback.hpp"

/*
 * Constructs a new solver.
 *
 * @param instance  the new solver's instance.
 * @param timeLimit the new solver's time limit.
 * @param seed      the seed for the new solver's pseudo-random numbers generator.
 */
BnCSolver::BnCSolver(const Instance & instance, unsigned int timeLimit, 
        unsigned int seed) : CEDPSolver::CEDPSolver(instance, timeLimit, seed) {}

/*
 * Constructs a new empty solver.
 */
BnCSolver::BnCSolver() : CEDPSolver::CEDPSolver() {}

/*
 * Solve this solver's instance.
 */
void BnCSolver::solve() {
    this->startTime = std::chrono::steady_clock::now();

    GRBEnv * env = 0;

    try {
        env = new GRBEnv();
        GRBModel model = GRBModel(* env);

        std::vector<std::vector<GRBVar> > x (this->instance.getG().m(), std::vector<GRBVar>
                (this->instance.getM()));

        /* ∀ e ∈ E */
        for (const Edge & e : this->instance.getG().getEdges()) {
            unsigned int eId = this->instance.getG().getEdgeId(e);

            /* ∀ j ∈ {1, ..., m} */
            for (unsigned int j = 0; j < this->instance.getM(); j++) {
                unsigned int obj = this->instance.getC(eId, j);

                /* x_{e, j} ∈ {0, 1} */
                x[eId - 1][j] = model.addVar(0.0, 1.0, obj, GRB_BINARY, "x_" + std::to_string(eId -
                            1) + "_" + std::to_string(j));
            }
        }

        model.update();

        /* max{∑_{e ∈ E}{∑_{j = 1}^{m}{c_{e, j} * x_{e, j}}}} */
        model.set(GRB_IntAttr_ModelSense, GRB_MAXIMIZE);

        /* ∀ e ∈ E */
        for (const Edge & e : this->instance.getG().getEdges()) {
            unsigned int eId = this->instance.getG().getEdgeId(e);

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
             * 2 * ∑_{e ∈ E}{d_{e} * x_{e, j}} <= 
             * min{D, ((2 * (1 + B)) / m) * ∑_{e ∈ E}{d_{e}}
             */
            GRBLinExpr lhs2 = 0.0;

            for (const Edge & e : this->instance.getG().getEdges()) {
                unsigned int eId = this->instance.getG().getEdgeId(e);

                lhs2 += 2.0 * e.w * x[eId - 1][j];
            }

            model.addConstr(lhs2 <= this->instance.getMaximumDemand(), "c_2_" + 
                    std::to_string(j));
        }

        /* ∀ j ∈ {1, ..., m} */
        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            /* ∑_{e ∈ E}{d_{e} * x_{e, j}} >= ((2 * (1 - B)) / m) * ∑_{e ∈ E}{d_{e}} */
            GRBLinExpr lhs3 = 0.0;

            for (const Edge & e : this->instance.getG().getEdges()) {
                unsigned int eId = this->instance.getG().getEdgeId(e);

                lhs3 += 2.0 * e.w * x[eId - 1][j];
            }

            model.addConstr(lhs3 >= this->instance.getMinimumDemand(), "c_3_" + std::to_string(j));
        }

        unsigned int elapsedTime = this->getElapsedTime();
        unsigned int remainingTime = 0;

        if (this->timeLimit > elapsedTime) {
            remainingTime = this->timeLimit - elapsedTime;
        }

        BnCSolverCallback callback (this->instance, x);
        model.setCallback(&callback);

        model.set(GRB_DoubleParam_TimeLimit, ((double) remainingTime));
        model.set(GRB_IntParam_OutputFlag, 0);
        model.set(GRB_IntParam_LazyConstraints, 1);
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

