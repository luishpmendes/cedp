#include "SolutionFixer.hpp"
#include <algorithm>
#include <cfloat>
#include <climits>

/*
 * Try to fix disconnected districts in the specified districts.
 *
 * @param instance                       the instance of the districts.
 * @param districts                      the districts to be fixed.
 * @param adjacentEdges                  the edges adjacent to each edge.
 * @param edgesDistrict                  the current district of each edge.
 * @param allocatedEdges                 the current allocated edges.
 * @param unallocatedEdges               the current unallocated edges.
 * @param allocatedAdjacentEdges         the current allocated adjacent edges of each edge.
 * @param unallocatedAdjacentEdges       the current unallocated adjacent edges of each edge.
 * @param districtsDemand                the current demand of each district.
 * @param districtsBridgesThatAreNotLeaf the current bridges that are
 *                                       not leaf edges of each district.
 * @param startTime                      the start time.
 * @param timeLimit                      the time limit.
 *
 * @return possibly fixed districts.
 */
std::vector<std::set<Edge> > SolutionFixer::fixDisconnectedDistricts(
        const Instance & instance,
        const std::vector<std::set<Edge> > & districts,
        const std::vector<std::set<Edge> > & adjacentEdges,
        std::vector<unsigned int> & edgesDistrict,
        std::set<Edge> & allocatedEdges, std::set<Edge> & unallocatedEdges,
        std::vector<std::set<Edge> > & allocatedAdjacentEdges,
        std::vector<std::set<Edge> > & unallocatedAdjacentEdges,
        std::vector<double> & districtsDemand,
        std::vector<std::set<Edge> > & districtsBridgesThatAreNotLeafs,
        const std::chrono::steady_clock::time_point & startTime, 
        unsigned int timeLimit) {
    std::vector<std::set<Edge> > fixedDistricts (districts);

    /* ∀ j ∈ {1, ..., m} */
    for (unsigned int j = 0; j < instance.getM() && Heuristic::getElapsedTime(startTime); j++) {
        Graph inducedSubGraph = instance.getG().getInducedSubGraph(fixedDistricts[j]);

        /* If G[E_{j}] is disconnected */
        if (!inducedSubGraph.isConnected()) {
            std::vector<Graph> connectedComponents = inducedSubGraph.getConnectedComponents();
            /* E^{*} ← ∅ */
            unsigned int bestComponent = connectedComponents.size();
            /* maxC ← -∞ */
            double maxValue = -DBL_MAX;
            /* maxE ← -∞ */
            double maxEdges = -DBL_MAX;

            /* ∀ connected component G'=(V', E') of G[E_{j}] */
            for (unsigned int i = 1; i < connectedComponents.size(); i++) {
                double componentValue = 0.0;
                double componentEdges = connectedComponents[i].m();

                for (const Edge & e : connectedComponents[i].getEdges()) {
                    componentValue += instance.getC(e, j);
                }

                /*
                 * if maxC < ∑_{e ∈ E'}{c_{e, j}} ∨ 
                 * (maxC = ∑_{e ∈ E'}{c_{e, j}} ∧ maxE < |E'|)
                 */
                if ((maxValue < componentValue) ||
                        ((maxValue == componentValue) &&
                         (maxEdges < componentEdges))) {
                    /* E^{*} ← E' */
                    bestComponent = i;
                    /* maxC ← ∑_{e ∈ E'}{c_{e, j}} */
                    maxValue = componentValue;
                    /* maxE ← |E'| */
                    maxEdges = componentEdges;
                }
            }

            /* E_{j} ← E^{*} */
            for (unsigned int i = 0; i < connectedComponents.size(); i++) {
                if (i != bestComponent) {
                    for (const Edge & e : connectedComponents[i].getEdges()) {
                        unsigned int eId = instance.getG().getEdgeId(e);

                        districtsDemand[j] -= 2 * e.w;
                        edgesDistrict[eId - 1] = instance.getM();
                        allocatedEdges.erase(e);
                        unallocatedEdges.insert(e);

                        for (const Edge & f : adjacentEdges[eId - 1]) {
                            unsigned int fId = instance.getG().getEdgeId(f);

                            allocatedAdjacentEdges[fId - 1].erase(e);
                            unallocatedAdjacentEdges[fId - 1].insert(e);
                        }
                    }
                }
            }

            fixedDistricts[j] = std::set<Edge>(connectedComponents[bestComponent].getEdges());

            inducedSubGraph = instance.getG().getInducedSubGraph(fixedDistricts[j]);
            std::set<Edge> districtBridges = inducedSubGraph.getBridges();
            std::set<Edge> districtLeafEdges = inducedSubGraph.getLeafEdges();
            districtsBridgesThatAreNotLeafs[j].clear();
            std::set_difference(districtBridges.begin(),
                    districtBridges.end(), districtLeafEdges.begin(),
                    districtLeafEdges.end(), std::inserter(
                        districtsBridgesThatAreNotLeafs[j],
                        districtsBridgesThatAreNotLeafs[j].begin()));
        }
    }

    return fixedDistricts;
}

/*
 * Try to fix disconnected districts in the specified solution.
 *
 * @param solution  the solution to be fixed.
 * @param timeLimit the time limit.
 *
 * @return a possibly fixed solution.
 */
Solution SolutionFixer::fixDisconnectedDistricts(const Solution & solution, 
        unsigned int timeLimit) {
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    Instance instance = solution.getInstance();
    std::vector<std::set<Edge> > districts = solution.getDistricts();
    std::vector<std::set<Edge> > adjacentEdges (instance.getG().m());
    std::vector<unsigned int> edgesDistrict = solution.getEdgesDistrict();
    std::set<Edge> allocatedEdges = solution.getAllocatedEdges();
    std::set<Edge> unallocatedEdges = solution.getUnallocatedEdges();
    std::vector<std::set<Edge> > allocatedAdjacentEdges (instance.getG().m());
    std::vector<std::set<Edge> > unallocatedAdjacentEdges (instance.getG().m());
    std::vector<double> districtsDemand = solution.getDistrictsDemand();
    std::vector<std::set<Edge> > districtsBridgesThatAreNotLeafs (instance.getM());

    for (const Edge & e : instance.getG().getEdges()) {
        unsigned int eId = instance.getG().getEdgeId(e);

        adjacentEdges[eId - 1] = instance.getG().getAdjacentEdges(e);
        std::set_intersection(allocatedEdges.begin(), allocatedEdges.end(),
                adjacentEdges[eId - 1].begin(), adjacentEdges[eId - 1].end(),
                std::inserter(allocatedAdjacentEdges[eId - 1],
                    allocatedAdjacentEdges[eId - 1].begin()));
        std::set_intersection(unallocatedEdges.begin(),
                unallocatedEdges.end(), adjacentEdges[eId - 1].begin(),
                adjacentEdges[eId - 1].end(), std::inserter(
                    unallocatedAdjacentEdges[eId - 1],
                    unallocatedAdjacentEdges[eId - 1].begin()));
    }

    for (unsigned int j = 0; j < instance.getM(); j++) {
        Graph inducedSubGraph = instance.getG().getInducedSubGraph(districts[j]);
        std::set<Edge> districtBridges = inducedSubGraph.getBridges();
        std::set<Edge> districtLeafEdges = inducedSubGraph.getLeafEdges();
        std::set_difference(districtBridges.begin(), districtBridges.end(),
                districtLeafEdges.begin(), districtLeafEdges.end(),
                std::inserter(districtsBridgesThatAreNotLeafs[j],
                    districtsBridgesThatAreNotLeafs[j].begin()));
    }

    std::vector<std::set<Edge> > fixedDistricts =
        SolutionFixer::fixDisconnectedDistricts(instance, districts, 
                adjacentEdges, edgesDistrict, allocatedEdges, 
                unallocatedEdges, allocatedAdjacentEdges, 
                unallocatedAdjacentEdges, districtsDemand, 
                districtsBridgesThatAreNotLeafs, startTime, timeLimit);

    return Solution(instance, fixedDistricts);
}

/*
 * Try to fix districts with demand over the maximum in the specified districts.
 *
 * @param instance                       the instance of the districts.
 * @param districts                      the districts to be fixed.
 * @param minimumDemand                  the minimum allowed demand for each district.
 * @param maximumDemand                  the maximum allowed demand for each district.
 * @param adjacentEdges                  the edges adjacent to each edge.
 * @param edgesDistrict                  the current district of each edge.
 * @param allocatedEdges                 the current allocated edges.
 * @param unallocatedEdges               the current unallocated edges.
 * @param allocatedAdjacentEdges         the current allocated adjacent edges of each edge.
 * @param unallocatedAdjacentEdges       the current unallocated adjacent edges of each edge.
 * @param districtsDemand                the current demand of each district.
 * @param districtsBridgesThatAreNotLeaf the current bridges that are not
 *                                       leaf edges of each district.
 * @param startTime                      the start time.
 * @param timeLimit                      the time limit.
 *
 * @return possibly fixed districts.
 */
std::vector<std::set<Edge> > SolutionFixer::fixDistrictsWithDemandOverTheMaximum(
        const Instance & instance,
        const std::vector<std::set<Edge> > & districts, double minimumDemand,
        double maximumDemand,
        const std::vector<std::set<Edge> > & adjacentEdges,
        std::vector<unsigned int> & edgesDistrict,
        std::set<Edge> & allocatedEdges, std::set<Edge> & unallocatedEdges,
        std::vector<std::set<Edge> > & allocatedAdjacentEdges,
        std::vector<std::set<Edge> > & unallocatedAdjacentEdges,
        std::vector<double> & districtsDemand,
        std::vector<std::set<Edge> > & districtsBridgesThatAreNotLeafs, 
        const std::chrono::steady_clock::time_point & startTime, 
        unsigned int timeLimit) {
    std::vector<std::set<Edge> > fixedDistricts (districts);
    std::vector<std::set<Edge> > allocatedAdjacentEdgesNotInDistrict (instance.getG().m());

    for (const Edge & e : unallocatedEdges) {
        unsigned int eId = instance.getG().getEdgeId(e);

        allocatedAdjacentEdgesNotInDistrict[eId - 1] =
            std::set<Edge>(allocatedAdjacentEdges[eId - 1]);
    }

    for (const Edge & e : allocatedEdges) {
        unsigned int eId = instance.getG().getEdgeId(e);
        unsigned int j = edgesDistrict[eId - 1];

        std::set_difference(allocatedAdjacentEdges[eId - 1].begin(),
                allocatedAdjacentEdges[eId - 1].end(),
                fixedDistricts[j].begin(), fixedDistricts[j].end(),
                std::inserter(allocatedAdjacentEdgesNotInDistrict[eId - 1],
                    allocatedAdjacentEdgesNotInDistrict[eId - 1].begin()));
    }

    /* ∀ j ∈ {1, ..., m} */
    for (unsigned int j = 0; j < instance.getM() && 
            Heuristic::getElapsedTime(startTime) < timeLimit; j++) {
        /* while d_{E_{j}} > min{D, (1 + B) \bar{d}_{ℰ}} */
        while (districtsDemand[j] > maximumDemand && 
                Heuristic::getElapsedTime(startTime) < timeLimit) {
            /* e ← ∅ */
            bool found = false;
            Edge e;
            unsigned int eId = 0;
            /* k ← j */
            unsigned int k = j;
            /* minC ← ∞ */
            double minValue = DBL_MAX;
            /* maxD ← -∞ */
            double maxWeight = -DBL_MAX;

            /* ∀ f ∈  E_{j} */
            for (const Edge & f : fixedDistricts[j]) {
                unsigned int fId = instance.getG().getEdgeId(f);

                /* if G[E_{j} \ {f}] is connected */
                if (districtsBridgesThatAreNotLeafs[j].find(f) ==
                        districtsBridgesThatAreNotLeafs[j].end()) {
                    /* maxC ← -∞ */
                    double maxValue = -DBL_MAX;
                    double value = instance.getC(f, j);
                    double weight = f.w;

                    /* ∀ g ∈ σ_{G}(f)∩(∪_{j = 1}^{m}{E_{j}}) \ E_{j} */
                    for (const Edge & g : allocatedAdjacentEdgesNotInDistrict[fId - 1]) {
                        unsigned int gId = instance.getG().getEdgeId(g);
                        /* Let l ∈ {1, ..., m} such that g ∈ E_{l} */
                        unsigned int l = edgesDistrict[gId - 1];
                        double newValue = instance.getC(f, l);

                        /*
                         * if d_{E_{j}} - 2 d_{f} ≥ (1 - B) \bar{d}_{ℰ} 
                         * ∧ d_{E_{l}} + 2 d_{f} ≤ min{D, (1 + B) \bar{d}_{ℰ}} 
                         * ∧ (e = ∅ ∨ minC > c_{f, j} ∨ (minC = c_{f, j} 
                         * ∧ (maxD < d_{f} ∨ (maxD = d_{f} ∧ maxC < c_{f, l}))))
                         */
                        if (districtsDemand[j] - 2 * weight >= minimumDemand
                                && districtsDemand[l] + 2 * weight <= maximumDemand
                                && (!found || minValue > value ||
                                    (minValue == value &&
                                     (maxWeight < weight ||
                                      (maxWeight == weight &&
                                       maxValue < newValue))))) {
                                /* e ← f */
                                found = true;
                                e = f;
                                eId = fId;
                                /* k ← l */
                                k = l;
                                /* minC ← c_{f, j} */
                                minValue = value;
                                /* maxD ← d_{f} */
                                maxWeight = weight;
                                /* maxC ← c_{f, l} */
                                maxValue = newValue;
                        }
                    }
                }
            }

            /* if e = ∅ */
            if (!found) {
                /* ∀ f ∈ E_{j} */
                for (const Edge & f : fixedDistricts[j]) {
                    unsigned int fId = instance.getG().getEdgeId(f);
                    double value = instance.getC(f, j);
                    double weight = f.w;

                    /* if e = ∅ ∨ minC > c_{f, j} ∨ (minC = c_{f, j} ∧ maxD < d_{f}) */
                    if (!found || minValue > value || (minValue == value &&
                                maxWeight < weight)) {
                        /* e ← f */
                        found = true;
                        e = f;
                        eId = fId;
                        /* minC ← c_{f, j} */
                        minValue = value;
                        /* maxD ← d_{f} */
                        maxWeight = weight;
                    }
                }
            }

            /* E_{j} ← E_{j} \ {e} */
            fixedDistricts[j].erase(e);
            districtsDemand[j] -= 2 * e.w;
            edgesDistrict[eId - 1] = instance.getM();
            allocatedEdges.erase(e);
            unallocatedEdges.insert(e);
            allocatedAdjacentEdgesNotInDistrict[eId - 1] =
                std::set<Edge> (allocatedAdjacentEdges[eId - 1]);

            for (const Edge & f : adjacentEdges[eId - 1]) {
                unsigned int fId = instance.getG().getEdgeId(f);

                allocatedAdjacentEdges[fId - 1].erase(e);
                unallocatedAdjacentEdges[fId - 1].insert(e);
                allocatedAdjacentEdgesNotInDistrict[fId - 1].erase(e);
            }

            Graph inducedSubGraph = instance.getG().getInducedSubGraph(fixedDistricts[j]);
            std::set<Edge> districtBridges = inducedSubGraph.getBridges();
            std::set<Edge> districtLeafEdges = inducedSubGraph.getLeafEdges();
            districtsBridgesThatAreNotLeafs[j].clear();
            std::set_difference(districtBridges.begin(),
                    districtBridges.end(), districtLeafEdges.begin(),
                    districtLeafEdges.end(), std::inserter(
                        districtsBridgesThatAreNotLeafs[j],
                        districtsBridgesThatAreNotLeafs[j].begin()));

            /* if k ≠ j */
            if (k != j) {
                /* E_{k} ← E_{k} ∪ {e}*/
                fixedDistricts[k].insert(e);
                districtsDemand[k] += 2 * e.w;
                edgesDistrict[eId - 1] = k;
                allocatedEdges.insert(e);
                unallocatedEdges.erase(e);
                allocatedAdjacentEdgesNotInDistrict[eId - 1].clear();
                std::set_difference(allocatedAdjacentEdges[eId - 1].begin(),
                        allocatedAdjacentEdges[eId - 1].end(),
                        fixedDistricts[k].begin(), fixedDistricts[k].end(),
                        std::inserter(
                            allocatedAdjacentEdgesNotInDistrict[eId - 1],
                            allocatedAdjacentEdgesNotInDistrict[eId - 1].begin()));

                for (const Edge & f : adjacentEdges[eId - 1]) {
                    unsigned int fId = instance.getG().getEdgeId(f);

                    allocatedAdjacentEdges[fId - 1].insert(e);
                    unallocatedAdjacentEdges[fId - 1].erase(e);

                    if (edgesDistrict[fId - 1] != k) {
                        allocatedAdjacentEdgesNotInDistrict[fId - 1].insert(e);
                    } else {
                        allocatedAdjacentEdgesNotInDistrict[fId - 1].erase(e);
                    }
                }

                Graph inducedSubGraph = instance.getG().getInducedSubGraph(fixedDistricts[k]);
                districtBridges = inducedSubGraph.getBridges();
                districtLeafEdges = inducedSubGraph.getLeafEdges();
                districtsBridgesThatAreNotLeafs[k].clear();
                std::set_difference(districtBridges.begin(),
                        districtBridges.end(), districtLeafEdges.begin(),
                        districtLeafEdges.end(), std::inserter(
                            districtsBridgesThatAreNotLeafs[k],
                            districtsBridgesThatAreNotLeafs[k].begin()));
            }
        }
    }

    return fixedDistricts;
}

/*
 * Try to fix districts with demand over the maximum in the specified solution.
 *
 * @param solution  the solution to be fixed.
 * @param timeLimit the time limit.
 *
 * @return a possibly fixed solution.
 */
Solution SolutionFixer::fixDistrictsWithDemandOverTheMaximum(
        const Solution & solution, unsigned int timeLimit) {
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    Instance instance = solution.getInstance();
    std::vector<std::set<Edge> > districts = solution.getDistricts();
    double minimumDemand = instance.getMinimumDemand();
    double maximumDemand = instance.getMaximumDemand();
    std::vector<std::set<Edge> > adjacentEdges (instance.getG().m());
    std::vector<unsigned int> edgesDistrict = solution.getEdgesDistrict();
    std::set<Edge> allocatedEdges = solution.getAllocatedEdges();
    std::set<Edge> unallocatedEdges = solution.getUnallocatedEdges();
    std::vector<std::set<Edge> > allocatedAdjacentEdges (instance.getG().m());
    std::vector<std::set<Edge> > unallocatedAdjacentEdges (instance.getG().m());
    std::vector<double> districtsDemand = solution.getDistrictsDemand();
    std::vector<std::set<Edge> > districtsBridgesThatAreNotLeafs (instance.getM());

    for (const Edge & e : instance.getG().getEdges()) {
        unsigned int eId = instance.getG().getEdgeId(e);

        adjacentEdges[eId - 1] = instance.getG().getAdjacentEdges(e);
        std::set_intersection(allocatedEdges.begin(), allocatedEdges.end(),
                adjacentEdges[eId - 1].begin(), adjacentEdges[eId - 1].end(),
                std::inserter(allocatedAdjacentEdges[eId - 1],
                    allocatedAdjacentEdges[eId - 1].begin()));
        std::set_intersection(unallocatedEdges.begin(),
                unallocatedEdges.end(), adjacentEdges[eId - 1].begin(),
                adjacentEdges[eId - 1].end(), std::inserter(
                    unallocatedAdjacentEdges[eId - 1],
                    unallocatedAdjacentEdges[eId - 1].begin()));
    }

    for (unsigned int j = 0; j < instance.getM(); j++) {
        Graph inducedSubGraph = instance.getG().getInducedSubGraph(districts[j]);
        std::set<Edge> districtBridges = inducedSubGraph.getBridges();
        std::set<Edge> districtLeafEdges = inducedSubGraph.getLeafEdges();
        std::set_difference(districtBridges.begin(), districtBridges.end(),
                districtLeafEdges.begin(), districtLeafEdges.end(),
                std::inserter(districtsBridgesThatAreNotLeafs[j],
                    districtsBridgesThatAreNotLeafs[j].begin()));
    }

    std::vector<std::set<Edge> > fixedDistricts =
        SolutionFixer::fixDistrictsWithDemandOverTheMaximum(instance, 
                districts, minimumDemand, maximumDemand, adjacentEdges, 
                edgesDistrict, allocatedEdges, unallocatedEdges, 
                allocatedAdjacentEdges, unallocatedAdjacentEdges, 
                districtsDemand, districtsBridgesThatAreNotLeafs, startTime, 
                timeLimit);

    return Solution(instance, fixedDistricts);
}

/*
 * Try to fix districts with demand under the minimum in the specified districts.
 *
 * @param instance                       the instance of the districts.
 * @param districts                      the districts to be fixed.
 * @param minimumDemand                  the minimum allowed demand for each district.
 * @param maximumDemand                  the maximum allowed demand for each district.
 * @param adjacentEdges                  the edges adjacent to each edge.
 * @param edgesDistrict                  the current district of each edge.
 * @param allocatedEdges                 the current allocated edges.
 * @param unallocatedEdges               the current unallocated edges.
 * @param allocatedAdjacentEdges         the current allocated adjacent edges
 *                                       of each edge.
 * @param unallocatedAdjacentEdges       the current unallocated adjacent
 *                                       edges of each edge.
 * @param districtsDemand                the current demand of each district.
 * @param districtsBridgesThatAreNotLeaf the current bridges that are not
 *                                       leaf edges of each district.
 * @param startTime                      the start time.
 * @param timeLimit                      the time limit.
 *
 * @return possibly fixed districts.
 */
std::vector<std::set<Edge> > SolutionFixer::fixDistrictsWithDemandUnderTheMinimum(
        const Instance & instance,
        const std::vector<std::set<Edge> > & districts, double minimumDemand,
        double maximumDemand,
        const std::vector<std::set<Edge> > & adjacentEdges,
        std::vector<unsigned int> & edgesDistrict,
        std::set<Edge> & allocatedEdges, std::set<Edge> & unallocatedEdges,
        std::vector<std::set<Edge> > & allocatedAdjacentEdges,
        std::vector<std::set<Edge> > & unallocatedAdjacentEdges,
        std::vector<double> & districtsDemand,
        std::vector<std::set<Edge> > & districtsBridgesThatAreNotLeafs,
        const std::chrono::steady_clock::time_point & startTime, 
        unsigned int timeLimit) {
    std::vector<std::set<Edge> > fixedDistricts (districts);
    std::vector<std::set<Edge> > districtsAdjacentEdges (instance.getM());
    std::vector<std::set<Edge> > districtsAllocatedAdjacentEdges (instance.getM());
    std::vector<std::set<Edge> > districtsUnallocatedAdjacentEdges (instance.getM());

    for (unsigned int j = 0; j < instance.getM(); j++) {
        districtsAdjacentEdges[j] = instance.getG().getAdjacentEdges(fixedDistricts[j]);
        std::set_intersection(allocatedEdges.begin(), allocatedEdges.end(),
                districtsAdjacentEdges[j].begin(),
                districtsAdjacentEdges[j].end(), std::inserter(
                    districtsAllocatedAdjacentEdges[j],
                    districtsAllocatedAdjacentEdges[j].begin()));
        std::set_intersection(unallocatedEdges.begin(),
                unallocatedEdges.end(), districtsAdjacentEdges[j].begin(),
                districtsAdjacentEdges[j].end(), std::inserter(
                    districtsUnallocatedAdjacentEdges[j],
                    districtsUnallocatedAdjacentEdges[j].begin()));
    }

    /* ∀ j ∈ {1, ..., m} */
    for (unsigned int j = 0; j < instance.getM() && 
            Heuristic::getElapsedTime(startTime) < timeLimit; j++) {
        /* while d_{E_{j}} < (1 - B) \bar{d}_{ℰ} */
        while (districtsDemand[j] < maximumDemand && 
                Heuristic::getElapsedTime(startTime) < timeLimit) {
            /* e ← ∅ */
            bool found = false;
            Edge e;
            unsigned int eId = 0;
            /* k ← j */
            unsigned int k = j;
            /* maxC ← -∞ */
            double maxValue = -DBL_MAX;
            /* minD ← -∞ */
            double maxWeight = -DBL_MAX;

            /* ∀ f ∈ σ_{G}(V_{j}) \ (∪_{l = 1}^{m}{E_{l}}) */
            for (const Edge & f : districtsUnallocatedAdjacentEdges[j]) {
                unsigned int fId = instance.getG().getEdgeId(f);
                double value = instance.getC(f, j);
                double weight = f.w;

                /*
                 * d_{E_{j}} + 2 d_{f} ≤ min{D, (1 + B) \bar{d}_{ℰ}} ∧
                 * (e = ∅ ∨ maxC < c_{f, j} ∨ (maxC = c_{f, j} ∧ maxD < d_{f}))
                 */
                if (districtsDemand[j] + 2 * weight <= maximumDemand &&
                        (!found || maxValue < value || (maxValue == value &&
                                                        maxWeight < weight))) {
                    /* e ← f */
                    found = true;
                    e = f;
                    eId = fId;
                    /* maxC ← c_{f, j} */
                    maxValue = value;
                    /* maxD ← d_{f} */
                    maxWeight = weight;
                }
            }

            /* if e = ∅ */
            if (!found) {
                /* ∀ f ∈ σ_{G}(V_{j})∩(∪_{l = 1}^{m}{E_{l}}) */
                for (const Edge & f : districtsAllocatedAdjacentEdges[j]) {
                    unsigned int fId = instance.getG().getEdgeId(f);
                    /* let l ∈ {1, ..., m} such that f ∈ E_{l} */
                    unsigned int l = edgesDistrict[fId - 1];
                    double value = instance.getC(f, j) - instance.getC(f, l);
                    double weight = f.w;

                    /*
                     * if d_{E_{j}} + 2 d_{f} ≤ min{D, (1 + B) \bar{d}_{ℰ}} 
                     * ∧ d_{E_{l}} - 2 d_{f} ≥ (1 - B) \bar{d}_{ℰ} ∧ 
                     * G[E_{l}\{f}] is connected ∧ (e = ∅ ∨ 
                     * maxC < c_{f, j} - c_{f, l} ∨ (maxC = c_{f, j} - c_{f, l} 
                     * ∧ maxD < d_{f}))
                     */
                    if (districtsDemand[j] + 2 * weight <= maximumDemand &&
                            districtsDemand[l] - 2 * weight >= minimumDemand
                            && districtsBridgesThatAreNotLeafs[l].find(f) ==
                            districtsBridgesThatAreNotLeafs[l].end() &&
                            (!found || maxValue < value ||
                             (maxValue == value && maxWeight < weight))) {
                        /* e ← f */
                        found = true;
                        e = f;
                        eId = fId;
                        /* k ← l */
                        k = l;
                        /* maxC ← c_{f, j} - c_{f, l} */
                        maxValue = value;
                        /* maxD ← d_{f} */
                        maxWeight = weight;
                    }
                }
            }

            /* if e ≠ ∅ */
            if (found) {
                /* E_{j} ← E_{j} ∪ {e} */
                fixedDistricts[j].insert(e);
                districtsDemand[j] += 2 * e.w;
                edgesDistrict[eId - 1] = j;
                allocatedEdges.insert(e);
                unallocatedEdges.erase(e);
                districtsAdjacentEdges[j].erase(e);
                districtsAllocatedAdjacentEdges[j].erase(e);
                districtsUnallocatedAdjacentEdges[j].erase(e);

                for (const Edge & f : adjacentEdges[eId - 1]) {
                    unsigned int fId = instance.getG().getEdgeId(f);

                    allocatedAdjacentEdges[fId - 1].insert(e);
                    unallocatedAdjacentEdges[fId - 1].erase(e);

                    if (edgesDistrict[fId - 1] != j) {
                        districtsAdjacentEdges[j].insert(e);
                    }
                }

                for (const Edge & f : allocatedAdjacentEdges[eId - 1]) {
                    unsigned int fId = instance.getG().getEdgeId(f);

                    if (edgesDistrict[fId - 1] != j) {
                        districtsAllocatedAdjacentEdges[j].insert(f);
                        districtsAllocatedAdjacentEdges[edgesDistrict[fId - 1]].insert(e);
                    }
                }

                for (const Edge & f : unallocatedAdjacentEdges[eId - 1]) {
                    districtsUnallocatedAdjacentEdges[j].insert(f);
                }

                Graph inducedSubGraph = instance.getG().getInducedSubGraph(fixedDistricts[j]);
                std::set<Edge> districtBridges = inducedSubGraph.getBridges();
                std::set<Edge> districtLeafEdges = inducedSubGraph.getLeafEdges();
                districtsBridgesThatAreNotLeafs[j].clear();
                std::set_difference(districtBridges.begin(),
                        districtBridges.end(), districtLeafEdges.begin(),
                        districtLeafEdges.end(), std::inserter(
                            districtsBridgesThatAreNotLeafs[j],
                            districtsBridgesThatAreNotLeafs[j].begin()));

                /* if k ≠ j */
                if (k != j) {
                    /* E_{k} ← E_{k} \ {e} */
                    fixedDistricts[k].erase(e);
                    districtsDemand[k] -= 2 * e.w;

                    inducedSubGraph = instance.getG().getInducedSubGraph(fixedDistricts[k]);
                    districtBridges = inducedSubGraph.getBridges();
                    districtLeafEdges = inducedSubGraph.getLeafEdges();
                    districtsBridgesThatAreNotLeafs[j].clear();
                    std::set_difference(districtBridges.begin(),
                            districtBridges.end(), districtLeafEdges.begin(),
                            districtLeafEdges.end(), std::inserter(
                                districtsBridgesThatAreNotLeafs[k],
                                districtsBridgesThatAreNotLeafs[k].begin()));
                }
            } else {
                break;
            }
        }
    }

    return fixedDistricts;
}

/*
 * Try to fix districts with demand under the minimum in the specified solution.
 *
 * @param solution  the solution to be fixed.
 * @param timeLimit the time limit.
 *
 * @return a possibly fixed solution.
 */
Solution SolutionFixer::fixDistrictsWithDemandUnderTheMinimum(
        const Solution & solution, unsigned int timeLimit) {
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    Instance instance = solution.getInstance();
    std::vector<std::set<Edge> > districts = solution.getDistricts();
    double minimumDemand = instance.getMinimumDemand();
    double maximumDemand = instance.getMaximumDemand();
    std::vector<std::set<Edge> > adjacentEdges (instance.getG().m());
    std::vector<unsigned int> edgesDistrict = solution.getEdgesDistrict();
    std::set<Edge> allocatedEdges = solution.getAllocatedEdges();
    std::set<Edge> unallocatedEdges = solution.getUnallocatedEdges();
    std::vector<std::set<Edge> > allocatedAdjacentEdges (instance.getG().m());
    std::vector<std::set<Edge> > unallocatedAdjacentEdges (instance.getG().m());
    std::vector<double> districtsDemand = solution.getDistrictsDemand();
    std::vector<std::set<Edge> > districtsBridgesThatAreNotLeafs (instance.getM());

    for (const Edge & e : instance.getG().getEdges()) {
        unsigned int eId = instance.getG().getEdgeId(e);

        adjacentEdges[eId - 1] = instance.getG().getAdjacentEdges(e);
        std::set_intersection(allocatedEdges.begin(), allocatedEdges.end(),
                adjacentEdges[eId - 1].begin(), adjacentEdges[eId - 1].end(),
                std::inserter(allocatedAdjacentEdges[eId - 1],
                    allocatedAdjacentEdges[eId - 1].begin()));
        std::set_intersection(unallocatedEdges.begin(),
                unallocatedEdges.end(), adjacentEdges[eId - 1].begin(),
                adjacentEdges[eId - 1].end(), std::inserter(
                    unallocatedAdjacentEdges[eId - 1],
                    unallocatedAdjacentEdges[eId - 1].begin()));
    }

    for (unsigned int j = 0; j < instance.getM(); j++) {
        Graph inducedSubGraph = instance.getG().getInducedSubGraph(districts[j]);
        std::set<Edge> districtBridges = inducedSubGraph.getBridges();
        std::set<Edge> districtLeafEdges = inducedSubGraph.getLeafEdges();
        std::set_difference(districtBridges.begin(), districtBridges.end(),
                districtLeafEdges.begin(), districtLeafEdges.end(),
                std::inserter(districtsBridgesThatAreNotLeafs[j],
                    districtsBridgesThatAreNotLeafs[j].begin()));
    }

    std::vector<std::set<Edge> > fixedDistricts =
        SolutionFixer::fixDistrictsWithDemandUnderTheMinimum(instance, 
                districts, minimumDemand, maximumDemand, adjacentEdges, 
                edgesDistrict, allocatedEdges, unallocatedEdges, 
                allocatedAdjacentEdges, unallocatedAdjacentEdges, 
                districtsDemand, districtsBridgesThatAreNotLeafs, startTime, 
                timeLimit);

    return Solution(instance, fixedDistricts);
}

/*
 * Try to fix unallocated edges in the specified districts.
 *
 * @param instance               the instance of the districts.
 * @param districts              the districts to be fixed.
 * @param maximumDemand          the maximum allowed demand for each district.
 * @param adjacentEdges          the edges adjacent to each edge.
 * @param edgesDistrict          the current district of each edge.
 * @param allocatedEdges         the current allocated edges.
 * @param unallocatedEdges       the current unallocated edges.
 * @param allocatedAdjacentEdges the current allocated adjacent edges of each edge.
 * @param districtsDemand        the current demand of each district.
 * @param startTime              the start time.
 * @param timeLimit              the time limit.
 *
 * @return possibly fixed districts.
 */
std::vector<std::set<Edge> > SolutionFixer::fixUnallocatedEdges(
        const Instance & instance,
        const std::vector<std::set<Edge> > & districts, double maximumDemand,
        const std::vector<std::set<Edge> > & adjacentEdges,
        std::vector<unsigned int> & edgesDistrict,
        std::set<Edge> & allocatedEdges, std::set<Edge> & unallocatedEdges,
        std::vector<std::set<Edge> > & allocatedAdjacentEdges,
        std::vector<double> & districtsDemand, 
        const std::chrono::steady_clock::time_point & startTime, 
        unsigned int timeLimit) {
    std::vector<std::set<Edge> > fixedDistricts (districts);

    /* while ∪_{j = 1}^{m}{E_{j}} ≠ E  */
    while (!unallocatedEdges.empty() && Heuristic::getElapsedTime(startTime) < timeLimit) {
        /* e ← ∅ */
        bool found = false;
        Edge e;
        unsigned int eId = 0;
        /* j ← 0 */
        unsigned int j = instance.getM();
        /* maxC ← -∞ */
        double maxValue = -DBL_MAX;
        /* minW ← ∞ */
        double minWeight = DBL_MAX;
        /* minD ← ∞ */
        double minDemand = DBL_MAX;

        /* ∀ f ∈ E\(∪_{k = 1}^{m}{E_{k}}) */
        for (const Edge & f : unallocatedEdges) {
            unsigned int fId = instance.getG().getEdgeId(f);
            double weight = f.w;

            /* ∀ g ∈ σ_{G}(f)∩(∪_{k = 1}^{m}{E_{k}}) */
            for (const Edge & g : allocatedAdjacentEdges[fId - 1]) {
                unsigned int gId = instance.getG().getEdgeId(g);
                /* let k ∈ {1, ..., m} such that g ∈ E_{k} */
                unsigned int k = edgesDistrict[gId - 1];
                double value = instance.getC(f, k);

                /*
                 * if d_{E_{k}} + 2 d_{f} ≤ min{D, (1 + B) \bar{d}_{ℰ}} 
                 * ∧ (e = ∅ ∨ maxC < c_{f, k} ∨ (maxC = c_{f, k} ∧ 
                 * (minW > d_{f ∨ (minW = d_{f} ∧ minD > d_{E_{k}}))))
                 */
                if (districtsDemand[k] + 2 * weight <= maximumDemand &&
                        (!found || maxValue < value ||
                         (maxValue == value &&
                          (minWeight > weight ||
                           (minWeight == weight &&
                            minDemand > districtsDemand[k]))))) {
                    /* e ← f */
                    found = true;
                    e = f;
                    eId = fId;
                    /* j ← k */
                    j = k;
                    /* maxC ← c_{f, k} */
                    maxValue = value;
                    /* minW ← d_{f} */
                    minWeight = weight;
                    /* minD ← d_{E_{k}} */
                    minDemand = districtsDemand[k];
                }
            }
        }

        /* if e = ∅ */
        if (!found) {
            /* ∀ f ∈ E\(∪_{k = 1}^{m}{E_{k}}) */
            for (const Edge & f : unallocatedEdges) {
                unsigned int fId = instance.getG().getEdgeId(f);
                double weight = f.w;
                /* ∀ k ∈ {1, ..., m} */
                for (unsigned int k = 0; k < instance.getM(); k++) {
                    double value = instance.getC(f, k);

                    /* 
                     * if e = ∅ ∨ maxC < c_{f, k} ∨ (maxC = c_{f, k} ∧ 
                     * (minW > d_{f} ∨ (minW = d_{f} ∧ minD > d_{E_{k}})))
                     */
                    if (!found || maxValue < value || (maxValue == value &&
                                (minWeight > weight ||
                                 (minWeight == weight &&
                                  minDemand > districtsDemand[k])))) {
                        /* e ← f */
                        found = true;
                        e = f;
                        eId = fId;
                        /* j ← k */
                        j = k;
                        /* maxC ← c_{f, k} */
                        maxValue = value;
                        /* minW ← d_{f} */
                        minWeight = weight;
                        /* minD ← d_{E_{k}} */
                        minDemand = districtsDemand[k];
                    }
                }
            }
        }

        /* E_{j} ← E_{j} ∪ {e} */
        fixedDistricts[j].insert(e);
        districtsDemand[j] += 2 * e.w;
        edgesDistrict[eId - 1] = j;
        allocatedEdges.insert(e);
        unallocatedEdges.erase(e);

        for (const Edge & f : adjacentEdges[eId - 1]) {
            unsigned int fId = instance.getG().getEdgeId(f);

            allocatedAdjacentEdges[fId - 1].insert(e);
        }
    }

    return fixedDistricts;
}

/*
 * Try to fix unallocated edges in the specified solution.
 *
 * @param solution the solution to be fixed.
 *
 * @return a possibly fixed solution.
 */
Solution SolutionFixer::fixUnallocatedEdges(const Solution & solution, unsigned int timeLimit) {
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    Instance instance = solution.getInstance();
    std::vector<std::set<Edge> > districts = solution.getDistricts();
    double maximumDemand = instance.getMaximumDemand();
    std::vector<std::set<Edge> > adjacentEdges (instance.getG().m());
    std::vector<unsigned int> edgesDistrict = solution.getEdgesDistrict();
    std::set<Edge> allocatedEdges = solution.getAllocatedEdges();
    std::set<Edge> unallocatedEdges = solution.getUnallocatedEdges();
    std::vector<std::set<Edge> > allocatedAdjacentEdges (instance.getG().m());
    std::vector<double> districtsDemand = solution.getDistrictsDemand();

    for (const Edge & e : instance.getG().getEdges()) {
        unsigned int eId = instance.getG().getEdgeId(e);

        adjacentEdges[eId - 1] = instance.getG().getAdjacentEdges(e);
        std::set_intersection(allocatedEdges.begin(), allocatedEdges.end(),
                adjacentEdges[eId - 1].begin(), adjacentEdges[eId - 1].end(),
                std::inserter(allocatedAdjacentEdges[eId - 1],
                    allocatedAdjacentEdges[eId - 1].begin()));
    }

    std::vector<std::set<Edge> > fixedDistricts =
        SolutionFixer::fixUnallocatedEdges(instance, districts, maximumDemand,
                adjacentEdges, edgesDistrict, allocatedEdges,
                unallocatedEdges, allocatedAdjacentEdges, districtsDemand, 
                startTime, timeLimit);

    return Solution(instance, fixedDistricts);
}

/*
 * Try to fix the specified solution.
 *
 * @param solution  the solution to be fixed.
 * @param timeLimit the time limit.
 *
 * @return a possible fixed solution.
 */
Solution SolutionFixer::fixSolution(const Solution & solution, unsigned int timeLimit) {
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    Instance instance = solution.getInstance();
    std::vector<std::set<Edge> > fixedDistricts = solution.getDistricts();
    double minimumDemand = instance.getMinimumDemand();
    double maximumDemand = instance.getMaximumDemand();

    std::vector<std::set<Edge> > adjacentEdges (instance.getG().m());
    std::vector<double> districtsDemand = solution.getDistrictsDemand();

    for (const Edge & e : instance.getG().getEdges()) {
        unsigned int eId = instance.getG().getEdgeId(e);

        adjacentEdges[eId - 1] = instance.getG().getAdjacentEdges(e);
    }

    std::vector<unsigned int> edgesDistrict = solution.getEdgesDistrict();
    std::set<Edge> allocatedEdges = solution.getAllocatedEdges();
    std::set<Edge> unallocatedEdges = solution.getUnallocatedEdges();
    std::vector<std::set<Edge> > allocatedAdjacentEdges (instance.getG().m());
    std::vector<std::set<Edge> > unallocatedAdjacentEdges (instance.getG().m());
    std::vector<std::set<Edge> > districtsBridgesThatAreNotLeafs (instance.getM());

    for (const Edge & e : instance.getG().getEdges()) {
        unsigned int eId = instance.getG().getEdgeId(e);

        std::set_intersection(allocatedEdges.begin(), allocatedEdges.end(),
                adjacentEdges[eId - 1].begin(), adjacentEdges[eId - 1].end(),
                std::inserter(allocatedAdjacentEdges[eId - 1],
                    allocatedAdjacentEdges[eId - 1].begin()));
        std::set_intersection(unallocatedEdges.begin(),
                unallocatedEdges.end(), adjacentEdges[eId - 1].begin(),
                adjacentEdges[eId - 1].end(), std::inserter(
                    unallocatedAdjacentEdges[eId - 1],
                    unallocatedAdjacentEdges[eId - 1].begin()));
    }

    for (unsigned int j = 0; j < instance.getM(); j++) {
        Graph inducedSubGraph = instance.getG().getInducedSubGraph(fixedDistricts[j]);
        std::set<Edge> districtBridges = inducedSubGraph.getBridges();
        std::set<Edge> districtLeafEdges = inducedSubGraph.getLeafEdges();
        std::set_difference(districtBridges.begin(), districtBridges.end(),
                districtLeafEdges.begin(), districtLeafEdges.end(),
                std::inserter(districtsBridgesThatAreNotLeafs[j],
                    districtsBridgesThatAreNotLeafs[j].begin()));
    }

    /* Fixing disconnected districts */
    fixedDistricts = SolutionFixer::fixDisconnectedDistricts(instance,
            fixedDistricts, adjacentEdges, edgesDistrict, allocatedEdges,
            unallocatedEdges, allocatedAdjacentEdges,
            unallocatedAdjacentEdges, districtsDemand,
            districtsBridgesThatAreNotLeafs, startTime, timeLimit);

    /* Fixing district with demand over the maximum */
    fixedDistricts = SolutionFixer::fixDistrictsWithDemandOverTheMaximum(
            instance, fixedDistricts, minimumDemand, maximumDemand, 
            adjacentEdges, edgesDistrict, allocatedEdges, unallocatedEdges, 
            allocatedAdjacentEdges, unallocatedAdjacentEdges, 
            districtsDemand, districtsBridgesThatAreNotLeafs, startTime, 
            timeLimit);

    /* Fixing disconnected districts */
    fixedDistricts = SolutionFixer::fixDisconnectedDistricts(instance,
            fixedDistricts, adjacentEdges, edgesDistrict, allocatedEdges,
            unallocatedEdges, allocatedAdjacentEdges,
            unallocatedAdjacentEdges, districtsDemand,
            districtsBridgesThatAreNotLeafs, startTime, timeLimit);

    /* Fixing district with demand under the minimum */
    fixedDistricts = SolutionFixer::fixDistrictsWithDemandUnderTheMinimum(
            instance, fixedDistricts, minimumDemand, maximumDemand, 
            adjacentEdges, edgesDistrict, allocatedEdges, unallocatedEdges, 
            allocatedAdjacentEdges, unallocatedAdjacentEdges, 
            districtsDemand, districtsBridgesThatAreNotLeafs, startTime, 
            timeLimit);

    /* Fixing unallocated edges */
    fixedDistricts = SolutionFixer::fixUnallocatedEdges(instance, 
            fixedDistricts, maximumDemand, adjacentEdges, edgesDistrict, 
            allocatedEdges, unallocatedEdges, allocatedAdjacentEdges, 
            districtsDemand, startTime, timeLimit);

    return Solution(instance, fixedDistricts);
}

