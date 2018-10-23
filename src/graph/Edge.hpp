#pragma once

#include "Vertex.hpp"

/*
 * The Edge class represents an undirected weighted edge connecting two distinct vertices.
 */
class Edge {
    public:
        /* This edge's first endpoint. */
        Vertex u;

        /* This edge's second endpoint. */
        Vertex v;

        /* This edge's weight. */
        double w;

        /*
         * Constructs a new weighted edge.
         *
         * @param u the new edge's first endpoint.
         * @param v the new edge's second endpoint.
         * @param w the new edge's weight.
         */
        Edge(Vertex u, Vertex v, double w);

        /*
         * Constructs a new weighted edge.
         *
         * @param u  the new edge's first endpoint identifier.
         * @param xu the new edge's first endpoint x coordinate.
         * @param yu the new edge's first endpoint y coordinate.
         * @param wu the new edge's first endpoint weight.
         * @param v  the new edge's second endpoint identifier.
         * @param xv the new edge's second endpoint x coordinate.
         * @param yv the new edge's second endpoint y coordinate.
         * @param wv the new edge's second endpoint weight.
         * @param w  the new edge's weight.
         */
        Edge(unsigned int u, double xu, double yu, double wu, unsigned int v, 
                double xv, double yv, double wv, double w);

        /*
         * Constructs a new weighted edge.
         *
         * @param u  the new edge's first endpoint identifier.
         * @param xu the new edge's first endpoint x coordinate.
         * @param yu the new edge's first endpoint y coordinate.
         * @param v  the new edge's second endpoint identifier.
         * @param xv the new edge's second endpoint x coordinate.
         * @param yv the new edge's second endpoint y coordinate.
         * @param w  the new edge's weight.
         */
        Edge(unsigned int u, double xu, double yu, unsigned int v, double xv, 
                double yv, double w);

        /*
         * Constructs a new weighted edge.
         *
         * @param u  the new edge's first endpoint identifier.
         * @param wu the new edge's first endpoint weight.
         * @param v  the new edge's second endpoint identifier.
         * @param wv the new edge's second endpoint weight.
         * @param w  the new edge's weight.
         */
        Edge(unsigned int u, double wu, unsigned int v, double wv, double w);

        /*
         * Constructs a new weighted edge.
         *
         * @param u the new edge's first endpoint identifier.
         * @param v the new edge's second endpoint identifier.
         * @param w the new edge's weight.
         */
        Edge(unsigned int u, unsigned int v, double w);

        /*
         * Constructs a new weighted edge.
         *
         * @param u the new edge's first endpoint.
         * @param v the new edge's second endpoint.
         */
        Edge(Vertex u, Vertex v);

        /*
         * Constructs a new weighted edge.
         *
         * @param u  the new edge's first endpoint identifier.
         * @param xu the new edge's first endpoint x coordinate.
         * @param yu the new edge's first endpoint y coordinate.
         * @param wu the new edge's first endpoint weight.
         * @param v  the new edge's second endpoint identifier.
         * @param xv the new edge's second endpoint x coordinate.
         * @param yv the new edge's second endpoint y coordinate.
         * @param wv the new edge's second endpoint weight.
         */
        Edge(unsigned int u, double xu, double yu, double wu, unsigned int v, 
                double xv, double yv, double wv);

        /*
         * Constructs a new weighted edge.
         *
         * @param u  the new edge's first endpoint identifier.
         * @param xu the new edge's first endpoint x coordinate.
         * @param yu the new edge's first endpoint y coordinate.
         * @param v  the new edge's second endpoint identifier.
         * @param xv the new edge's second endpoint x coordinate.
         * @param yv the new edge's second endpoint y coordinate.
         */
        Edge(unsigned int u, double xu, double yu, unsigned int v, double xv, double yv);

        /*
         * Constructs a new weighted edge.
         *
         * @param u  the new edge's first endpoint identifier.
         * @param wu the new edge's first endpoint weight.
         * @param v  the new edge's second endpoint identifier.
         * @param wv the new edge's second endpoint weight.
         */
        Edge(unsigned int u, double wu, unsigned int v, double wv);

        /*
         * Constructs a new weighted edge.
         *
         * @param u the new edge's first endpoint identifier.
         * @param v the new edge's second endpoint identifier.
         */
        Edge(unsigned int u, unsigned int v);

        /* Constructs a null edge. */
        Edge();

        /*
         * Write this edge into the specified output stream.
         *
         * @param os the output stream to write into.
         */
        void write(std::ostream & os) const;

        /*
         * Write this edge into the specified file.
         *
         * @param filename the file to write into.
         */
        void write(const char * filename) const;

        /*
         * Write this edge into the standard output stream.
         */
        void write() const;

        /*
         * Indicates whether some edge is equals to this one.
         *
         * @param e the reference edge to which to compare.
         *
         * @return true if this edge is the same as the e argument; false otherwise.
         */
        bool operator == (const Edge & e) const;

        /*
         * Compares this edge with the specified edge for order, 
         * indicating whether this edge is less than the specified one.
         *
         * @param e the edge to be compared.
         *
         * @return true if this edge is less than the specified edge; false otherwise.
         */
        bool operator < (const Edge & e) const;

        /*
         * Compares this edge with the specified edge for order, 
         * indicating whether this edge is greater than the specified one.
         *
         * @param e the edge to be compared.
         *
         * @return true if this edge is greater than the specified edge; false otherwise.
         */
        bool operator > (const Edge & e) const;

        /*
         * Compares the weight of the specified edges.
         *
         * @param e the first edge been compared.
         * @param f the second edge been compared.
         *
         * @return true if the weight of the first edge is less than the 
         *         weight of the second one; false otherwise.
         */
        static bool weightComparator(const Edge & e, const Edge & f);
};

