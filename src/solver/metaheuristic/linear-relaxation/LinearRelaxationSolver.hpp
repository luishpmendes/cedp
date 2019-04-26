#pragma once

#include "../../CEDPSolver.hpp"

/*
 * The LinearRelaxationSolver class represents a solver for the CEDP using 
 * the linear relaxation method.
 */
class LinearRelaxationSolver : public CEDPSolver {
    public:
        /*
         * Constructs a new solver.
         *
         * @param instance  the new solver's instance.
         * @param timeLimit the new solver's time limit.
         * @param seed      the seed for the new solver's pseudo-random numbers generator.
         */
        LinearRelaxationSolver(const Instance & instance, 
                unsigned int timeLimit, unsigned int seed);

        /*
         * Constructs a new empty solver.
         */
        LinearRelaxationSolver();

        /*
         * Solve this solver's instance.
         */
        void solve();
};

