#pragma once

#include "../Heuristic.hpp"
#include "../../../solution/Solution.hpp"

/* 
 * The GreedyConstructiveHeuristic represents a constructive heuristic for 
 * the CEDP.
 */
class GreedyConstructiveHeuristic : public Heuristic {
    private:
        /*
         * This constructive heuristic's threshold parameter for the 
         * restricted candidate list in the interval [0, 1].
         */
        double alpha;
    public:
        /*
         * Constructs a new constructive heuristic.
         *
         * @param instance the new constructive heuristic's instance.
         * @param seed     the seed for the new constructive heuristic's 
         *                 pseudo-random numbers generator.
         * @param alpha    the new constructive heuristic's threshold 
         *                 parameter.
         */
        GreedyConstructiveHeuristic(const Instance & instance, 
                unsigned int seed, double alpha);

        /*
         * Constructs a new constructive heuristic.
         *
         * @param instance the new constructive heuristic's instance.
         * @param seed     the seed for the new constructive heuristic's 
         *                 pseudo-random numbers generator.
         */
        GreedyConstructiveHeuristic(const Instance & instance, 
                unsigned int seed);

        /*
         * Constructs a new empty constructive heuristic.
         */
        GreedyConstructiveHeuristic();

        /*
         * Returns this constructive heuristic's threshold parameter for the 
         * restricted candidate list.
         *
         * @return this constructive heuristic's threshold parameter for the 
         *         restricted candidate list.
         */
        double getAlpha();

        /*
         * Sets this constructive heuristic's threshold parameter for the 
         * restricted candidate list.
         *
         * @param alpha this constructive heuristic's new threshold parameters
         *              for the restricted candidate list.
         */
        void setAlpha(double alpha);

        /*
         * Constructs a solution for this heuristics instance.
         *
         * @param timeLimit the time limit.
         *
         * @return a solution for this heuristics instance.
         */
        Solution constructSolution(unsigned int timeLimit);
};

