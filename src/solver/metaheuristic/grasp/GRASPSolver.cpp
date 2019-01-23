#include "GRASPSolver.hpp"
#include <fstream>

/*
 * Constructs a new solver.
 *
 * @param instance  the new solver's instance.
 * @param timeLimit the new solver's time limit.
 * @param seed      the seed for the new solver's pseudo-random numbers 
 *                  generator.
 * @param m         the number of values for the new solver's threshold 
 *                  parameter.
 * @param k         the number of iterations between each update in the new 
 *                  solver's threshold parameter probabilities.
 */
GRASPSolver::GRASPSolver(const Instance & instance, unsigned int timeLimit, 
        unsigned int seed, unsigned int m, unsigned int k) : 
    CEDPSolver::CEDPSolver(instance, timeLimit, seed), m(m), k(k) {
    this->gcHeuristic = GreedyConstructiveHeuristic(this->instance, seed);
}

/*
 * Constructs a new empty solver.
 */
GRASPSolver::GRASPSolver() : CEDPSolver::CEDPSolver() {}


/*
 * Returns the number of values for this solver's threshold parameter.
 *
 * @return the number of values for this solver's threshold parameter.
 */
unsigned int GRASPSolver::getM() const {
    return this->m;
}

/*
 * Returns the number of iterations between each update in this solver's threshold parameter.
 *
 * @return the number of iterations between each update in this solver's threshold parameter.
 */
unsigned int GRASPSolver::getK() const {
    return this->k;
}

/*
 * Returns the i-th possible value for alpha.
 *
 * @param i the index of the desired value.
 *
 * @return the i-th possible value for alpha.
 */
double GRASPSolver::getAlpha(unsigned int i) const {
    if (i < this->psi.size()) {
        return this->psi[i];
    }

    return 0.0;
}

/*
 * Returns the probability associated with the i-th possible value for alpha.
 *
 * @param i the index of the desired value.
 *
 * @return the probability associated with the i-th possible value for alpha.
 */
double GRASPSolver::getP(unsigned int i) const {
    if (i < this->p.size()) {
        return this->p[i];
    }

    return 0.0;
}

/*
 * Returns the statistics of the solution's values found using the i-th 
 * possible value for alpha.
 *
 * @param i the index of the desired value.
 *
 * @return the statistics of the solution's values found using the i-th 
 *         possible value for alpha.
 */
Statistics GRASPSolver::getPrimalBoundStatictics(unsigned int i) const {
    if (i < this->primalBoundStatisticsPerAlpha.size()) {
        return this->primalBoundStatisticsPerAlpha[i];
    }

    return Statistics();
}

/*
 * Returns the statistics of the ratio between initial and local search solutions value.
 *
 * @return the statistics of the ratio between initial and local search solutions value.
 */
Statistics GRASPSolver::getRatioStatistics() const {
    return this->ratioStatistics;
}

/*
 * Returns this solver's iterations counter.
 *
 * @return this solver's iterations counter.
 */
unsigned int GRASPSolver::getIterationsCounter() const {
    return this->iterationsCounter;
}

/*
 * Returns the iteration when this solver found the first solution.
 *
 * @return the iteration when this solver found the first solution.
 */
unsigned int GRASPSolver::getFirstSolutionIteration() const {
    return this->firstSolutionIteration;
}

/*
 * Returns the time in seconds when this solver found the first solution.
 *
 * @return the time in seconds when this solver found the first solution.
 */
unsigned int GRASPSolver::getFirstSolutionTime() const {
    return this->firstSolutionTime;
}

/*
 * Returns the iteration when this solver found the best solution.
 *
 * @return the iteration when this solver found the best solution.
 */
unsigned int GRASPSolver::getBestSolutionIteration() const {
    return this->bestSolutionIteration;
}

/*
 * Returns the time in seconds when this solver found the best solution.
 *
 * @return the time in seconds when this solver found the best solution.
 */
unsigned int GRASPSolver::getBestSolutionTime() const {
    return this->bestSolutionTime;
}

/*
 * Returns this solver's counter of solutions that are not edge partition.
 *
 * @return this solver's counter of solutions that are not edge partition.
 */
unsigned int GRASPSolver::getNotPartitionSolutionsCounter() const {
    return this->notPartitionSolutionsCounter;
}

/*
 * Returns this solver's counter of solutions that are not connected.
 *
 * @return this solver's counter of solutions that are not connected.
 */
unsigned int GRASPSolver::getNotConnectedSolutionsCounter() const {
    return this->notConnectedSolutionsCounter;
}

/*
 * Returns this solver's counter of solutions that do not respects the capacity.
 *
 * @return this solver's counter of solutions that do not respects the capacity.
 */
unsigned int GRASPSolver::getNotRespectsCapacitySolutionsCounter() const {
    return this->notRespectsCapacitySolutionsCounter;
}

/*
 * Returns this solver's counter of solutions that are not balanced.
 *
 * @return this solver's counter of solutions that are not balanced.
 */
unsigned int GRASPSolver::getNotBalancedSolutionsCounter() const {
    return this->notBalancedSolutionsCounter;
}

/*
 * Returns this solver's counter of solutions that are not feasible.
 *
 * @return this solver's counter of solutions that are not feasible.
 */
unsigned int GRASPSolver::getNotFeasibleSolutionsCounter() const {
    return this->notFeasibleSolutionsCounter;
}

/*
 * Returns this solver's counter of solutions that were fixed.
 *
 * @return this solver's counter of solutions that were fixed.
 */
unsigned int GRASPSolver::getFixedSolutionsCounter() const {
    return this->fixedSolutionsCounter;
}

/*
 * Returns this solver's counter of local search.
 *
 * @return this solver's counter of local search.
 */
unsigned int GRASPSolver::getLocalSearchCounter() const {
    return this->localSearchCounter;
}

/*
 * Randomly selects a value for α.
 *
 * @return the index of the selected value for α.
 */
unsigned int GRASPSolver::chooseAlpha() {
    unsigned int i = 0;

    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    double randP = distribution(this->generator);
    double sumP = 0;
    
    while (i < this->m && sumP + this->p[i] < randP) {
        sumP += this->p[i];
        i++;
    }

    return i;
}

/*
 * Reevaluate the probabilities associated with each value for α.
 */
void GRASPSolver::reevalueateProbabilities() {
    std::vector<double> q (this->m);
    double sumQ = 0;

    for (unsigned int j = 0; j < this->m; j++) {
        q[j] = this->primalBoundStatisticsPerAlpha[j].getMean() / 
            this->bestPrimalBound;
        sumQ += q[j];
    }

    for (unsigned int j = 0; j < this->m; j++) {
        this->p[j] = q[j]/sumQ;
    }
}

/*
 * Solve this solver's instance.
 */
void GRASPSolver::solve() {
    this->startTime = std::chrono::steady_clock::now();

    this->psi = std::vector<double> (this->m);
    this->p = std::vector<double> (this->m, 1.0/((double) this->m));
    this->primalBoundStatisticsPerAlpha = std::vector<Statistics>(this->m);

    this->firstSolutionIteration = 0;
    this->firstSolutionTime = 0;
    this->bestSolutionIteration = 0;
    this->bestSolutionTime = 0;
    this->notPartitionSolutionsCounter = 0;
    this->notConnectedSolutionsCounter = 0;
    this->notRespectsCapacitySolutionsCounter = 0;
    this->notBalancedSolutionsCounter = 0;
    this->notFeasibleSolutionsCounter = 0;
    this->fixedSolutionsCounter = 0;
    this->localSearchCounter = 0;

    for (unsigned int i = 0; i < this->m; i++) {
        this->psi[i] = ((double) (i + 1))/((double) this->m);
    }

    this->ratioStatistics = Statistics();

    /* while termination criteria are not met */
    for (this->iterationsCounter = 1; !this->areTerminationCriteriaMet(); 
            this->iterationsCounter++) {
        unsigned int elapsedTime = this->getElapsedTime();
        unsigned int remainingTime = 0;

        if (this->timeLimit > elapsedTime) {
            remainingTime = this->timeLimit - elapsedTime;
        }

        unsigned int i = this->chooseAlpha();

        this->gcHeuristic.setAlpha(this->psi[i]);

        /* ℰ' ← Constructive-Heuristic(m, D, B, G, d, c) */
        Solution solution = this->gcHeuristic.constructSolution(remainingTime);

        bool isFeasible = true;

        if (!solution.isPartition()) {
            isFeasible = false;
            this->notPartitionSolutionsCounter++;
        }

        if (!solution.isConnected()) {
            isFeasible = false;
            this->notConnectedSolutionsCounter++;
        }

        if (!solution.respectsCapacity()) {
            isFeasible = false;
            this->notRespectsCapacitySolutionsCounter++;
        }

        if (!solution.isBalanced()) {
            isFeasible = false;
            this->notBalancedSolutionsCounter++;
        }

        /* if ℰ' is not a feasible solution */
        if (!isFeasible) {
            this->notFeasibleSolutionsCounter++;
            elapsedTime = this->getElapsedTime();
            remainingTime = 0;

            if (this->timeLimit > elapsedTime) {
                remainingTime = this->timeLimit - elapsedTime;
            }

            /* ℰ' ← Fix-Solution(m, D, B, G, d, c, ℰ') */
            solution = SolutionFixer::fixSolution(solution, remainingTime);
        }

        /* if ℰ' is a feasible solution */
        if (solution.isFeasible()) {
            this->solutionsCounter++;

            if (!isFeasible) {
                this->fixedSolutionsCounter++;
            }

            double primalBound = solution.getValue();

            if (this->solutionsCounter <= k || primalBound >= 
                    (this->ratioStatistics.getMean() - 2.0 * 
                     this->ratioStatistics.getStandardDeviation()) * 
                    this->bestPrimalBound) {
                elapsedTime = this->getElapsedTime();
                remainingTime = 0;

                if (this->timeLimit > elapsedTime) {
                    remainingTime = this->timeLimit - elapsedTime;
                }

                /* ℰ' ← Local-Search-Heuristic(m, D, B, G, d, c, ℰ') */
                solution = this->lsHeuristic.improveSolution(solution, 
                        remainingTime);
                this->localSearchCounter++;
                double newPrimalBound = solution.getValue();

                double ratio = primalBound / newPrimalBound;

                this->ratioStatistics.addValue(ratio);

                primalBound = newPrimalBound;
            }

            if (this->solutionsCounter == 1) {
                this->firstSolutionIteration = this->iterationsCounter;
                this->firstSolutionTime = this->getElapsedTime();
            }

            /* 
             * if ℰ = ∅ 
             * || ∑_{j = 1}^{m}{∑_{e ∈ E_{j}}{c_{e, j}}} 
             * < ∑_{j = 1}^{m}{∑_{e ∈ E'_{j}}{c_{e, j}}} 
             */
            if (this->bestPrimalBound < primalBound) {
                /* ℰ ← ℰ' */
                this->bestPrimalBound = primalBound;
                this->bestPrimalSolution = solution;
                this->bestSolutionIteration = this->iterationsCounter;
                this->bestSolutionTime = this->getElapsedTime();
            }

            this->primalBoundStatisticsPerAlpha[i].addValue(primalBound);
        }

        if (this->solutionsCounter % this->k == 0 && 
                this->solutionsCounter > 0) {
            this->reevalueateProbabilities();
        }
    }

    this->solvingTime = this->getElapsedTime();
}

/*
 * Write this solver's statistics into the specified output stream.
 *
 * @param os the output stream to write into.
 */
void GRASPSolver::write(std::ostream & os) const {
    CEDPSolver::write(os);
    os << "Total iterations: " << this->iterationsCounter << std::endl;
    os << "First solution iteration: " << this->firstSolutionIteration << std::endl;
    os << "First solution time: " << this->firstSolutionTime << std::endl;
    os << "Best solution iteration: " << this->bestSolutionIteration << std::endl;
    os << "Best solution time: " << this->bestSolutionTime << std::endl;
    os << "Solutions that are not partition: " << 
        this->notPartitionSolutionsCounter << std::endl;
    os << "Solutions that are not connected: " << 
        this->notConnectedSolutionsCounter << std::endl;
    os << "Solutions that do not respects the capacity: " << 
        this->notRespectsCapacitySolutionsCounter << std::endl;
    os << "Solutions that are not balanced: " << this->notBalancedSolutionsCounter << std::endl;
    os << "Solutions that are not feasible: " << this->notFeasibleSolutionsCounter << std::endl;
    os << "Solutions that were fixed: " << this->fixedSolutionsCounter << std::endl;
    os << "Local search counter: " << this->localSearchCounter << std::endl;
}

/*
 * Write this solver's statistics into the specified file.
 *
 * @param filename the file to write into.
 */
void GRASPSolver::write(const char * filename) const {
    std::ofstream ofs;
    ofs.open(filename);

    if (ofs.is_open()) {
        this->write(ofs);
        ofs.close();
    } else {
        throw "File not created.";
    }
}

/*
 * Write this solver's statistics into the specified file.
 *
 * @param filename the file to write into.
 */
void GRASPSolver::write(const std::string & filename) const {
    this->write(filename.c_str());
}

/*
 * Write this solver's statistics into the standard output stream.
 */
void GRASPSolver::write() const {
    this->write(std::cout);
}

