#include "Solution.hpp"
#include <fstream>

/*
 * Initializes a new solution.
 *
 * @param instance  the new solution's instance.
 * @param districts the new solution's districts.
 */
void Solution::init(const Instance & instance, const std::vector<std::set<Edge> > & districts) {
    this->instance = instance;
    this->districts = std::vector<std::set<Edge> > (this->instance.getM());
    this->edgesDistrict = std::vector<unsigned int> (
            this->instance.getG().m(), this->instance.getM());
    this->x = std::vector<std::vector<bool> > (this->instance.getG().m(), 
            std::vector<bool> (this->instance.getM(), false));
    this->districtsDemand = std::vector<double> (this->instance.getM(), 0.0);
    this->districtsValue = std::vector<double> (this->instance.getM(), 0.0);
    this->value = 0.0;

    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        for (const Edge & e : districts[j]) {
            unsigned int eId = this->instance.getG().getEdgeId(e);
            unsigned int k = this->edgesDistrict[eId - 1];

            if (k == this->instance.getM() || (k < this->instance.getM() && 
                        this->instance.getC(e, j) > this->instance.getC(e, k))) {
                this->setEdgeDistrict(eId, j);
            }
        }
    }
}

/*
 * Initializes a new solution.
 *
 * @param instance      the new solution's instance.
 * @param edgesDistrict the new solution's district of each edge.
 */
void Solution::init(const Instance & instance, const std::vector<unsigned int> & edgesDistrict) {
    this->instance = instance;
    this->districts = std::vector<std::set<Edge> > (this->instance.getM());
    this->edgesDistrict = std::vector<unsigned int> (
            this->instance.getG().m(), this->instance.getM());
    this->x = std::vector<std::vector<bool> > (this->instance.getG().m(), 
            std::vector<bool> (this->instance.getM(), false));
    this->districtsDemand = std::vector<double> (this->instance.getM(), 0.0);
    this->districtsValue = std::vector<double> (this->instance.getM(), 0.0);
    this->value = 0.0;

    this->setEdgesDistrict(edgesDistrict);
}

/*
 * Initializes the solution.
 *
 * @param instance the new solution's instance.
 * @param x        the new solution's decision variables.
 */
void Solution::init(const Instance & instance, const std::vector<std::vector<bool> > & x) {
    this->instance = instance;
    this->districts = std::vector<std::set<Edge> > (this->instance.getM());
    this->edgesDistrict = std::vector<unsigned int> (
            this->instance.getG().m(), this->instance.getM());
    this->x = std::vector<std::vector<bool> > (this->instance.getG().m(), 
            std::vector<bool> (this->instance.getM(), false));
    this->districtsDemand = std::vector<double> (this->instance.getM(), 0.0);
    this->districtsValue = std::vector<double> (this->instance.getM(), 0.0);
    this->value = 0.0;

    for (unsigned int eId = 1; eId <= x.size(); eId++) {
        for (unsigned int j = 0; j < this->instance.getM(); j++) {
            if (x[eId - 1][j]) {
                this->setEdgeDistrict(eId, j);
            }
        }
    }
}

/*
 * Initializes a new solution.
 *
 * @param instance the new solution's instance.
 * @param is       the input stream to read from.
 */
void Solution::init(const Instance & instance, std::istream & is) {
    std::vector<std::set<Edge> > districts (instance.getM());
    std::vector<unsigned int> E (instance.getM());

    for (unsigned int j = 0; j < instance.getM(); j++) {
        is >> E[j];
    }

    for (unsigned int j = 0; j < instance.getM(); j++) {
        for (unsigned int e = 0; e < E[j]; e++) {
            unsigned int u, v;
            double w;
            is >> u >> v >> w;
            Edge edge = instance.getG().getEdge(u, v);
            districts[j].insert(edge);
        }
    }

    this->init(instance, districts);
}

/*
 * Constructs a new solution.
 *
 * @param instance  the new solution's instance.
 * @param districts the new solution's districts.
 */
Solution::Solution(const Instance & instance, const std::vector<std::set<Edge> > & districts) {
    this->init(instance, districts);
}

/*
 * Constructs a new solution.
 *
 * @param instance      the new solution's instance.
 * @param edgesDistrict the new solution's district of each edge.
 */
Solution::Solution(const Instance & instance, const std::vector<unsigned int> & edgesDistrict) {
    this->init(instance, edgesDistrict);
}

/*
 * Constructs a new solution.
 *
 * @param instance the new solution's instance.
 * @param x        the new solution's decision variables.
 */
Solution::Solution(const Instance & instance, const std::vector<std::vector<bool> > & x) {
    this->init(instance, x);
}

/*
 * Constructs a new solution.
 *
 * @param instance the new solution's instance.
 */
Solution::Solution(const Instance & instance) : Solution::Solution(instance, 
        std::vector<std::set<Edge> > (instance.getM())) {}

/*
 * Constructs a new solution.
 *
 * @param instance the new solution's instance.
 * @param is       the input stream to read from.
 */
Solution::Solution(const Instance & instance, std::istream & is) {
    this->init(instance, is);
}

/*
 * Constructs a new solution.
 *
 * @param instance the new solution's instance.
 * @param filename the file to read from.
 */
Solution::Solution(const Instance & instance, const char * filename) {
    std::ifstream ifs;
    ifs.open(filename);

    if (ifs.is_open()) {
        this->init(instance, ifs);
    } else {
        throw "File not found.";
    }
}

/*
 * Constructs a new solution.
 *
 * @param instance the new solution's instance.
 * @param filename the file to read from.
 */
Solution::Solution(const Instance & instance, std::string filename) : 
    Solution::Solution(instance, filename.c_str()) {}

/*
 * Constructs a new empty solution.
 */
Solution::Solution() : Solution::Solution(Instance()) {}

/*
 * Verifies whether this solution is empty.
 *
 * @return true if this solution is empty; false otherwise.
 */
bool Solution::isEmpty() const {
    if (this->instance.isEmpty()) {
        return true;
    }

    if (this->districts.empty()) {
        return true;
    }

    for (const std::set<Edge> & district : this->districts) {
        if (!district.empty()) {
            return false;
        }
    }

    return true;
}

/*
 * Returns this solution's instance.
 *
 * @return this solution's instance.
 */
Instance Solution::getInstance() const {
    return this->instance;
}

/*
 * Returns this solution's districts.
 *
 * @return this solution's districts.
 */
std::vector<std::set<Edge> > Solution::getDistricts() const {
    return this->districts;
}

/*
 * Returns this solution's specified district.
 *
 * @param j the id of the districts to be returned.
 *
 * @return this solution's specified district.
 */
std::set<Edge> Solution::getDistrict(unsigned int j) const {
    if (j < this->instance.getM()) {
        return this->districts[j];
    }

    return std::set<Edge> ();
}

/*
 * Sets this solution's specified district.
 *
 * @param j        the id of the districts to be set.
 * @param district the new edges of district specified district.
 */
void Solution::setDistrict(unsigned int j, const std::set<Edge> & district) {
    for (const Edge & e : district) {
        this->setEdgeDistrict(e, j);
    }
}

/*
 * Sets this solution's districts.
 *
 * @param districts the new districts.
 */
void Solution::setDistricts(const std::vector<std::set<Edge> > & districts) {
    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        this->setDistrict(j, districts[j]);
    }
}

/*
 * Unsets this solution's specified district.
 *
 * @param j the id of the districts to be unset.
 */
void Solution::unsetDistrict(unsigned int j) {
    if (j < this->instance.getM()) {
        for (const Edge & e : this->districts[j]) {
            this->unsetEdgeDistrict(e);
        }
    }
}

/*
 * Returns the district of each edge.
 *
 * @return the district of each edge.
 */
std::vector<unsigned int> Solution::getEdgesDistrict() const {
    return this->edgesDistrict;
}

/*
 * Returns the specified edge's district.
 *
 * @param edge the edge whose district is to be returned.
 *
 * @return the specified edge's district.
 */
unsigned int Solution::getEdgeDistrict(unsigned int eId) const {
    if (eId >= 1 && eId <= this->instance.getG().m()) {
        return this->edgesDistrict[eId - 1];
    }

    return this->instance.getM();
}

/* Returns the specified edge's district.
 *
 * @param edge the edge whose district is to be returned.
 *
 * @return the specified edge's district.
 */
unsigned int Solution::getEdgeDistrict(const Edge & e) const {
    unsigned int eId = this->instance.getG().getEdgeId(e);

    return this->getEdgeDistrict(eId);
}

/*
 * Sets the specified edge's district to the specified district.
 *
 * @param eId the id of the edge whose district is to be set.
 * @param j   the new district of the specified edge.
 */
void Solution::setEdgeDistrict(unsigned int eId, unsigned int j) {
    if (eId >= 1 && eId <= this->instance.getG().m() && j < this->instance.getM()) {
        Edge e = this->instance.getG().getEdgeById(eId);
        unsigned int k = this->edgesDistrict[eId - 1];

        if (k < this->instance.getM()) {
            this->districts[k].erase(e);
            this->x[eId - 1][k] = false;
            this->districtsDemand[k] -= 2 * e.w;
            this->districtsValue[k] -= this->instance.getC(eId, k);
            this->value -= this->instance.getC(eId, k);
        }

        this->districts[j].insert(e);
        this->edgesDistrict[eId - 1] = j;
        this->x[eId - 1][j] = true;
        this->unallocatedEdges.erase(e);
        this->allocatedEdges.insert(e);
        this->districtsDemand[j] += 2 * e.w;
        this->districtsValue[j] += this->instance.getC(eId, j);
        this->value += this->instance.getC(eId, j);
    }
}

/*
 * Sets the specified edge's district to the specified district.
 *
 * @param edge the edge whose district is to be set.
 * @param j    the new district of the specified edge.
 */
void Solution::setEdgeDistrict(const Edge & e, unsigned int j) {
    unsigned int eId = this->instance.getG().getEdgeId(e);

    this->setEdgeDistrict(eId, j);
}

/*
 * Sets the district of a subset of edges.
 *
 * @param edges the subset of edges whose district is to be set.
 * @param j     the new district of the specified edges.
 */
void Solution::setEdgesDistrict(const std::set<Edge> edges, unsigned int j) {
    for (const Edge & e : edges) {
        this->setEdgeDistrict(e, j);
    }
}

/*
 * Sets the district of each edge.
 *
 * @param edgesDistrict the district of each edge.
 */
void Solution::setEdgesDistrict(const std::vector<unsigned int> & edgesDistrict) {
    for (unsigned int eId = 1; eId <= edgesDistrict.size(); eId++) {
        unsigned int j = edgesDistrict[eId - 1];

        this->setEdgeDistrict(eId, j);
    }
}

/*
 * Unsets the specified edge's district.
 *
 * @param eId the id of the edge whose district is to be unset.
 */
void Solution::unsetEdgeDistrict(unsigned int eId) {
    if (eId >= 1 && eId <= this->instance.getG().m()) {
        Edge e = this->instance.getG().getEdgeById(eId);

        this->edgesDistrict[eId - 1] = this->instance.getM();
        this->unallocatedEdges.insert(e);
        this->allocatedEdges.erase(e);

        unsigned int k = this->edgesDistrict[eId - 1];

        if (k < this->instance.getM()) {
            this->districts[k].erase(e);
            this->x[eId - 1][k] = false;
            this->districtsDemand[k] -= 2 * e.w;
            this->districtsValue[k] -= this->instance.getC(eId, k);
            this->value -= this->instance.getC(eId, k);
        }
    }
}

/*
 * Unsets the specified edge's district.
 *
 * @param edge the edge whose district is to be unset.
 */
void Solution::unsetEdgeDistrict(const Edge & e) {
    unsigned int eId = this->instance.getG().getEdgeId(e);

    this->unsetEdgeDistrict(eId);
}

/*
 * Unsets the specified edges' district.
 *
 * @param edges the edges whose district is to be unset.
 */
void Solution::unsetEdgesDistrict(const std::set<Edge> & edges) {
    for (const Edge & e : edges) {
        this->unsetEdgeDistrict(e);
    }
}

/*
 * Returns this solution's decision variables.
 *
 * @return this solution's decision variables.
 */
std::vector<std::vector<bool> > Solution::getX() const {
    return this->x;
}

/*
 * Returns this solution's decision variable associated with the specified edge and district.
 *
 * @param eId the id of the edge whose decision variable is to be returned.
 * @param j   the id of the district whose decision variable is to be returned.
 *
 * @return this solution's decision variable associated with the specified edge and district.
 */
bool Solution::getX(unsigned int eId, unsigned int j) const {
    if (eId >= 1 && eId <= this->instance.getG().m() && j < this->instance.getM()) {
        return this->x[eId - 1][j];
    }

    return false;
}

/*
 * Returns this solution's decision variable associated with the specified edge and district.
 *
 * @param e the id of the edge whose decision variable is to be returned.
 * @param j the id of the district whose decision variable is to be returned.
 *
 * @return this solution's decision variable associated with the specified edge and district.
 */
bool Solution::getX(const Edge & e, unsigned int j) const {
    unsigned int eId = this->instance.getG().getEdgeId(e);

    return this->getX(eId, j);
}

/*
 * Returns this solution's unallocated edges.
 *
 * @return this solution's unallocated edges.
 */
std::set<Edge> Solution::getUnallocatedEdges() const {
    return this->unallocatedEdges;
}

/*
 * Returns this solution's allocated edges.
 *
 * @return this solution's allocated edges.
 */
std::set<Edge> Solution::getAllocatedEdges() const {
    return this->allocatedEdges;
}

/*
 * Returns this solution's demand of each district.
 *
 * @return this solution's demand of each district.
 */
std::vector<double> Solution::getDistrictsDemand() const {
    return this->districtsDemand;
}

/*
 * Returns this solution's demand of the specified district.
 *
 * @param j the id of the district whose demand is to be returned.
 *
 * @return this solution's demand of the specified district.
 */
double Solution::getDistrictsDemand(unsigned int j) const {
    if (j < this->instance.getM()) {
        return this->districtsDemand[j];
    }

    return 0.0;
}

/*
 * Returns this solution's value of the specified district.
 *
 * @param j the id of the district whose value is to be returned.
 *
 * @return this solution's value of the specified district.
 */
double Solution::getDistrictValue(unsigned int j) const {
    if (j < this->instance.getM()) {
        return this->districtsValue[j];
    }

    return 0.0;
}

/*
 * Returns this solution's value.
 *
 * @return this solution's value.
 */
double Solution::getValue() const {
    return this->value;
}

/*
 * Verifies whether the edges of this solution's instance are allocated to
 * exactly one distrist in this solution.
 *
 * @return true if all the edges are allocated to exactly one district; false otherwise.
 */
bool Solution::isPartition() const {
    for (const Edge & e : this->instance.getG().getEdges()) {
        if (this->getEdgeDistrict(e) >= this->instance.getM()) {
            return false;
        }
    }

    return true;
}

/*
 * Verifies whether this solution's districts are connected for this solution's instance.
 *
 * @return true if all districts are connected; false otherwise.
 */
bool Solution::isConnected() const {
    /* ∀ E_{j} ∈ ℰ */
    for (const std::set<Edge> & district : this->districts) {
        /* if G[E_{j}] is not connected */
        if (!this->instance.getG().getInducedSubGraph(district).isConnected()) {
            return false;
        }
    }

    return true;
}

/*
 * Verifies whether this solution's districts respects the capacity of this
 * solution's instance.
 *
 * @return true if all districts respect the capacity; false otherwise.
 */
bool Solution::respectsCapacity() const {
    /* ∀ E_{j} ∈ ℰ */
    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        /* if 2 ∑_{e ∈ E_{j}}{d_{e}} > D */
        if (this->districtsDemand[j] > this->instance.getD()) {
            return false;
        }
    }

    return true;
}

/*
 * Verifies whether this solution's districts are balanced for this solution's instance.
 *
 * @return true if all districts are balanced; false otherwise.
 */
bool Solution::isBalanced() const {
    /* ∀ E_{j} ∈ ℰ */
    for (unsigned int j = 0; j < this->instance.getM(); j++) {
        /*
         * if m ∑_{e ∈ E_{j}}{d_{e}} < (1 - B) ∑_{e ∈ E}{d_{e}}
         * || m ∑_{e ∈ E_{j}}{d_{e}} > (1 + B) ∑_{e ∈ E}{d_{e}}
         */
        if (this->districtsDemand[j] < this->instance.getMinimumDemand() || 
                this->districtsDemand[j] > this->instance.getMaximumDemand()) {
            return false;
        }
    }

    return true;
}

/*
 * Verifies whether this solution is feasible for this solution's instance.
 *
 * @return true if this solution is feasible; false otherwise.
 */
bool Solution::isFeasible() const {
    return (this->isPartition() && this->isConnected() && 
            this->respectsCapacity() && this->isBalanced());
}

/*
 * Write this solution into the specified output stream.
 *
 * @param os the output stream to write into.
 */
void Solution::write(std::ostream & os) const {
    for (const std::set<Edge> & district : this->districts) {
        os << district.size() << std::endl;
    }

    for (const std::set<Edge> & district : this->districts) {
        for (const Edge & e : district) {
            e.write(os);
        }
    }
}

/*
 * Write this solution into the specified file.
 *
 * @param filename the file to write into.
 */
void Solution::write(const char * filename) const {
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
 * Write this solution into the specified file.
 *
 * @param filename the file to write into.
 */
void Solution::write(const std::string & filename) const {
    this->write(filename.c_str());
}

/*
 * Write this solution into the standard output stream.
 */
void Solution::write() const {
    this->write(std::cout);
}

