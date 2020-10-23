#pragma once

#include "../graph/Graph.hpp"

/*
 * The Instance class represents an instance of the CEDP.
 */
class Instance {
    private:
        /* This instance's number of districts. */
        unsigned int m;

        /* This instance's maximum capacity of each district. */
        unsigned int D;

        /* This instance's maximum imbalance allowed for each district. */
        double B;

        /* This instance's connected undirected weighted graph. */
        Graph G;

        /* This instance's line graph. */
        Graph LG;

        /* This instance's G' */
        Graph GPrime;

        /* This instance's G' artificial vertex. */
        Vertex ePrime;

        /* This instance's profit obtained by allocating each edge in each district. */
        std::vector<std::vector<double> > c;

        /* This instance's minimum allowed demand for each district. */
        double minimumDemand;

        /* This instance's maximum allowed demand for each district. */
        double maximumDemand;

        /* Define this instance's minimum and maximum allowed demand. */
        void defineMinimumAndMaximumDemand();

        /*
         * Initializes a new instance.
         *
         * @param is the input stream to read from.
         */
        void init(std::istream & is);

        /*
         * Initializes a new instance with random costs.
         *
         * @param m         the new instance's number of districts.
         * @param D         the new instance's maximum capacity of each district.
         * @param B         the new instance's maximum imbalance allowed for each district.
         * @param G         the new instance's connected undirected graph.
         * @param generator the pseudo-random numbers generator.
         */
        void init(unsigned int m, unsigned int D, double B, const Graph & G, 
                std::mt19937 generator);

    public:
        /*
         * Constructs a new instance.
         *
         * @param m the new instance's number of districts.
         * @param D the new instance's maximum capacity of each district.
         * @param B the new instance's maximum imbalance allowed for each district.
         * @param G the new instance's connected undirected graph.
         * @param c the new instance's profit obtained by allocating each edge in each district.
         */
        Instance(unsigned int m, unsigned int D, double B, const Graph & G, 
                std::vector<std::vector<double> > c);

        /*
         * Constructs a new instance.
         *
         * @param is the input stream to read from.
         */
        Instance(std::istream & is);

        /*
         * Constructs a new instance.
         *
         * @param filename the file to read from.
         */
        Instance(const char * filename);

        /*
         * Constructs a new instance.
         *
         * @param filename the file to read from.
         */
        Instance(const std::string & filename);

        /*
         * Constructs a new instance with random costs.
         *
         * @param m         the new instance's number of districts.
         * @param D         the new instance's maximum capacity of each district.
         * @param B         the new instance's maximum imbalance allowed for each district.
         * @param G         the new instance's connected undirected graph.
         * @param generator the pseudo-random numbers generator.
         */
        Instance(unsigned int m, unsigned int D, double B, const Graph & G, 
                std::mt19937 generator);

        /*
         * Constructs a new instance with random costs.
         *
         * @param m    the new instance's number of districts.
         * @param D    the new instance's maximum capacity of each district.
         * @param B    the new instance's maximum imbalance allowed for each district.
         * @param G    the new instance's connected undirected graph.
         * @param seed the seed for the pseudo-random numbers generator.
         */
        Instance(unsigned int m, unsigned int D, double B, const Graph & G, unsigned int seed);

        /*
         * Constructs a new instance with random costs.
         *
         * @param m the new instance's number of districts.
         * @param D the new instance's maximum capacity of each district.
         * @param B the new instance's maximum imbalance allowed for each district.
         * @param G the new instance's connected undirected graph.
         */
        Instance(unsigned int m, unsigned int D, double B, const Graph & G);

        /*
         * Constructs a new instance with random costs.
         *
         * @param G         the new instance's connected undirected graph.
         * @param generator the pseudo-random numbers generator
         */
        Instance(const Graph & G, std::mt19937 generator);

        /*
         * Constructs a new instance with random costs.
         *
         * @param G    the new instance's connected undirected graph.
         * @param seed the seed for the pseudo-random numbers generator
         */
        Instance(const Graph & G, unsigned int seed);

        /*
         * Constructs a new instance with random costs.
         *
         * @param G the new instance's connected undirected graph.
         */
        Instance(const Graph & G);

        /*
         * Constructs a new empty instance.
         */
        Instance();

        /*
         * Verifies whether this instance is empty.
         *
         * @return true if this instance is empty; false otherwise.
         */
        bool isEmpty() const;

        /*
         * Returns this instance's number of districts.
         *
         * @return this instance's number of districts.
         */
        unsigned int getM() const;

        /*
         * Returns this instance's maximum capacity of each district.
         *
         * @return this instance's maximum capacity of each district.
         */
        unsigned int getD() const;

        /*
         * Returns this instance's maximum imbalance allowed for each district.
         *
         * @return this instance's maximum imbalance allowed for each district.
         */
        double getB() const;

        /*
         * Returns this instance's connected undirected weighted graph.
         *
         * @return this instance's connected undirected weighted graph.
         */
        Graph getG() const;

        /*
         * Returns this instance's line graph.
         *
         * @return this instance's line graph.
         */
        Graph getLG() const;

        /*
         * Returns this instance's G'.
         *
         * @return this instance's G'.
         */
        Graph getGPrime() const;

        /* 
         * Returns this instance's G' artificial vertex.
         *
         * @return this instance's G' artificial vertex.
         */
        Vertex getEPrime() const;

        /*
         * Returns this instance's profit obtained by allocating each edge in each district.
         *
         * @return this instance's profit obtained by allocating each edge in each district.
         */
        std::vector<std::vector<double> > getC() const;

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
        double getC(unsigned int eId, unsigned int j) const;

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
        double getC(Edge e, unsigned int j) const;

        /*
         * Returns this instance's minimum allowed demand for each district.
         *
         * @return this instance's minimum allowed demand for each district.
         */
        double getMinimumDemand() const;

        /*
         * Returns this instance's maximum allowed demand for each district.
         *
         * @return this instance's maximum allowed demand for each district.
         */
        double getMaximumDemand() const;

        /*
         * Write this instance into the specified output stream.
         *
         * @param os the output stream to write into.
         */
        void write(std::ostream & os) const;

        /*
         * Write this instance into the specified file.
         *
         * @param filename the file to write into.
         */
        void write(const char * filename) const;

        /*
         * Write this instance into the standard output stream.
         */
        void write() const;
};

