#include "Heuristic.hpp"

/*
 * Constructs a new heuristic.
 *
 * @param instance the new heuristic's instance.
 * @param seed     the seed for the new heuristic's pseudo-random numbers generator.
 */
Heuristic::Heuristic(const Instance & instance, unsigned int seed) : 
    instance(instance), generator(seed) {}

/*
 * Constructs a new empty heuristic.
 */
Heuristic::Heuristic() : Heuristic::Heuristic(Instance(), 0) {}

/*
 * Returns the elapsed time.
 *
 * @param startTime the start time.
 *
 * @return the elapsed time.
 */
unsigned int Heuristic::getElapsedTime(
        const std::chrono::steady_clock::time_point & startTime) {
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::seconds elapsedTime = 
        std::chrono::duration_cast<std::chrono::seconds> (currentTime - 
                startTime);
    return elapsedTime.count();
}

