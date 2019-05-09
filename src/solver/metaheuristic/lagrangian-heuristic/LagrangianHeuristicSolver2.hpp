#pragma once

#include "../../CEDPSolver.hpp"
#include "gurobi_c++.h"

class LagrangianHeuristicSolver2 : public CEDPSolver {
    private:
        /*
         * This solver's Gurobi environment.
         */
        GRBEnv * env;

        /*
         * This solver's iterations counter.
         */
        unsigned int iterationsCounter;

        /*
         * The iteration when this solver found the best solution.
         */
        unsigned int bestSolutionIteration;

        /*
         * The time in seconds when this solver found the best solution.
         */
        unsigned int bestSolutionTime;

        /*
         * This solver's counter of solutions that are not edge partition.
         */
        unsigned int notPartitionSolutionsCounter;

        /*
         * This solver's counter of solutions that are not connected.
         */
        unsigned int notConnectedSolutionsCounter;

        /*
         * This solver's counter of solutions that do not respects the capacity.
         */
        unsigned int notRespectsCapacitySolutionsCounter;

        /*
         * This solver's counter of solutions that are not balanced.
         */
        unsigned int notBalancedSolutionsCounter;

        /*
         * This solver's counter of solutions that are not feasible.
         */
        unsigned int notFeasibleSolutionsCounter;

        /*
         * This solver's counter of solutions that were fixed.
         */
        unsigned int fixedSolutionsCounter;

        /*
         * This solver's π updating parameter.
         */
        unsigned int N;

        /*
         * This solver's π parameter.
         */
        double PI;

        /*
         * This solver's Lagrangian multipliers for the 4th set of constraints.
         * λ^{1}_{j} ∈ ℝ, ∀ j ∈ {1, ..., m}
         */
        std::vector<double> lambda1;

        /*
         * This solver's Lagrangian multipliers for the 5th set of constraints.
         * λ^{2} ∈ ℝ
         */
        double lambda2;

        /*
         * This solver's Lagrangian multipliers for the 6th set of constraints.
         * λ^{3}_{e, j} ∈ ℝ ^{+}, ∀ e ∈ U, j ∈ {1, ..., m}
         */
        std::vector<std::vector<double> > lambda3;

        /*
         * This solver's Lagrangian multipliers for the 7th set of constraints.
         * λ^{4}_{{e, f}, j} ∈ ℝ ^{+}, ∀ {e, f} ∈ A, j ∈ {1, ..., m}
         */
        std::vector<std::vector<double> > lambda4;

        /*
         * This solver's Lagrangian multipliers for the 8th set of constraints.
         * λ^{5}_{{e, f}, j} ∈ ℝ ^{+}, ∀ {e, f} ∈ A, j ∈ {1, ..., m}
         */
        std::vector<std::vector<double> > lambda5;

        /*
         * This solver's Lagrangian multipliers for the 9th set of constraints.
         * λ^{6}_{e, j} ∈ ℝ ^{+}, ∀ e ∈ U, j ∈ {1, ..., m}
         */
        std::vector<std::vector<double> > lambda6;

        /*
         * This solver's current solution.
         */
        Solution currentSolution;

        /*
         * This solver's x value for the current dual solution.
         */
        std::vector<std::vector<bool> > x;

        /*
         * This solver's y value for the current dual solution.
         */
        std::vector<std::vector<bool> > y;

        /*
         * This solver's z value for the current dual solution.
         */
        std::vector<std::vector<double> > z;

        /*
         * This solver's subgradients for λ^{1}.
         */
        std::vector<double> subgradient1;

        /*
         * This solver's subgradients for λ^{2}.
         */
        double subgradient2;

        /*
         * This solver's subgradients for λ^{3}.
         */
        std::vector<std::vector<double> > subgradient3;

        /*
         * This solver's subgradients for λ^{4}.
         */
        std::vector<std::vector<double> > subgradient4;

        /*
         * This solver's subgradients for λ^{5}.
         */
        std::vector<std::vector<double> > subgradient5;

        /*
         * This solver's subgradients for λ^{6}.
         */
        std::vector<std::vector<double> > subgradient6;

        /*
         * This solver's subgradient method step size.
         */
        double T;

        /*
         * Solve the first Lagrangian relaxation subproblem with the current set of multipliers.
         *
         * @param cTilde the Lagrangian costs.
         *
         * @return the optimal value of the first Lagrangian relaxation 
         *         subproblem with the current set of multipliers.
         */
        double solveLagrangianRelaxationSubproblem1(
                const std::vector<std::vector<double> > & cTilde);

        /*
         * Solve the second Lagrangian relaxation subproblem with the current set of multipliers.
         *
         * @return the optimal value of the second Lagrangian relaxation 
         *         subproblem with the current set of multipliers.
         */
        double solveLagrangianRelaxationSubproblem2();

        /*
         * Solve the Lagrangian relaxation subproblem with the current set of multipliers.
         *
         * @return the optimal value of the Lagrangian relaxation subproblem 
         *         with the current set of multipliers.
         */
        double solveLagrangianRelaxationSubproblem();

        /*
         * Define subgradients for the relaxed constraints.
         */
        void defineSubgradients();

        /*
         * Define a step size T.
         */
        void defineStepSize();

        /*
         * Update the Lagrangian multipliers.
         */
        void updateLagrangianMultipliers();

        /*
         * Verifies whether this solver's termination criteria have been met.
         *
         * @return true if this solver's termination criteria have been met; false otherwise.
         */
        bool areTerminationCriteriaMet() const;

    public:
        /*
         * Constructs a new solver.
         *
         * @param instance  the new solver's instance.
         * @param timeLimit the new solver's time limit.
         * @param seed      the seed for the new solver's pseudo-random numbers generator.
         * @param N         the new solver's π updating parameter.
         */
        LagrangianHeuristicSolver2(const Instance & instance, 
                unsigned int timeLimit, unsigned int seed, unsigned int N);

        /*
         * Constructs a new empty solver.
         */
        LagrangianHeuristicSolver2();

        /*
         * Returns this solver's π updating parameter.
         *
         * @return this solver's π updating parameter.
         */
        unsigned int getN();

        /*
         * Solve this solver's instance.
         */
        void solve();

        /*
         * Write this solver's statistics into the specified output stream.
         *
         * @param os the output stream to write into.
         */
        void write(std::ostream & os) const;

        /*
         * Write this solver's statistics into the specified file.
         *
         * @param filename the file to write into.
         */
        void write(const char * filename) const;

        /*
         * Write this solver's statistics into the specified file.
         *
         * @param filename the file to write into.
         */
        void write(const std::string & filename) const;

        /*
         * Write this solver's statistics into the standard output stream.
         */
        void write() const;
};

