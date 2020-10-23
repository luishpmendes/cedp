#pragma once

#include "../../CEDPSolver.hpp"

/*
 * The BnCSolver class represents a solver for the CEDP using the Branch-and-Cut method.
 */
class BnCSolver : public CEDPSolver {
    private:
        /*
         * The percentage of time to find a warm start solution.
         */
        double warmStartPercentageTime;

        /*
         * The number of values for the GRASP's threshold parameter.
         */
        unsigned int m;

        /*
         * The number of iterations between each update in the GRASP's 
         * threshold parameter probabilities.
         */
        unsigned int k;
        
    public:
        /*
         * Constructs a new solver.
         *
         * @param instance                the new solver's instance.
         * @param timeLimit               the new solver's time limit.
         * @param seed                    the seed for the new solver's
         *                                pseudo-random numbers generator.
         * @param warmStartPercentageTime the percentage of time to find a warm
         *                                start solution.
         * @param m                       the number of values for the GRASP's
         *                                threshold parameter.
         * @param k                       The number of iterations between each
         *                                update in the GRASP's threshold
         *                                parameter probabilities.
         */
        BnCSolver(const Instance & instance,
                  unsigned int timeLimit,
                  unsigned int seed,
                  double warmStartPercentageTime,
                  unsigned int m,
                  unsigned int k);

        /*
         * Constructs a new empty solver.
         */
        BnCSolver();

        /*
         * Returns the percentage of time to find a warm start solution.
         *
         * @return the percentage of time to find a warm start solution.
         */
        double getWarmStartPercentageTime() const;

        /*
         * Returns the number of values for the GRASP's threshold parameter.
         *
         * @return the number of values for the GRASP's threshold parameter.
         */
        unsigned int getM() const;

        /*
         * Returns the number of iterations between each update in the 
         * GRASP's threshold parameter.
         *
         * @return the number of iterations between each update in the
         *         GRASP's threshold parameter.
         */
        unsigned int getK() const;

        /*
         * Solve this solver's instance.
         */
        void solve();
};

