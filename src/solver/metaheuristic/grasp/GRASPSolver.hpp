#pragma once

#include "../../CEDPSolver.hpp"
#include "../../heuristic/constructive/GreedyConstructiveHeuristic.hpp"
#include "../../heuristic/fixer/SolutionFixer.hpp"
#include "../../heuristic/localsearch/LocalSearchHeuristic.hpp"
#include "../../../statistics/Statistics.hpp"

/*
 * The GRASPSolver class represents a solver for the CEDP using the Greedy 
 * Randomized Adaptive Search Procedure method.
 */
class GRASPSolver : public CEDPSolver {
    private:
        /* This solver's greedy constructive heuristic. */
        GreedyConstructiveHeuristic gcHeuristic;

        /* This solver's local search heuristic. */
        LocalSearchHeuristic lsHeuristic;

        /*
         * The number of values for this solver's threshold parameter.
         */
        unsigned int m;

        /*
         * The number of iterations between each update in this solver's 
         * threshold parameter probabilities.
         */
        unsigned int k;

        /*
         * The set of possible values for α.
         */
        std::vector<double> psi;

        /*
         * The probabilities associated with each value for α.
         */
        std::vector<double> p;

        /*
         * The statistics of the solution's values found using each value for α.
         */
        std::vector<Statistics> primalBoundStatisticsPerAlpha;

        /* 
         * The statistics of the ratio between initial and local search solutions value.
         */
        Statistics ratioStatistics;

        /*
         * This solver's iterations counter.
         */
        unsigned int iterationsCounter;

        /*
         * The iteration when this solver found the first solution.
         */
        unsigned int firstSolutionIteration;

        /*
         * The time in seconds when this solver found the first solution.
         */
        unsigned int firstSolutionTime;

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
         * This solver's counter of local search.
         */
        unsigned int localSearchCounter;

        /*
         * Randomly selects a value for α.
         *
         * @return the index of the selected value for α.
         */
        unsigned int chooseAlpha();

        /*
         * Updated the average solution value found by each value for α.
         *
         * @param i the index of the selected value for α.
         * @param primalBound the new primal bound.
         */
        void updateAverageSolutionValuePerAlpha(unsigned int i, 
                double primalBound);

        /*
         * Reevaluate the probabilities associated with each value for α.
         */
        void reevalueateProbabilities();

    public:
        /*
         * Constructs a new solver.
         *
         * @param instance  the new solver's instance.
         * @param timeLimit the new solver's time limit.
         * @param seed      the seed for the new solver's pseudo-random 
         *                  numbers generator.
         * @param m         the number of values for the new solver's 
         *                  threshold parameter.
         * @param k         the number of iterations between each update in 
         *                  the new solver's threshdold probabilities.
         */
        GRASPSolver(const Instance & instance, unsigned int timeLimit, 
                unsigned int seed, unsigned int m, unsigned int k);

        /*
         * Constructs a new empty solver.
         */
        GRASPSolver();

        /*
         * Returns the number of values for this solver's threshold parameter.
         *
         * @return the number of values for this solver's threshold parameter.
         */
        unsigned int getM() const;

        /*
         * Returns the number of iterations between each update in this 
         * solver's threshold parameter.
         *
         * @return the number of iterations between each update in this
         *         solver's threshold parameter.
         */
        unsigned int getK() const;

        /*
         * Returns the i-th possible value for alpha.
         *
         * @param i the index of the desired value.
         *
         * @return the i-th possible value for alpha.
         */
        double getAlpha(unsigned int i) const;

        /*
         * Returns the probability associated with the i-th possible value for alpha.
         *
         * @param i the index of the desired value.
         *
         * @return the probability associated with the i-th possible value for alpha.
         */
        double getP(unsigned int i) const;

        /*
         * Returns the statistics of the solution's values found using the 
         * i-th possible value for alpha.
         *
         * @param i the index of the desired value.
         *
         * @return the statistics of the solution's values found using the
         *         i-th possible value for alpha.
         */
        Statistics getPrimalBoundStatictics(unsigned int i) const;

        /*
         * Returns the statistics of the ratio between initial and local search solutions value.
         *
         * @return the statistics of the ratio between initial and local search solutions value.
         */
        Statistics getRatioStatistics() const;

        /*
         * Returns this solver's iterations counter.
         *
         * @return this solver's iterations counter.
         */
        unsigned int getIterationsCounter() const;

        /*
         * Returns the iteration when this solver found the first solution.
         *
         * @return the iteration when this solver found the first solution.
         */
        unsigned int getFirstSolutionIteration() const;

        /*
         * Returns the time in seconds when this solver found the first solution.
         *
         * @return the time in seconds when this solver found the first solution.
         */
        unsigned int getFirstSolutionTime() const;

        /*
         * Returns the iteration when this solver found the best solution.
         *
         * @return the iteration when this solver found the best solution.
         */
        unsigned int getBestSolutionIteration() const;

        /*
         * Returns the time in seconds when this solver found the best solution.
         *
         * @return the time in seconds when this solver found the best solution.
         */
        unsigned int getBestSolutionTime() const;

        /*
         * Returns this solver's counter of solutions that are not edge partition.
         *
         * @return this solver's counter of solutions that are not edge partition.
         */
        unsigned int getNotPartitionSolutionsCounter() const;

        /*
         * Returns this solver's counter of solutions that are not connected.
         *
         * @return this solver's counter of solutions that are not connected.
         */
        unsigned int getNotConnectedSolutionsCounter() const;

        /*
         * Returns this solver's counter of solutions that do not respects the capacity.
         *
         * @return this solver's counter of solutions that do not respects the capacity.
         */
        unsigned int getNotRespectsCapacitySolutionsCounter() const;

        /*
         * Returns this solver's counter of solutions that are not balanced.
         *
         * @return this solver's counter of solutions that are not balanced.
         */
        unsigned int getNotBalancedSolutionsCounter() const;

        /*
         * Returns this solver's counter of solutions that are not feasible.
         *
         * @return this solver's counter of solutions that are not feasible.
         */
        unsigned int getNotFeasibleSolutionsCounter() const;

        /*
         * Returns this solver's counter of solutions that were fixed.
         *
         * @return this solver's counter of solutions that were fixed.
         */
        unsigned int getFixedSolutionsCounter() const;

        /*
         * Returns this solver's counter of local search.
         *
         * @return this solver's counter of local search.
         */
        unsigned int getLocalSearchCounter() const;

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

