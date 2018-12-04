#include "Vertex.hpp"
#include <cmath>
#include <fstream>

/*
 * Constructs a new weighted vertex.
 *
 * @param v the new vertex's identifier.
 * @param x the new vertex's x coordinate.
 * @param y the new vertex's y coordinate.
 * @param w the new vertex's weight.
 */
Vertex::Vertex(unsigned int v, double x, double y, double w) : v(v), x(x), y(y), w(w) {}


/*
 * Constructs a new weighted vertex.
 *
 * @param v the new vertex's identifier.
 * @param x the new vertex's x coordinate.
 * @param y the new vertex's y coordinate.
 */
Vertex::Vertex(unsigned int v, double x, double y) : Vertex::Vertex(v, x, y, 0.0) {}

/*
 * Constructs a new weighted vertex.
 *
 * @param v the new vertex's identifier.
 * @param w the new vertex's weight.
 */
Vertex::Vertex(unsigned int v, double w) : Vertex::Vertex(v, 0.0, 0.0, w) {}

/*
 * Constructs a new unweighted vertex.
 *
 * @param v the new vertex's identifier.
 */
Vertex::Vertex(unsigned int v) : Vertex::Vertex(v, 0.0) {}

/* Constructs a null vertex. */
Vertex::Vertex() : Vertex(0) {}

/*
 * Write this vertex into the specified output stream.
 *
 * @param os the output stream to write into.
 */
void Vertex::write(std::ostream & os) const {
    os << this->x << " " << this->y << std::endl;
}

/*
 * Write this vertex into the specified file.
 *
 * @param filename the file to write into.
 */
void Vertex::write(const char * filename) const {
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
 * Write this vertex into the standard output stream.
 */
void Vertex::write() const {
    this->write(std::cout);
}

/*
 * Indicates whether some vertex is equals to this one.
 *
 * @param v the reference vertex to which to compare.
 *
 * @return true if this vertex is the same as the v argument; false otherwise.
 */
bool Vertex::operator == (const Vertex & v) const {
    return (this->v == v.v && fabs(this->x - v.x) < 1E-7 && 
            fabs(this->y - v.y) < 1E-7 && this->w == v.w);
}

/*
 * Compares this vertex with the specified vertex for order, 
 * indicating whether this vertex is less than the specified one.
 *
 * @param v the vertex to be compared.
 *
 * @return true if this vertex is less than the specified vertex; false otherwise.
 */
bool Vertex::operator < (const Vertex & v) const {
    if (this->v == v.v) {
        if (this->x == v.x) {
            if (this->y == v.y) {
                return (this->w < v.w);
            }

            return (this->y < v.y);
        }

        return (this->x < v.x);
    }

    return (this->v < v.v);
}

/*
 * Compared this vertex with the specified vertex for order, 
 * indicating whether this* vertex is greater than the specified one.
 *
 * @param v the vertex to be compared.
 *
 * @return true if this vertex is grater than the specified vertex; false otherwise.
 */
bool Vertex::operator > (const Vertex & v) const {
    if (this->v == v.v) {
        if (this->x == v.x) {
            if (this->y == v.y) {
                return (this->w > v.w);
            }

            return (this->y > v.y);
        }

        return (this->x > v.x);
    }

    return (this->v > v.v);
}

/*
 * Compares the weight of the specified vertices.
 *
 * @param u the first vertex been compared.
 * @param v the second vertex been compared.
 *
 * @return true if the weight of the first edge is less than the weight of 
           the second one; false otherwise
 */
bool Vertex::weightComparator(const Vertex & u, const Vertex & v) {
    return u.w < v.w;
}

