#include "Edge.hpp"
#include <fstream>

/*
 * Constructs a new weighted edge.
 *
 * @param u the new edge's first endpoint.
 * @param v the new edge's second endpoint.
 * @param w the new edge's weight.
 */
Edge::Edge(Vertex u, Vertex v, double w) : w(w) {
    if (u < v) {
        this->u = u;
        this->v = v;
    } else {
        this->u = v;
        this->v = u;
    }
}

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
Edge::Edge(unsigned int u, double xu, double yu, double wu, unsigned int v, 
        double xv, double yv, double wv, double w) : 
    Edge::Edge(Vertex(u, xu, yu, wu), Vertex(v, xv, yv, wv), w) {}

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
Edge::Edge(unsigned int u, double xu, double yu, unsigned int v, double xv, 
        double yv, double w) : Edge::Edge(Vertex(u, xu, yu), Vertex(v, xv, yv), w) {}

/*
 * Constructs a new weighted edge.
 *
 * @param u  the new edge's first endpoint identifier.
 * @param wu the new edge's first endpoint weight.
 * @param v  the new edge's second endpoint identifier.
 * @param wv the new edge's second endpoint weight.
 * @param w  the new edge's weight.
 */
Edge::Edge(unsigned int u, double wu, unsigned int v, double wv, double w) : 
    Edge::Edge(Vertex(u, wu), Vertex(v, wv), w) {}

/*
 * Constructs a new weighted edge.
 *
 * @param u the new edge's first endpoint identifier.
 * @param v the new edge's second endpoint identifier.
 * @param w the new edge's weight.
 */
Edge::Edge(unsigned int u, unsigned int v, double w) : Edge::Edge(Vertex(u), Vertex(v), w) {}

/*
 * Constructs a new weighted edge.
 *
 * @param u the new edge's first endpoint.
 * @param v the new edge's second endpoint.
 */
Edge::Edge(Vertex u, Vertex v) : Edge::Edge(u, v, 0.0) {}

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
Edge::Edge(unsigned int u, double xu, double yu, double wu, unsigned int v, 
        double xv, double yv, double wv) : Edge::Edge(u, xu, yu, wu, v, xv, yv, wv, 0.0) {}

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
Edge::Edge(unsigned int u, double xu, double yu, unsigned int v, double xv, 
        double yv) : Edge::Edge(u, xu, yu, v, xv, yv, 0.0) {}

/*
 * Constructs a new weighted edge.
 *
 * @param u  the new edge's first endpoint identifier.
 * @param wu the new edge's first endpoint weight.
 * @param v  the new edge's second endpoint identifier.
 * @param wv the new edge's second endpoint weight.
 */
Edge::Edge(unsigned int u, double wu, unsigned int v, double wv) : 
    Edge::Edge(u, wu, v, wv, 0.0) {}

/*
 * Constructs a new weighted edge.
 *
 * @param u the new edge's first endpoint identifier.
 * @param v the new edge's second endpoint identifier.
 */
Edge::Edge(unsigned int u, unsigned int v) : Edge::Edge(u, v, 0.0) {}

/* Constructs a null edge */
Edge::Edge() : Edge::Edge(0, 0) {}

/*
 * Write this edge into the specified output stream.
 *
 * @param os the output stream to write into.
 */
void Edge::write(std::ostream & os) const {
    os << this->u.v << " " << this->v.v << " " << this->w << std::endl;
}

/*
 * Write this edge into the specified file.
 *
 * @param filename the file to write into.
 */
void Edge::write(const char * filename) const {
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
 * Write this edge into the standard output stream.
 */
void Edge::write() const {
    this->write(std::cout);
}

/*
 * Indicates whether some edge is equals to this one.
 *
 * @param e the reference edge to which to compare.
 *
 * @return true if this edge is the same as the e argument; false otherwise.
 */
bool Edge::operator == (const Edge & e) const {
    return (this->u == e.u && this->v == e.v && this->w == e.w);
}

/*
 * Compares this edge with the specified edge for order, 
 * indicating whether this edge is less than the specified one.
 *
 * @param e the edge to be compared.
 *
 * @return true if this edge is less than the specified edge; false otherwise.
 */
bool Edge::operator < (const Edge & e) const {
    if (this->u == e.u) {
        if (this->v == e.v) {
            return (this->w < e.w);
        }

        return (this->v < e.v);
    }

    return (this->u < e.u);
}

/*
 * Compares this edge with the specified edge for order, 
 * indicating whether this edge is greater than the specified one.
 *
 * @param e the edge to be compared.
 *
 * @return true if this edge is greater than the specified edge; false otherwise.
 */
bool Edge::operator > (const Edge & e) const {
    if (this->u == e.u) {
        if (this->v == e.v) {
            return (this->w > e.w);
        }

        return (this->v > e.v);
    }

    return (this->u > e.u);
}

/*
 * Compares the weight of the specified edges.
 *
 * @param e the first edge been compared.
 * @param f the second edge been compared.
 *
 * @return true if the weight of the first edge is less than the weight of 
 *         the second one; false otherwise.
 */
bool Edge::weightComparator(const Edge & e, const Edge & f) {
    return e.w < f.w;
}

