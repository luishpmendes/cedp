#include "Instance.hpp"
#include <chrono>
#include <fstream>

/* Define this instance's minimum and maximum allowed demand. */
void Instance::defineMinimumAndMaximumDemand() {
    this->minimumDemand = 2.0 * this->G.getEdgesWeight();
    this->maximumDemand = 2.0 * this->G.getEdgesWeight();;

    this->minimumDemand *= (1.0 - this->B) / ((double) this->m);
    this->maximumDemand *= (1.0 + this->B) / ((double) this->m);

    if (this->maximumDemand > this->D) {
        this->maximumDemand = this->D;
    }
}

/*
 * Initializes a new instance.
 *
 * @param is the input stream to read from.
 */
void Instance::init(std::istream & is) {
    is >> this->m >> this->D >> this->B;

    /* G = (V, E) */
    this->G = Graph(is);
    /* L(G) = (U, A) */
    this->LG = this->G.getLineGraph();
    /* G′ = (U′, A′) */
    this->GPrime = Graph(this->LG);
    /* e′ */
    this->ePrime = Vertex(this->LG.getMaxV() + 1);
    /* U′ = U ∪ {e′} */
    this->GPrime.addVertex(ePrime);

    /* A′ = A ∪ {{e′, e} : e ∈ U} */
    for (const Vertex & e : this->LG.getVertices()) {
        this->GPrime.addEdge(ePrime, e);
    }

    this->c = std::vector<std::vector<double> > (this->G.m(), std::vector<double> (this->m));

    for (unsigned int e = 0; e < this->G.m(); e++) {
        for (unsigned int j = 0; j < this->m; j++) {
            is >> this->c[e][j];
        }
    }

    this->defineMinimumAndMaximumDemand();
}

/*
 * Initializes a new instance with random costs.
 *
 * @param m         the new instance's number of districts.
 * @param D         the new instance's maximum capacity of each district.
 * @param B         the new instance's maximum imbalance allowed for each district.
 * @param G         the new instance's connected undirected graph.
 * @param generator the pseudo-random numbers generator.
 */
void Instance::init(unsigned int m, unsigned int D, double B, const Graph & G, 
        std::mt19937 generator) {
    generator.discard(1000);
    this->m = m;
    this->D = D;
    this->B = B;
    /* G = (V, E) */
    this->G = Graph(G);
    /* L(G) = (U, A) */
    this->LG = this->G.getLineGraph();
    /* G′ = (U′, A′) */
    this->GPrime = Graph(this->LG);
    /* e′ */
    this->ePrime = Vertex(this->LG.getMaxV() + 1);
    /* U′ = U ∪ {e′} */
    this->GPrime.addVertex(ePrime);

    /* A′ = A ∪ {{e′, e} : e ∈ U} */
    for (const Vertex & e : this->LG.getVertices()) {
        this->GPrime.addEdge(ePrime, e);
    }

    this->c = std::vector<std::vector<double> > (this->G.m(), std::vector<double> (this->m));

    std::uniform_int_distribution<unsigned int> distribution(0, this->m * this->G.m() - 1);

    for (unsigned int e = 0; e < this->G.m(); e++) {
        for (unsigned int j = 0; j < this->m; j++) {
            this->c[e][j] = distribution(generator);
        }
    }

    this->defineMinimumAndMaximumDemand();
}
        
/*
 * Constructs a new instance.
 *
 * @param m the new instance's number of districts.
 * @param D the new instance's maximum capacity of each district.
 * @param B the new instance's maximum imbalance allowed for each district.
 * @param G the new instance's connected undirected graph.
 * @param c the new instance's profit obtained by allocating each edge in each district.
 */
Instance::Instance(unsigned int m, unsigned int D, double B, const Graph & G, 
        std::vector<std::vector<double> > c) : m(m), D(D), B(B), G(G), c(c) {
    this->defineMinimumAndMaximumDemand();
}

/*
 * Constructs a new instance.
 *
 * @param is the input stream to read from.
 */
Instance::Instance(std::istream & is) {
    this->init(is);
}

/*
 * Constructs a new instance.
 *
 * @param filename the file to read from.
 */
Instance::Instance(const char * filename) {
    std::ifstream ifs;
    ifs.open(filename);

    if (ifs.is_open()) {
        this->init(ifs);
    } else {
        throw "File not found.";
    }
}

/*
 * Constructs a new instance.
 *
 * @param filename the file to read from.
 */
Instance::Instance(const std::string & filename) : Instance::Instance(filename.c_str()) {}

/*
 * Constructs a new instance with random costs.
 *
 * @param m         the new instance's number of districts.
 * @param D         the new instance's maximum capacity of each district.
 * @param B         the new instance's maximum imbalance allowed for each district.
 * @param G         the new instance's connected undirected graph.
 * @param generator the pseudo-random numbers generator.
 */
Instance::Instance(unsigned int m, unsigned int D, double B, const Graph & G, 
        std::mt19937 generator) {
    this->init(m, D, B, G, generator);
}

/*
 * Constructs a new instance with random costs.
 *
 * @param m    the new instance's number of districts.
 * @param D    the new instance's maximum capacity of each district.
 * @param B    the new instance's maximum imbalance allowed for each district.
 * @param G    the new instance's connected undirected graph.
 * @param seed the seed for the pseudo-random numbers generator.
 */
Instance::Instance(unsigned int m, unsigned int D, double B, const Graph & G, 
        unsigned int seed) : Instance::Instance(m, D, B, G, 
            std::mt19937(seed)) {}

/*
 * Constructs a new instance with random costs.
 *
 * @param m the new instance's number of districts.
 * @param D the new instance's maximum capacity of each district.
 * @param B the new instance's maximum imbalance allowed for each district.
 * @param G the new instance's connected undirected graph.
 */
Instance::Instance(unsigned int m, unsigned int D, double B, const Graph & G) 
    : Instance::Instance(m, D, B, G, 
            std::chrono::system_clock::now().time_since_epoch().count()) {}

/*
 * Constructs a new instance with random costs.
 *
 * @param G         the new instance's connected undirected graph.
 * @param generator the pseudo-random numbers generator.
 */
Instance::Instance(const Graph & G, std::mt19937 generator) {
    unsigned int m = round(sqrt(G.m()));
    double dE = G.getEdgesWeight();
    unsigned int D = round(((2.0 * (1.0 + 0.2)) / ((double) m)) * ((double) dE));
    double B = 0.25;

    this->init(m, D, B, G, generator);
}

/*
 * Constructs a new instance with random costs.
 *
 * @param G    the new instance's connected undirected graph.
 * @param seed the seed for the pseudo-random numbers generator
 */
Instance::Instance(const Graph & G, unsigned int seed) : Instance::Instance(G, 
        std::mt19937(seed)) {}

/*
 * Constructs a new instance with random costs.
 *
 * @param G the new instance's connected undirected graph.
 */
Instance::Instance(const Graph & G) : Instance::Instance(G, 
        std::chrono::system_clock::now().time_since_epoch().count()) {}

/*
 * Constructs a new empty instance.
 */
Instance::Instance() : m(0), D(0), B(0.0), G(), c(), minimumDemand(0.0), maximumDemand(0.0) {}

/*
 * Verifies whether this instance is empty.
 *
 * @return true if this instance is empty; false otherwise.
 */
bool Instance::isEmpty() const {
    return (this->G.isEmpty() && this->c.empty());
}

/*
 * Returns this instance's number of districts.
 *
 * @return this instance's number of districts.
 */
unsigned int Instance::getM() const {
    return this->m;
}

/*
 * Returns this instance's maximum capacity of each district.
 *
 * @return this instance's maximum capacity of each district.
 */
unsigned int Instance::getD() const {
    return this->D;
}

/*
 * Returns this instance's maximum imbalance allowed for each district.
 *
 * @return this instance's maximum imbalance allowed for each district.
 */
double Instance::getB() const {
    return this->B;
}

/*
 * Returns this instance's connected undirected weighted graph.
 *
 * @return this instance's connected undirected weighted graph.
 */
Graph Instance::getG() const {
    return this->G;
}

/*
 * Returns this instance's line graph.
 *
 * @return this instance's line graph.
 */
Graph Instance::getLG() const {
    return this->LG;
}

/*
 * Returns this instance's G'.
 *
 * @return this instance's G'.
 */
Graph Instance::getGPrime() const {
    return this->GPrime;
}

/* 
 * Returns this instance's G' artificial vertex.
 *
 * @return this instance's G' artificial vertex.
 */
Vertex Instance::getEPrime() const {
    return this->ePrime;
}

/*
 * Returns this instance's profit obtained by allocating each edge in each district.
 *
 * @return this instance's profit obtained by allocating each edge in each district.
 */
std::vector<std::vector<double> > Instance::getC() const {
    return std::vector<std::vector<double> >(this->c);
}

/*
 * Returns this instance's profit obtained by allocating the specified 
 * edge in the specified district.
 *
 * @param eId the edge id.
 * @param j   the district id.
 *
 * @return this instance's profit obtained by allocating the specified
 *         edge in the specified district.
 */
double Instance::getC(unsigned int eId, unsigned int j) const {
    if (eId >= 1 && eId <= this->G.m() && j < this->m) {
        return this->c[eId - 1][j];
    }

    return 0.0;
}

/*
 * Returns this instance's profit obtained by allocating the specified 
 * edge in the specified district.
 *
 * @param e the edge.
 * @param j the district id.
 *
 * @return this instance's profit obtained by allocating the specified
 *         edge in the specified district.
 */
double Instance::getC(Edge e, unsigned int j) const {
    unsigned int eId = this->G.getEdgeId(e);

    return this->getC(eId, j);
}

/*
 * Returns this instance's minimum allowed demand for each district.
 *
 * @return this instance's minimum allowed demand for each district.
 */
double Instance::getMinimumDemand() const {
    return this->minimumDemand;
}

/*
 * Returns this instance's maximum allowed demand for each district.
 *
 * @return this instance's maximum allowed demand for each district.
 */
double Instance::getMaximumDemand() const {
    return this->maximumDemand;
}

/*
 * Write this instance into the specified output stream.
 *
 * @param os the output stream to write into.
 */
void Instance::write(std::ostream & os) const {
    os << this->m << std::endl;
    os << this->D << std::endl;
    os << this->B << std::endl;

    this->G.write(os);

    for (unsigned int e = 0; e < this->G.m(); e++) {
        if (this->m > 0) {
            os << this->c[e][0];
        }

        for (unsigned int j = 1; j < this->m; j++) {
            os << " " << this->c[e][j];
        }

        os << std::endl;
    }
}

/*
 * Write this instance into the specified file.
 *
 * @param filename the file to write into.
 */
void Instance::write(const char * filename) const {
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
 * Write this instance into the standard output stream.
 */
void Instance::write() const {
    this->write(std::cout);
}

