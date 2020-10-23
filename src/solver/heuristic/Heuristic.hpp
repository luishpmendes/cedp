#pragma once

#include "../../instance/Instance.hpp"
#include <chrono>

/* The Heuristic abstract class represents a heuristic for the CEDP. */
class Heuristic {
    protected:
        /* This heuristic's instance. */
        Instance instance;

        /* This heuristic's pseudo-random numbers generator. */
        std::mt19937 generator;
    public:
        /*
         * Constructs a new heuristic.
         *
         * @param instance the new heuristic's instance.
         * @param seed     the seed for the new heuristic's pseudo-random numbers generator.
         */
        Heuristic(const Instance & instance, unsigned int seed);

        /*
         * Constructs a new empty heuristic.
         */
        Heuristic();

        /*
         * Returns the elapsed time.
         *
         * @param startTime the start time.
         *
         * @return the elapsed time.
         */
        static unsigned int getElapsedTime(
                const std::chrono::steady_clock::time_point & startTime);
};

