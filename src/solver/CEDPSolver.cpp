#include "CEDPSolver.hpp"
#include <cfloat>
#include <climits>
#include <fstream>

/*
 * Constructs a new solver.
 *
 * @param instance  the new solver's instance.
 * @param timeLimit the new solver's time limit.
 * @param seed      the seed for the new solver's pseudo-random numbers generator.
 */
CEDPSolver::CEDPSolver(const Instance & instance,
                       unsigned int timeLimit,
                       unsigned int seed)
     : instance(instance), timeLimit(timeLimit), seed(seed), generator(seed),
       solvingTime(0), solutionsCounter(0), bestPrimalBound(0),
       bestDualBound(DBL_MAX), bestPrimalSolution(instance) {
    this->generator.discard(1000);
}

/*
 * Constructs a new empty solver.
 */
CEDPSolver::CEDPSolver() : CEDPSolver::CEDPSolver(Instance(), 0, 0) {}

/*
 * Returns this solver's elapsed time.
 *
 * @return this solver's elapsed time.
 */
unsigned int CEDPSolver::getElapsedTime() const {
    return Heuristic::getElapsedTime(this->startTime);
}

/*
 * Verifies whether this solver's termination criteria have been met.
 *
 * @return true if this solver's termination criteria have been met; false otherwise.
 */
bool CEDPSolver::areTerminationCriteriaMet() const {
    /* Verifies whether the time limit has been reached */
    if (this->getElapsedTime() >= this->timeLimit) {
        return true;
    }

    /* Verifies whether the primal bound and dual bound have converged */
    if (this->bestDualBound - ((double) this->bestPrimalBound) < 1.0) {
        return true;
    }

    return false;
}

/*
 * Returns this solver's instance.
 *
 * @return this solver's instance.
 */
Instance CEDPSolver::getInstance() const {
    return this->instance;
}

/*
 * Returns this solver's solving time.
 *
 * @return this solver's solving time.
 */
unsigned int CEDPSolver::getSolvingTime() const {
    return this->solvingTime;
}

/*
 * Returns the number of primal solutions found by this solver.
 *
 * @return the number of primal solutions found by this solver.
 */
unsigned int CEDPSolver::getSolutionsCounter() const {
    return this->solutionsCounter;
}

/*
 * Returns this solver's best primal bound.
 *
 * @return this solver's best primal bound.
 */
unsigned int CEDPSolver::getBestPrimalBound() const {
    return this->bestPrimalBound;
}

/*
 * Returns this solver's best dual bound.
 *
 * @return this solver's best dual bound.
 */
double CEDPSolver::getBestDualBound() const {
    return this->bestDualBound;
}

/*
 * Returns this solver's best primal solution.
 *
 * @return this solver's best primal solution.
 */
Solution CEDPSolver::getBestPrimalSolution() const {
    return bestPrimalSolution;
}

/*
 * Write this solver's statistics into the specified output stream.
 *
 * @param os the output stream to write into.
 */
void CEDPSolver::write(std::ostream & os) const {
    os << "m: " << this->instance.getM() << std::endl;
    os << "D: " << this->instance.getD() << std::endl;
    os << "B: " << this->instance.getB() << std::endl;
    os << "|V|: " << this->instance.getG().n() << std::endl;
    os << "|E|: " << this->instance.getG().m() << std::endl;
    os << "|U|: " << this->instance.getLG().n() << std::endl;
    os << "|A|: " << this->instance.getLG().m() << std::endl;
    os << "|U'|: " << this->instance.getGPrime().n() << std::endl;
    os << "|A'|: " << this->instance.getGPrime().m() << std::endl;
    os << "Maximum demand: " << this->instance.getMaximumDemand() << std::endl;
    os << "Time limit: " << this->timeLimit << "s" << std::endl;
    os << "Seed: " << this->seed << std::endl;
    os << "Solving time: " << this->solvingTime << "s" << std::endl;
    os << "Solutions found: " << this->solutionsCounter << std::endl;
    os << "Best primal bound: " << this->bestPrimalBound << std::endl;
    os << "Best dual bound: " << this->bestDualBound << std::endl;
    os << "Is solution feasible: " << this->bestPrimalSolution.isFeasible() << std::endl;
}

/*
 * Write this solver's statistics into the specified file.
 *
 * @param filename the file to write into.
 */
void CEDPSolver::write(const char * filename) const {
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
void CEDPSolver::write(const std::string & filename) const {
    this->write(filename.c_str());
}

/*
 * Write this solver's statistics into the standard output stream.
 */
void CEDPSolver::write() const {
    this->write(std::cout);
}

