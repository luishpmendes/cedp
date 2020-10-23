#pragma once

#include "../instance/Instance.hpp"
#include "../solution/Solution.hpp"
#include "heuristic/Heuristic.hpp"
#include <chrono>

/*
 * The CEDPSolver abstract class represents a solver for the CEDP.
 */
class CEDPSolver {
    protected:
        /* This solver's instance. */
        Instance instance;

        /* This solver's time limit in seconds. */
        unsigned int timeLimit;

        /* The seed for this solver's pseudo-random numbers generator. */
        unsigned int seed;

        /* This solver's start time. */
        std::chrono::steady_clock::time_point startTime;

        /* This solver's pseudo-random numbers generator. */
        std::mt19937 generator;

        /* This solver's solving time in seconds. */
        unsigned int solvingTime;

        /* Number of primal solutions found by this solver. */
        unsigned int solutionsCounter;

        /* This solver's best primal bound. */
        unsigned int bestPrimalBound;

        /* This solver's best dual bound. */
        double bestDualBound;

        /* This solver's best primal solution. */
        Solution bestPrimalSolution;

        /*
         * Returns this solver's elapsed time.
         *
         * @return this solver's elapsed time.
         */
        unsigned int getElapsedTime() const;

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
         */
        CEDPSolver(const Instance & instance, unsigned int timeLimit, unsigned int seed);

        /*
         * Constructs a new empty solver.
         */
        CEDPSolver();

        /*
         * Returns this solver's instance.
         *
         * @return this solver's instance.
         */
        Instance getInstance() const;

        /*
         * Returns this solver's solving time.
         *
         * @return this solver's solving time.
         */
        unsigned int getSolvingTime() const;

        /*
         * Returns the number of primal solutions found by this solver.
         *
         * @return the number of primal solutions found by this solver.
         */
        unsigned int getSolutionsCounter() const;

        /*
         * Returns this solver's best primal bound.
         *
         * @return this solver's best primal bound.
         */
        unsigned int getBestPrimalBound() const;

        /*
         * Returns this solver's best dual bound.
         *
         * @return this solver's best dual bound.
         */
        double getBestDualBound() const;

        /*
         * Returns this solver's best primal solution.
         *
         * @return this solver's best primal solution.
         */
        Solution getBestPrimalSolution() const;

        /*
         * Solve this solver's instance.
         */
        virtual void solve() = 0;

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

