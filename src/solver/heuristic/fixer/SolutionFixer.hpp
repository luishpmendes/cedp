#pragma once

#include "../../../solution/Solution.hpp"
#include "../Heuristic.hpp"

class SolutionFixer {
    public:
        /*
         * Try to fix disconnected districts in the specified districts.
         *
         * @param instance                       the instance of the districts.
         * @param districts                      the districts to be fixed.
         * @param adjacentEdges                  the edges adjacent to each edge.
         * @param edgesDistrict                  the current district of each edge.
         * @param allocatedEdges                 the current allocated edges.
         * @param unallocatedEdges               the current unallocated edges.
         * @param allocatedAdjacentEdges         the current allocated 
         *                                       adjacent edges of each edge.
         * @param unallocatedAdjacentEdges       the current unallocated 
         *                                       adjacent edges of each edge.
         * @param districtsDemand                the current demand of each district.
         * @param districtsBridgesThatAreNotLeaf the current bridges that are 
         *                                       not leaf edges of each district.
         * @param startTime                      the start time.
         * @param timeLimit                      the time limit.
         *
         * @return possibly fixed districts.
         */
        static std::vector<std::set<Edge> > fixDisconnectedDistricts(
                const Instance & instance, 
                const std::vector<std::set<Edge> > & districts, 
                const std::vector<std::set<Edge> > & adjacentEdges, 
                std::vector<unsigned int> & edgesDistrict, 
                std::set<Edge> & allocatedEdges, 
                std::set<Edge> & unallocatedEdges, 
                std::vector<std::set<Edge> > & allocatedAdjacentEdges, 
                std::vector<std::set<Edge> > & unallocatedAdjacentEdges, 
                std::vector<double> & districtsDemand, 
                std::vector<std::set<Edge> > & districtsBridgesThatAreNotLeafs,
                const std::chrono::steady_clock::time_point & startTime,
                unsigned int timeLimit);

        /*
         * Try to fix disconnected districts in the specified solution.
         *
         * @param solution  the solution to be fixed.
         * @param timeLimit the time limit.
         *
         * @return a possibly fixed solution.
         */
        static Solution fixDisconnectedDistricts(const Solution & solution, 
                unsigned int timeLimit);

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
         * @param allocatedAdjacentEdges         the current allocated 
         *                                       adjacent edges of each edge.
         * @param unallocatedAdjacentEdges       the current unallocated 
         *                                       adjacent edges of each edge.
         * @param districtsDemand                the current demand of each district.
         * @param districtsBridgesThatAreNotLeaf the current bridges that are 
         *                                       not leaf edges of each district.
         * @param startTime                      the start time.
         * @param timeLimit                      the time limit.
         *
         * @return possibly fixed districts.
         */
        static std::vector<std::set<Edge> > fixDistrictsWithDemandOverTheMaximum(
                const Instance & instance, 
                const std::vector<std::set<Edge> > & districts, 
                double minimumDemand, double maximumDemand, 
                const std::vector<std::set<Edge> > & adjacentEdges, 
                std::vector<unsigned int> & edgesDistrict, 
                std::set<Edge> & allocatedEdges, 
                std::set<Edge> & unallocatedEdges, 
                std::vector<std::set<Edge> > & allocatedAdjacentEdges, 
                std::vector<std::set<Edge> > & unallocatedAdjacentEdges, 
                std::vector<double> & districtsDemand, 
                std::vector<std::set<Edge> > & districtsBridgesThatAreNotLeafs, 
                const std::chrono::steady_clock::time_point & startTime, 
                unsigned int timeLimit);

        /*
         * Try to fix districts with demand over the maximum in the specified solution.
         *
         * @param solution  the solution to be fixed.
         * @param timeLimit the time limit.
         *
         * @return a possibly fixed solution.
         */
        static Solution fixDistrictsWithDemandOverTheMaximum(
                const Solution & solution, unsigned int timeLimit);

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
         * @param allocatedAdjacentEdges         the current allocated 
         *                                       adjacent edges of each edge.
         * @param unallocatedAdjacentEdges       the current unallocated 
         *                                       adjacent edges of each edge.
         * @param districtsDemand                the current demand of each district.
         * @param districtsBridgesThatAreNotLeaf the current bridges that are 
         *                                       not leaf edges of each district.
         * @param startTime                      the start time.
         * @param timeLimit                      the time limit.
         *
         * @return possibly fixed districts.
         */
        static std::vector<std::set<Edge> > fixDistrictsWithDemandUnderTheMinimum(
                const Instance & instance, 
                const std::vector<std::set<Edge> > & districts, 
                double minimumDemand, double maximumDemand, 
                const std::vector<std::set<Edge> > & adjacentEdges, 
                std::vector<unsigned int> & edgesDistrict, 
                std::set<Edge> & allocatedEdges, 
                std::set<Edge> & unallocatedEdges, 
                std::vector<std::set<Edge> > & allocatedAdjacentEdges, 
                std::vector<std::set<Edge> > & unallocatedAdjacentEdges, 
                std::vector<double> & districtsDemand, 
                std::vector<std::set<Edge> > & districtsBridgesThatAreNotLeafs,
                const std::chrono::steady_clock::time_point & startTime, 
                unsigned int timeLimit);

        /*
         * Try to fix districts with demand under the minimum in the specified solution.
         *
         * @param solution  the solution to be fixed.
         * @param timeLimit the time limit.
         *
         * @return a possibly fixed solution.
         */
        static Solution fixDistrictsWithDemandUnderTheMinimum(
                const Solution & solution, unsigned int timeLimit);

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
        static std::vector<std::set<Edge> > fixUnallocatedEdges(
                const Instance & instance, 
                const std::vector<std::set<Edge> > & districts, 
                double maximumDemand, 
                const std::vector<std::set<Edge> > & adjacentEdges, 
                std::vector<unsigned int> & edgesDistrict, 
                std::set<Edge> & allocatedEdges, 
                std::set<Edge> & unallocatedEdges, 
                std::vector<std::set<Edge> > & allocatedAdjacentEdges, 
                std::vector<double> & districtsDemand, 
                const std::chrono::steady_clock::time_point & startTime, 
                unsigned int timeLimit);

        /*
         * Try to fix unallocated edges in the specified solution.
         *
         * @param solution the solution to be fixed.
         *
         * @return a possibly fixed solution.
         */
        static Solution fixUnallocatedEdges(const Solution & solution, unsigned int timeLimit);

        /*
         * Try to fix the specified solution.
         *
         * @param solution  the solution to be fixed.
         * @param timeLimit the time limit.
         *
         * @return a possible fixed solution.
         */
        static Solution fixSolution(const Solution & solution, unsigned int timeLimit);
};

