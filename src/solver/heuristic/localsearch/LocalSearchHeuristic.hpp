#pragma once

#include "../Heuristic.hpp"
#include "../../../solution/Solution.hpp"

/* The LocalSearchHeuristic represents a local search heuristic for the CEDP. */
class LocalSearchHeuristic : public Heuristic {
    public:
        /*
         * Constructs a new local search heuristic.
         *
         * @param instance the new local search heuristic's instance.
         * @param seed     the seed for the new local search heuristic's 
         *                 pseudo-random numbers generator.
         */
        LocalSearchHeuristic(const Instance & instance, unsigned int seed);

        /*
         * Constructs a new empty local search heuristic.
         */
        LocalSearchHeuristic();

        /*
         * Improves the specified solution.
         *
         * @param solution  the solution to be improved.
         * @param timeLimit the time limit.
         *
         * @return an improved solution.
         */
        Solution improveSolution(Solution solution, unsigned int timeLimit);
};

