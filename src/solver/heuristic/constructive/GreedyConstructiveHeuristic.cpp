#include "GreedyConstructiveHeuristic.hpp"
#include <climits>

/*
 * Constructs a new constructive heuristic.
 *
 * @param instance the new constructive heuristic's instance.
 * @param seed     the seed for the new constructive heuristic's pseudo-random 
 *                 numbers generator.
 * @param alpha    the new constructive heuristic's threshold parameter.
 */
GreedyConstructiveHeuristic::GreedyConstructiveHeuristic(
        const Instance & instance, unsigned int seed, double alpha) : 
    Heuristic::Heuristic(instance, seed), alpha(alpha) {}

/*
 * Constructs a new constructive heuristic.
 *
 * @param instance the new constructive heuristic's instance.
 * @param seed     the seed for the new constructive heuristic's pseudo-random 
 *                 numbers generator.
 */
GreedyConstructiveHeuristic::GreedyConstructiveHeuristic(
        const Instance & instance, unsigned int seed) : 
    GreedyConstructiveHeuristic::GreedyConstructiveHeuristic(instance, seed, 
            0.0) {}

/*
 * Constructs a new empty constructive heuristic.
 */
GreedyConstructiveHeuristic::GreedyConstructiveHeuristic() : 
    Heuristic::Heuristic(), alpha(0.0) {}

/*
 * Returns this constructive heuristic's threshold parameter for the restricted candidate list.
 *
 * @return this constructive heuristic's threshold parameter for the restricted candidate list.
 */
double GreedyConstructiveHeuristic::getAlpha() {
    return this->alpha;
}

/*
 * Sets this constructive heuristic's threshold parameter for the restricted 
 * candidate list.
 *
 * @param alpha this constructive heuristic's new threshold parameters for 
 *              the restricted candidate list.
 */
void GreedyConstructiveHeuristic::setAlpha(double alpha) {
    this->alpha = alpha;
}

/*
 * Constructs a solution for this heuristics instance.
 *
 * @param timeLimit the time limit.
 *
 * @return a solution for this heuristics instance.
 */
Solution GreedyConstructiveHeuristic::constructSolution(unsigned int timeLimit) {
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    std::vector<std::set<Edge> > districts (this->instance.getM());
    std::vector<double> districtsDemand (this->instance.getM(), 0.0);
    std::vector<unsigned int> edgesDistrict (this->instance.getG().m(), this->instance.getM());
    std::vector<std::set<Edge> > edgesAdjacentEdges (this->instance.getG().m());
    std::set<Edge> unallocatedEdges = this->instance.getG().getEdges();
    std::vector<std::set<Edge> > districtsUnallocatedAdjacentEdges (this->instance.getM());
    std::set<unsigned int> emptyDistricts;
    double maxDemand = this->instance.getMaximumDemand();
    double minDemand = this->instance.getMinimumDemand();

    for (const Edge & e : this->instance.getG().getEdges()) {
        unsigned int eId = this->instance.getG().getEdgeId(e);

        edgesAdjacentEdges[eId - 1] = this->instance.getG().getAdjacentEdges(e);
    }

    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        emptyDistricts.insert(j);
    }

    /* while E \ ∪_{j = 1}^{m}{E_{j}} ≠ ∅ */
    while (!unallocatedEdges.empty() && Heuristic::getElapsedTime(startTime) < timeLimit) {
        /* CL ← ∅ */
        std::vector<std::pair<std::pair<Edge, unsigned int>, double> > candidateList;

        /* ∀ j ∈ {1, ..., m} */
        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            /* if E_{j} ≠ ∅ ∧ d_{E_{j}} < (1 - B) \bar{d}_{ℰ} */
            if (!districts[j].empty() && districtsDemand[j] < minDemand) {
                /* Let V_{j} ⊆ V such that G[E_{j}] = (V_{j}, E_{j}) */
                /* ∀ e ∈ σ_{G}(V_{j}) \ ∪_{k = 1}^{m}{E_{k}} */
                for (const Edge & e : districtsUnallocatedAdjacentEdges[j]) {
                    /* if d_{E_{j}} + 2 d_{e} ≤ min{D, (1 + B) \bar{d}_{ℰ}} */
                    if (districtsDemand[j] + 2.0 * e.w <= maxDemand) {
                        /* CL ← CL ∪ {(e, j, c_{e, j})} */
                        candidateList.push_back(std::make_pair(
                                    std::make_pair(e, j), 
                                    this->instance.getC(e, j)));
                    }
                }
            }
        }

        /* if CL = ∅ */
        if (candidateList.empty()) {
            /* ∀ j ∈ {1, ..., m} */
            for (unsigned int j = 0; j < this->instance.getM(); j++) {
                /* if E_{j} = ∅ */
                if (districts[j].empty()) {
                    /* ∀ e ∈ E \ ∪_{k = 1}^{m}{E_{k}} */
                    for (const Edge & e : unallocatedEdges) {
                        /* CL ← CL ∪ {(e, j, c_{e, j})} */
                        candidateList.push_back(std::make_pair(
                                    std::make_pair(e, j), 
                                    this->instance.getC(e, j)));
                    }
                } else {
                    /* Let V_{j} ⊆ V such that G[E_{j}] = (V_{j}, E_{j}) */
                    /* ∀ e ∈ σ_{G}(V_{j}) \ ∪_{k = 1}^{m}{E_{k}} */
                    for (const Edge & e : districtsUnallocatedAdjacentEdges[j]) {
                        /* if d_{E_{j}} + 2 d_{e} ≤ min{D, (1 + B) \bar{d}_{ℰ}} */
                        if (districtsDemand[j] + 2.0 * e.w <= maxDemand) {
                            /* CL ← CL ∪ {(e, j, c_{e, j})} */
                            candidateList.push_back(std::make_pair(
                                        std::make_pair(e, j), 
                                        this->instance.getC(e, j)));
                        }
                    }
                }
            }
        }

        /* if CL = ∅ */
        if (candidateList.empty()) {
            /* ∀ j ∈ {1, ..., m} */
            for (unsigned int j = 0; j < this->instance.getM(); j++) {
                /* ∀ e ∈ σ_{G}(V_{j}) \ ∪_{k = 1}^{m}{E_{k}} */
                for (const Edge & e : unallocatedEdges) {
                    /* if d_{E_{j}} + 2 d_{e} ≤ min{D, (1 + B) \bar{d}_{ℰ}} */
                    if (districtsDemand[j] + 2.0 * e.w <= maxDemand) {
                        /* CL ← CL ∪ {(e, j, c_{e, j})} */
                        candidateList.push_back(std::make_pair(
                                    std::make_pair(e, j), 
                                    this->instance.getC(e, j)));
                    }
                }
            }
        }

        /* if CL = ∅ */
        if (candidateList.empty()) {
            /* ∀ j ∈ {1, ..., m} */
            for (unsigned int j = 0; j < this->instance.getM(); j++) {
                /* ∀ e ∈ E \ ∪_{k = 1}^{m}{E_{k}} */
                for (const Edge & e : unallocatedEdges) {
                    /* CL ← CL ∪ {(e, j, c_{e, j})} */
                    candidateList.push_back(std::make_pair(
                                std::make_pair(e, j), 
                                this->instance.getC(e, j)));
                }
            }
        }

        /* Let minC and maxC by the minimum and maximum values of CL candidates, respectively */
        double minC, maxC;
        minC = maxC = candidateList.front().second;

        for (const std::pair<std::pair<Edge, unsigned int>, double> & 
                candidate : candidateList) {
            if (minC > candidate.second) {
                minC = candidate.second;
            }

            if (maxC < candidate.second) {
                maxC = candidate.second;
            }
        }

        double threshold = maxC - this->alpha * (maxC - minC);

        /* RCL ← ∅ */
        std::vector<std::pair<std::pair<Edge, unsigned int>, double> > restrictedCandidateList;

        /* ∀ (e, j, c_{e, j}) */
        for (const std::pair<std::pair<Edge, unsigned int>, double> & 
                candidate : candidateList) {
            /* if c_{e, j} ≤ α(maxC - minC)  */
            if (candidate.second >= threshold) {
                /* RCL ← RCL ∪ {(e, j, c_{e, j})} */
                restrictedCandidateList.push_back(candidate);
            }
        }

        /* Choose a candidate (e, j, c_{e, j}) from RCL randomly */
        std::uniform_int_distribution<unsigned int> distribution(0, 
                restrictedCandidateList.size() - 1);
        std::pair<std::pair<Edge, unsigned int>, double> chosenCandidate =
            restrictedCandidateList[distribution(this->generator)];
        Edge e = chosenCandidate.first.first;
        unsigned int eId = this->instance.getG().getEdgeId(e);
        unsigned int j = chosenCandidate.first.second;

        /* E_{j} ← E_{j} ∪ {e} */
        districts[j].insert(e);
        districtsDemand[j] += 2.0 * e.w;
        edgesDistrict[eId - 1] = j;
        unallocatedEdges.erase(e);
        emptyDistricts.erase(j);
        districtsUnallocatedAdjacentEdges[j].erase(e);

        for (const Edge & f : edgesAdjacentEdges[eId - 1]) {
            unsigned int fId = this->instance.getG().getEdgeId(f);
            unsigned int k = edgesDistrict[fId - 1];

            if (k < this->instance.getM()) {
                districtsUnallocatedAdjacentEdges[k].erase(e);
            } else {
                districtsUnallocatedAdjacentEdges[j].insert(f);
            }
        }
    }

    return Solution(this->instance, districts);
}

