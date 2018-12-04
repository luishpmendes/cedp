#pragma once

#include <iostream>

/*
 * The Vertex class represents a weighted vertex.
 */
class Vertex {
    public:
        /* This vertex's identifier. */
        unsigned int v;

        /* This vertex's x coordinate. */
        double x;

        /* This vertex's y coordinate. */
        double y;

        /* This vertex's weight. */
        double w;

        /*
         * Constructs a new weighted vertex.
         *
         * @param v the new vertex's identifier.
         * @param x the new vertex's x coordinate.
         * @param y the new vertex's y coordinate.
         * @param w the new vertex's weight.
         */
        Vertex(unsigned int v, double x, double y, double w);

        /*
         * Constructs a new weighted vertex.
         *
         * @param v the new vertex's identifier.
         * @param w the new vertex's weight.
         */
        Vertex(unsigned int v, double w);

        /*
         * Constructs a new weighted vertex.
         *
         * @param v the new vertex's identifier.
         * @param x the new vertex's x coordinate.
         * @param y the new vertex's y coordinate.
         */
        Vertex(unsigned int v, double x, double y);

        /*
         * Constructs a new unweighted vertex.
         *
         * @param v the new vertex's identifier.
         */
        Vertex(unsigned int v);

        /* Constructs a null vertex. */
        Vertex();

        /*
         * Write this vertex into the specified output stream.
         *
         * @param os the output stream to write into.
         */
        void write(std::ostream & os) const;

        /*
         * Write this vertex into the specified file.
         *
         * @param filename the file to write into.
         */
        void write(const char * filename) const;

        /*
         * Write this vertex into the standard output stream.
         */
        void write() const;

        /*
         * Indicates whether some vertex is equals to this one.
         *
         * @param v the reference vertex to which to compare.
         *
         * @return true if this vertex is the same as the v argument; false otherwise.
         */
        bool operator == (const Vertex & v) const;

        /*
         * Compares this vertex with the specified vertex for order, 
         * indicating whether this vertex is less than the specified one.
         *
         * @param v the vertex to be compared.
         *
         * @return true if this vertex is less than the specified vertex; false otherwise.
         */
        bool operator < (const Vertex & v) const;

        /*
         * Compared this vertex with the specified vertex for order, 
         * indicating whether this* vertex is greater than the specified one.
         *
         * @param v the vertex to be compared.
         *
         * @return true if this vertex is grater than the specified vertex; false otherwise.
         */
        bool operator > (const Vertex & v) const;

        /*
         * Compares the weight of the specified vertices.
         *
         * @param u the first vertex been compared.
         * @param v the second vertex been compared.
         *
         * @return true if the weight of the first edge is less than the weight of 
                   the second one; false otherwise
         */
        static bool weightComparator(const Vertex & u, const Vertex & v);
};

