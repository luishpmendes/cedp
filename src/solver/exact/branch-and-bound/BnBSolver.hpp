#pragma once

#include "../../CEDPSolver.hpp"

/*
 * The BnBSolver class represents a solver for the CEDP using the Branch-and-Bound method.
 */
class BnBSolver : public CEDPSolver {
    public:
        /*
         * Constructs a new solver.
         *
         * @param instance  the new solver's instance.
         * @param timeLimit the new solver's time limit.
         * @param seed      the seed for the new solver's pseudo-random numbers generator.
         */
        BnBSolver(const Instance & instance, unsigned int timeLimit, unsigned int seed);

        /*
         * Constructs a new empty solver.
         */
        BnBSolver();

        /*
         * Solve this solver's instance.
         */
        void solve();
};

