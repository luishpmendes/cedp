#pragma once

#include "../instance/Instance.hpp"

/*
 * The Solution class represents a solution for the CEDP.
 */
class Solution {
    private:
        /* This solution's instance. */
        Instance instance;

        /* This solution's districts. */
        std::vector<std::set<Edge> > districts;

        /* This solution's district of each edge. */
        std::vector<unsigned int> edgesDistrict;

        /* This solution's decision variables. */
        std::vector<std::vector<bool> > x;

        /* This solution's unallocated edges. */
        std::set<Edge> unallocatedEdges;

        /* This solution's allocated edges. */
        std::set<Edge> allocatedEdges;

        /* This solution's demand of each district. */
        std::vector<double> districtsDemand;

        /* This solution's value of each district. */
        std::vector<double> districtsValue;

        /* This solution's value. */
        double value;

        /*
         * Initializes a new solution.
         *
         * @param instance  the new solution's instance.
         * @param districts the new solution's districts.
         */
        void init(const Instance & instance, const std::vector<std::set<Edge> > & districts);

        /*
         * Initializes a new solution.
         *
         * @param instance      the new solution's instance.
         * @param edgesDistrict the new solution's district of each edge.
         */
        void init(const Instance & instance, const std::vector<unsigned int> & edgesDistrict);

        /*
         * Initializes a new solution.
         *
         * @param instance the new solution's instance.
         * @param x        the new solution's decision variables.
         */
        void init(const Instance & instance, const std::vector<std::vector<bool> > & x);

        /*
         * Initializes a new solution.
         *
         * @param instance the new solution's instance.
         * @param is       the input stream to read from.
         */
        void init(const Instance & instance, std::istream & is);

    public:
        /*
         * Constructs a new solution.
         *
         * @param instance  the new solution's instance.
         * @param districts the new solution's districts.
         */
        Solution(const Instance & instance, const std::vector<std::set<Edge> > & districts);

        /*
         * Constructs a new solution.
         *
         * @param instance      the new solution's instance.
         * @param edgesDistrict the new solution's district of each edge.
         */
        Solution(const Instance & instance, const std::vector<unsigned int> & edgesDistrict);

        /*
         * Constructs a new solution.
         *
         * @param instance the new solution's instance.
         * @param x        the new solution's decision variables.
         */
        Solution(const Instance & instance, const std::vector<std::vector<bool> > & x);

        /*
         * Constructs a new solution.
         *
         * @param instance the new solution's instance.
         * @param is       the input stream to read from.
         */
        Solution(const Instance & instance, std::istream & is);

        /*
         * Constructs a new solution.
         *
         * @param instance the new solution's instance.
         * @param filename the file to read from.
         */
        Solution(const Instance & instance, const char * filename);

        /*
         * Constructs a new solution.
         *
         * @param instance the new solution's instance.
         * @param filename the file to read from.
         */
        Solution(const Instance & instance, std::string filename);

        /*
         * Constructs a new solution.
         *
         * @param instance the new solution's instance.
         */
        Solution(const Instance & instance);

        /*
         * Constructs a new empty solution.
         */
        Solution();

        /*
         * Verifies whether this solution is empty.
         *
         * @return true if this solution is empty; false otherwise.
         */
        bool isEmpty() const;

        /*
         * Returns this solution's instance.
         *
         * @return this solution's instance.
         */
        Instance getInstance() const;

        /*
         * Returns this solution's districts.
         *
         * @return this solution's districts.
         */
        std::vector<std::set<Edge> > getDistricts() const;

        /*
         * Returns this solution's specified district.
         *
         * @param j the id of the districts to be returned.
         *
         * @return this solution's specified district.
         */
        std::set<Edge> getDistrict(unsigned int j) const;

        /*
         * Sets this solution's specified district.
         *
         * @param j        the id of the districts to be set.
         * @param district the new edges of district specified district.
         */
        void setDistrict(unsigned int j, const std::set<Edge> & district);

        /*
         * Sets this solution's districts.
         *
         * @param districts the new districts.
         */
        void setDistricts(const std::vector<std::set<Edge> > & districts);

        /*
         * Unsets this solution's specified district.
         *
         * @param j the id of the districts to be unset.
         */
        void unsetDistrict(unsigned int j);

        /*
         * Returns the district of each edge.
         *
         * @return the district of each edge.
         */
        std::vector<unsigned int> getEdgesDistrict() const;

        /*
         * Returns the specified edge's district.
         *
         * @param edge the edge whose district is to be returned.
         *
         * @return the specified edge's district.
         */
        unsigned int getEdgeDistrict(unsigned int eId) const;

        /*
         * Returns the specified edge's district.
         *
         * @param edge the edge whose district is to be returned.
         *
         * @return the specified edge's district.
         */
        unsigned int getEdgeDistrict(const Edge & e) const;

        /*
         * Sets the specified edge's district to the specified district.
         *
         * @param eId the id of the edge whose district is to be set.
         * @param j   the new district of the specified edge.
         */
        void setEdgeDistrict(unsigned int eId, unsigned int j);

        /*
         * Sets the specified edge's district to the specified district.
         *
         * @param edge the edge whose district is to be set.
         * @param j    the new district of the specified edge.
         */
        void setEdgeDistrict(const Edge & e, unsigned int j);

        /*
         * Sets the district of a subset of edges.
         *
         * @param edges the subset of edges whose district is to be set.
         * @param j     the new district of the specified edges.
         */
        void setEdgesDistrict(const std::set<Edge> edges, unsigned int j);

        /*
         * Sets the district of each edge.
         *
         * @param edgesDistrict the district of each edge.
         */
        void setEdgesDistrict(const std::vector<unsigned int> & edgesDistrict);

        /*
         * Unsets the specified edge's district.
         *
         * @param eId the id of the edge whose district is to be unset.
         */
        void unsetEdgeDistrict(unsigned int eId);

        /*
         * Unsets the specified edge's district.
         *
         * @param edge the edge whose district is to be unset.
         */
        void unsetEdgeDistrict(const Edge & e);

        /*
         * Unsets the specified edges' district.
         *
         * @param edges the edges whose district is to be unset.
         */
        void unsetEdgesDistrict(const std::set<Edge> & edges);

        /*
         * Returns this solution's decision variables.
         *
         * @return this solution's decision variables.
         */
        std::vector<std::vector<bool> > getX() const;

        /*
         * Returns this solution's decision variable associated with the 
         * specified edge and district.
         *
         * @param eId the id of the edge whose decision variable is to be returned.
         * @param j   the id of the district whose decision variable is to be returned.
         *
         * @return this solution's decision variable associated with the 
         * specified edge and district.
         */
        bool getX(unsigned int eId, unsigned int j) const;

        /*
         * Returns this solution's decision variable associated with the 
         * specified edge and district.
         *
         * @param e the id of the edge whose decision variable is to be returned.
         * @param j the id of the district whose decision variable is to be returned.
         *
         * @return this solution's decision variable associated with the 
         * specified edge and district.
         */
        bool getX(const Edge & e, unsigned int j) const;

        /*
         * Returns this solution's unallocated edges.
         *
         * @return this solution's unallocated edges.
         */
        std::set<Edge> getUnallocatedEdges() const;

        /*
         * Returns this solution's allocated edges.
         *
         * @return this solution's allocated edges.
         */
        std::set<Edge> getAllocatedEdges() const;

        /*
         * Returns this solution's demand of each district.
         *
         * @return this solution's demand of each district.
         */
        std::vector<double> getDistrictsDemand() const;

        /*
         * Returns this solution's demand of the specified district.
         *
         * @param j the id of the district whose demand is to be returned.
         *
         * @return this solution's demand of the specified district.
         */
        double getDistrictsDemand(unsigned int j) const;

        /*
         * Returns this solution's value of the specified district.
         *
         * @param j the id of the district whose value is to be returned.
         *
         * @return this solution's value of the specified district.
         */
        double getDistrictValue(unsigned int j) const;

        /*
         * Returns this solution's value.
         *
         * @return this solution's value.
         */
        double getValue() const;

        /*
         * Verifies whether the edges of this solution's instance are allocated 
         * to exactly one distrist in this solution.
         *
         * @return true if all the edges are allocated to exactly one district;
         *         false otherwise.
         */
        bool isPartition() const;

        /*
         * Verifies whether this solution's districts are connected for this solution's instance.
         *
         * @return true if all districts are connected; false otherwise.
         */
        bool isConnected() const;

        /*
         * Verifies whether this solution's districts respects the capacity 
         * of this solution's instance.
         *
         * @return true if all districts respect the capacity; false otherwise.
         */
        bool respectsCapacity() const;

        /*
         * Verifies whether this solution's districts are balanced for this solution's instance.
         *
         * @return true if all districts are balanced; false otherwise.
         */
        bool isBalanced() const;

        /*
         * Verifies whether this solution is feasible for this solution's instance.
         *
         * @return true if this solution is feasible; false otherwise.
         */
        bool isFeasible() const;

        /*
         * Write this solution into the specified output stream.
         *
         * @param os the output stream to write into.
         */
        void write(std::ostream & os) const;

        /*
         * Write this solution into the specified file.
         *
         * @param filename the file to write into.
         */
        void write(const char * filename) const;

        /*
         * Write this solution into the specified file.
         *
         * @param filename the file to write into.
         */
        void write(const std::string & filename) const;

        /*
         * Write this solution into the standard output stream.
         */
        void write() const;
};

