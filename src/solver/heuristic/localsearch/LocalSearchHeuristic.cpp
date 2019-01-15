#include "LocalSearchHeuristic.hpp"
#include <dlib/optimization/max_cost_assignment.h>

/*
 * Constructs a new local search heuristic.
 *
 * @param instance the new local search heuristic's initial solution.
 * @param seed     the seed for the new local search heuristic's pseudo-random 
 *                 numbers generator.
 */
LocalSearchHeuristic::LocalSearchHeuristic(const Instance & instance, 
        unsigned int seed) : Heuristic::Heuristic(instance, seed) {}

/*
 * Constructs a new empty local search heuristic.
 */
LocalSearchHeuristic::LocalSearchHeuristic() : Heuristic::Heuristic() {}

/*
 * Improves the specified solution.
 *
 * @param solution the solution to be improved.
 * @param timeLimit the time limit.
 *
 * @return an improved solution.
 */
Solution LocalSearchHeuristic::improveSolution(Solution solution, unsigned int timeLimit) {
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    Solution improvedSolution(solution);
    std::vector<std::set<Edge> > improvedDistricts = improvedSolution.getDistricts();
    double minimumDemand = this->instance.getMinimumDemand();
    double maximumDemand = this->instance.getMaximumDemand();
    dlib::matrix<int> cost(this->instance.getM(), this->instance.getM());
    std::vector<long int> districtsIds;
    std::vector<unsigned int> edgesDistrict;
    std::vector<std::set<Edge> > edgesAdjacentEdges (this->instance.getG().m());
    std::vector<std::set<Edge> > edgesAdjacentEdgesNotInDistrict (this->instance.getG().m());
    std::vector<unsigned int> districtsVector (this->instance.getM(), this->instance.getM());
    std::vector<double> districtsDemand;
    std::vector<std::set<Edge> > districtsFrontierEdges (this->instance.getM());
    std::vector<std::set<Edge> > districtsFrontierEdgesThatAreNotBridgesButMayBeLeafs 
        (this->instance.getM());

    if (Heuristic::getElapsedTime(startTime) < timeLimit) {
        for (unsigned int i = 0; i < this->instance.getM(); i++) {
            for (unsigned int j = 0; j < this->instance.getM(); j++) {
                cost(i, j) = 0;

                for (const Edge & e : improvedDistricts[i]) {
                    cost(i, j) += this->instance.getC(e, j);
                }
            }
        }

        /* ℰ ← Max-Cost-Assignment(ℰ) */
        districtsIds = dlib::max_cost_assignment(cost);

        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            improvedDistricts[districtsIds[j]] = improvedSolution.getDistrict(j);
        }

        improvedSolution = Solution(this->instance, improvedDistricts);
    }

    if (Heuristic::getElapsedTime(startTime) < timeLimit) {
        edgesDistrict = improvedSolution.getEdgesDistrict();

        for (const Edge & e : this->instance.getG().getEdges()) {
            unsigned int eId = this->instance.getG().getEdgeId(e);
            unsigned int j = edgesDistrict[eId - 1];

            edgesAdjacentEdges[eId - 1] = this->instance.getG().getAdjacentEdges(e);
            std::set_difference(edgesAdjacentEdges[eId - 1].begin(), 
                    edgesAdjacentEdges[eId - 1].end(), 
                    improvedDistricts[j].begin(), improvedDistricts[j].end(), 
                    std::inserter(edgesAdjacentEdgesNotInDistrict[eId - 1], 
                        edgesAdjacentEdgesNotInDistrict[eId - 1].begin()));
        }

        districtsDemand = improvedSolution.getDistrictsDemand();

        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            districtsVector[j] = j;

            Graph inducedSubGraph = 
                this->instance.getG().getInducedSubGraph(improvedDistricts[j]);
            std::set<Edge> districtBridges = inducedSubGraph.getBridges();
            std::set<Edge> districtLeafEdges = inducedSubGraph.getLeafEdges();
            std::set<Edge> districtBridgesThatAreNotLeafs;

            std::set_difference(districtBridges.begin(), districtBridges.end(), 
                    districtLeafEdges.begin(), districtLeafEdges.end(), 
                    std::inserter(districtBridgesThatAreNotLeafs, 
                        districtBridgesThatAreNotLeafs.begin()));

            std::set<Edge> districtAdjacentEdges = 
                this->instance.getG().getAdjacentEdges(improvedDistricts[j]);

            for (const Edge & e : districtAdjacentEdges) {
                unsigned int eId = this->instance.getG().getEdgeId(e);

                if (edgesDistrict[eId - 1] == j) {
                    districtsFrontierEdges[j].insert(e);
                }
            }

            std::set_difference(districtsFrontierEdges[j].begin(), 
                    districtsFrontierEdges[j].end(), 
                    districtBridgesThatAreNotLeafs.begin(), 
                    districtBridgesThatAreNotLeafs.end(), 
                    std::inserter(
                        districtsFrontierEdgesThatAreNotBridgesButMayBeLeafs[j], 
                        districtsFrontierEdgesThatAreNotBridgesButMayBeLeafs[j].begin()));
        }

        /* improved ← true */
        bool improved = true;

        /* while improved */
        while (improved && Heuristic::getElapsedTime(startTime) < timeLimit) {
            /* improved ← false */
            improved = false;

            shuffle(districtsVector.begin(), districtsVector.end(), this->generator);

            /* ∀ j ∈ {1, ..., m} */
            for (unsigned int j : districtsVector) {
                std::vector<Edge> districtFrontierEdgesThatAreNotBridgesButMayBeLeafsVector (
                        districtsFrontierEdgesThatAreNotBridgesButMayBeLeafs[j].begin(), 
                        districtsFrontierEdgesThatAreNotBridgesButMayBeLeafs[j].end());
                shuffle(districtFrontierEdgesThatAreNotBridgesButMayBeLeafsVector.begin(), 
                        districtFrontierEdgesThatAreNotBridgesButMayBeLeafsVector.end(), 
                        this->generator);

                /* ∀ e ∈ E_{j} */
                for (const Edge & e : districtFrontierEdgesThatAreNotBridgesButMayBeLeafsVector) {
                    unsigned int eId = this->instance.getG().getEdgeId(e);

                    /* 
                     * if G[E_{j} \ {e}] is connected ∧ 
                     * d_{E_{j}} - 2 d_{e} ≥ (1 - B) \bar{d}_{ℰ} 
                     */
                    if (districtsDemand[j] - 2 * e.w >= minimumDemand) {
                        std::vector<Edge> edgeAdjacentEdgesNotInDistrictVector (
                                edgesAdjacentEdgesNotInDistrict[eId - 1].begin(), 
                                edgesAdjacentEdgesNotInDistrict[eId - 1].end());
                        shuffle(edgeAdjacentEdgesNotInDistrictVector.begin(), 
                                edgeAdjacentEdgesNotInDistrictVector.end(), this->generator);

                        /* ∀ f ∈ σ_{G}(e) \ E_{j} */
                        for (const Edge & f : edgeAdjacentEdgesNotInDistrictVector) {
                            /* Let k ∈ {1, ..., m} such that f ∈ E_{k} */
                            unsigned int fId = this->instance.getG().getEdgeId(f);
                            unsigned int k = edgesDistrict[fId - 1];

                            /*
                             * if d_{E_{k}} + 2 d_{e} <= min{D, (1 + B) \bar{d}_{ℰ}} 
                             * ∧ c_{e,j} < c_{e, k}
                             */
                            if (districtsDemand[k] + 2 * e.w <= maximumDemand 
                                    && this->instance.getC(e, j) < this->instance.getC(e, k)) {
                                /* E_{j} ← E_{j} \ {e} */
                                improvedDistricts[j].erase(e);
                                /* E_{k} ← E_{k} ∪ {e} */
                                improvedDistricts[k].insert(e);
                                edgesDistrict[eId - 1] = k;
                                std::set_difference(
                                        edgesAdjacentEdges[eId - 1].begin(), 
                                        edgesAdjacentEdges[eId - 1].end(), 
                                        improvedDistricts[k].begin(), 
                                        improvedDistricts[k].end(), 
                                        std::inserter(
                                            edgesAdjacentEdgesNotInDistrict[eId - 1], 
                                            edgesAdjacentEdgesNotInDistrict[eId - 1].begin()));

                                for (const Edge & g : edgesAdjacentEdges[eId - 1]) {
                                    unsigned int gId = this->instance.getG().getEdgeId(g);
                                    unsigned int l = edgesDistrict[gId - 1];

                                    if (l == j) {
                                        edgesAdjacentEdgesNotInDistrict[gId - 1].insert(e);
                                    } else if (l == k) {
                                        edgesAdjacentEdgesNotInDistrict[gId - 1].erase(e);
                                    }
                                }

                                districtsDemand[j] -= 2 * e.w;
                                districtsDemand[k] += 2 * e.w;

                                districtsFrontierEdges[j].erase(e);

                                for (const Edge & g : edgesAdjacentEdges[eId - 1]) {
                                    unsigned int gId = this->instance.getG().getEdgeId(g);

                                    if (edgesDistrict[gId - 1] == j) {
                                        bool isFrontierEdge = false;

                                        for (const Edge & h : edgesAdjacentEdges[gId - 1]) {
                                            unsigned int hId = 
                                                this->instance.getG().getEdgeId(h);

                                            if (edgesDistrict[hId - 1] != j) {
                                                isFrontierEdge = true;
                                                break;
                                            }
                                        }

                                        if (isFrontierEdge) {
                                            districtsFrontierEdges[j].insert(g);
                                        }
                                    }

                                    if (edgesDistrict[gId - 1] == k) {
                                        bool isFrontierEdge = false;

                                        for (const Edge & h : edgesAdjacentEdges[gId - 1]) {
                                            unsigned int hId = 
                                                this->instance.getG().getEdgeId(h);

                                            if (edgesDistrict[hId - 1] != k) {
                                                isFrontierEdge = true;
                                                break;
                                            }
                                        }

                                        if (!isFrontierEdge) {
                                            districtsFrontierEdges[k].erase(g);
                                        }
                                    }

                                    if (edgesDistrict[gId - 1] != k) {
                                        districtsFrontierEdges[k].insert(e);
                                    }
                                }

                                Graph inducedSubGraph = this->instance.getG().
                                    getInducedSubGraph(improvedDistricts[j]);
                                std::set<Edge> districtBridges = inducedSubGraph.getBridges();
                                std::set<Edge> districtLeafEdges = 
                                    inducedSubGraph.getLeafEdges();
                                std::set<Edge> districtBridgesThatAreNotLeafs;
                                std::set_difference(districtBridges.begin(), 
                                        districtBridges.end(), 
                                        districtLeafEdges.begin(), 
                                        districtLeafEdges.end(), 
                                        std::inserter(
                                            districtBridgesThatAreNotLeafs, 
                                            districtBridgesThatAreNotLeafs.begin()));
                                districtsFrontierEdgesThatAreNotBridgesButMayBeLeafs[j].clear();
                                std::set_difference(
                                        districtsFrontierEdges[j].begin(), 
                                        districtsFrontierEdges[j].end(), 
                                        districtBridgesThatAreNotLeafs.begin(), 
                                        districtBridgesThatAreNotLeafs.end(), 
                                        std::inserter(
                                            districtsFrontierEdgesThatAreNotBridgesButMayBeLeafs[j], 
                                            districtsFrontierEdgesThatAreNotBridgesButMayBeLeafs[j].begin()));

                                inducedSubGraph = this->instance.getG().
                                    getInducedSubGraph(improvedDistricts[k]);
                                districtBridges = inducedSubGraph.getBridges();
                                districtLeafEdges = inducedSubGraph.getLeafEdges();
                                districtBridgesThatAreNotLeafs.clear();
                                std::set_difference(districtBridges.begin(), 
                                        districtBridges.end(), 
                                        districtLeafEdges.begin(), 
                                        districtLeafEdges.end(), 
                                        std::inserter(
                                            districtBridgesThatAreNotLeafs, 
                                            districtBridgesThatAreNotLeafs.begin()));

                                /* improved ← true */
                                improved = true;

                                break;
                            }
                        }
                    }

                    if (improved) {
                        break;
                    }
                }

                if (improved) {
                    break;
                }
            }
        }

        improvedSolution = Solution(this->instance, improvedDistricts);
    }

    if (Heuristic::getElapsedTime(startTime) < timeLimit) {
        for (unsigned int i = 0; i < this->instance.getM(); i++) {
            for (unsigned int j = 0; j < this->instance.getM(); j++) {
                cost(i, j) = 0;

                for (const Edge & e : improvedDistricts[i]) {
                    cost(i, j) += this->instance.getC(e, j);
                }
            }
        }

        /* ℰ ← Max-Cost-Assignment(ℰ) */
        districtsIds = dlib::max_cost_assignment(cost);

        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            improvedDistricts[districtsIds[j]] = improvedSolution.getDistrict(j);
        }

        improvedSolution = Solution(this->instance, improvedDistricts);
    }

    return improvedSolution;
}

