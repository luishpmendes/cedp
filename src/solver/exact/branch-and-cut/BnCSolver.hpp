#pragma once

#include "../../CEDPSolver.hpp"

/*
 * The BnCSolver class represents a solver for the CEDP using the Branch-and-Cut method.
 */
class BnCSolver : public CEDPSolver {
    public:
        /*
         * Constructs a new solver.
         *
         * @param instance  the new solver's instance.
         * @param timeLimit the new solver's time limit.
         * @param seed      the seed for the new solver's pseudo-random numbers generator.
         */
        BnCSolver(const Instance & instance, unsigned int timeLimit, unsigned int seed);

        /*
         * Constructs a new empty solver.
         */
        BnCSolver();

        /*
         * Solve this solver's instance.
         */
        void solve();
};

