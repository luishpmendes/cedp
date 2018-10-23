#include "Graph.hpp"
#include "../disjoint-sets/DisjointSets.hpp"
#include <algorithm>
#include <chrono>
#include <cfloat>
#include <fstream>
#include <queue>

/* White color constant */
const unsigned int Graph::WHITE = 0;

/* Gray color constant */
const unsigned int Graph::GRAY = 1;

/* Black color constant */
const unsigned int Graph::BLACK = 2;

/*
 * Initializes a new graph.
 *
 * @param vertices the new graph's weighted vertex set.
 * @param edges    the new graph's edge set.
 */
void Graph::init(const std::set<Vertex> & vertices, const std::set<Edge> & edges) {
    this->maxV = 0;
    this->maxVid = 0;

    this->vertices = std::set<Vertex>();
    this->verticesWeight = 0;

    for (Vertex v : vertices) {
        this->addVertex(v);
    }

    this->maxEid = 0;

    this->edges = std::set<Edge>();
    this->edgesWeight = 0;
    this->edge2id = std::map<Edge, unsigned int>();
    this->id2edge = std::vector<Edge>(edges.size(), Edge());
    this->adjacencyLists = std::vector<std::list<std::pair<Vertex, double> > >(
            this->maxVid);
    this->adjacencyMatrix = std::vector<std::vector<double> >(this->maxVid, 
            std::vector<double>(this->maxVid, DBL_MAX));

    for (Edge e : edges) {
        this->addEdge(e);
    }
}

/*
 * Initializes a new graph.
 *
 * @param vertices the new graph's unweighted vertex set.
 * @param edges    the new graph's edge set.
 */
void Graph::init(const std::set<unsigned int> & vertices, const std::set<Edge> & edges) {
    std::set<Vertex> V;

    for (unsigned int v : vertices) {
        V.insert(Vertex(v));
    }

    this->init(V, edges);
}

/*
 * Initializes a new graph.
 *
 * @param is the input stream to read from.
 */
void Graph::init(std::istream & is) {
    unsigned int V, E;
    std::set<Vertex> vertices;
    std::set<Edge> edges;

    is >> V >> E;

    for (unsigned int v = 0; v < V; v++) {
        double x, y;
        is >> x >> y;
        vertices.insert(Vertex(v, x, y));
    }

    for (unsigned int e = 0; e < E; e++) {
        unsigned int u, v;
        double w;
        is >> u >> v >> w;
        edges.insert(Edge(u, v, w));
    }

    this->init(vertices, edges);
}

/*
 * Constructs a new graph.
 *
 * @param vertices the new graph's weighted vertex set.
 * @param edges    the new graph's edge set.
 */
Graph::Graph(const std::set<Vertex> & vertices, const std::set<Edge> & edges) {
    this->init(vertices, edges);
}

/*
 * Constructs a new graph.
 *
 * @param vertices the new graph's unweighted vertex set.
 * @param edges    the new graph's edge set.
 */
Graph::Graph(const std::set<unsigned int> & vertices, const std::set<Edge> & edges) {
    this->init(vertices, edges);
}

/*
 * Constructs a new graph.
 *
 * @param vertices the new graph's weighted vertex set.
 */
Graph::Graph(const std::set<Vertex> & vertices) : Graph::Graph(vertices, std::set<Edge> ()) {}

/*
 * Constructs a new graph.
 *
 * @param vertices the new graph's unweighted vertex set.
 */
Graph::Graph(const std::set<unsigned int> & vertices) : 
    Graph::Graph(vertices, std::set<Edge> ()) {}

/*
 * Constructs a new graph.
 *
 * @param edges the new graph's edge set.
 */
Graph::Graph(const std::set<Edge> & edges) {
    std::set<Vertex> vertices;

    for (const Edge & e : edges) {
        vertices.insert(e.u);
        vertices.insert(e.v);
    }

    this->init(vertices, edges);
}

/*
 * Constructs a new graph.
 *
 * @param n the size of the new graph's vertex set.
 */
Graph::Graph(unsigned int n) {
    std::set<unsigned int> vertices;
    std::set<Edge> edges;

    for (unsigned int v = 0; v < n; v++) {
        vertices.insert(v);
    }

    this->init(vertices, edges);
}

/*
 * Constructs a new graph.
 *
 * @param is the input stream to read from.
 */
Graph::Graph(std::istream & is) {
    this->init(is);
}

/*
 * Constructs a new graph.
 *
 * @param filename the file to read from.
 */
Graph::Graph(const char * filename) {
    std::ifstream ifs;
    ifs.open(filename);

    if (ifs.is_open()) {
        this->init(ifs);
    } else {
        throw "File not found.";
    }
}

/* Constructs a new empty graph. */
Graph::Graph() : Graph::Graph((unsigned int) 0) {}

/*
 * Returns the edges of a spanning tree of the graph defined by the specified edges.
 *
 * @param E the edges of the graph whose spanning tree is to be returned.
 *
 * @return the edges of a spanning tree of the graph defined by the specified edges.
 */
std::set<Edge> Graph::getSpanningTree(const std::vector<Edge> E) {
    std::set<Vertex> V;

    for (const Edge & e : E) {
        V.insert(e.u);
        V.insert(e.v);
    }

    DisjointSets S (V.size());
    /* T ← ∅ */
    std::set<Edge> T;

    /* ∀ v ∈ V */
    for (const Vertex & v : V) {
        /* Make-Set(v) */
        S.makeSet(v.v); 
    }

    /* ∀ {u, v} ∈ E */
    for (const Edge & e : E) {
        /* if Find-Set(u) ≠ Find-Set(v) */
        if (S.findSet(e.u.v) != S.findSet(e.v.v)) {
            /* T ← T ∪ {{u, v}} */
            T.insert(e);
            /* Union(u, v) */
            S.unionSets(e.u.v, e.v.v);
        }
    }

    return T;
}

/*
 * Verifies whether this graph is empty.
 *
 * @return true if this graph is empty; false otherwise.
 */
bool Graph::isEmpty() const {
    return (this->vertices.empty() && this->edges.empty());
}

/*
 * Returns this graph's vertex set.
 *
 * @return this graph's vertex set.
 */
std::set<Vertex> Graph::getVertices() const {
    return this->vertices;
}

/*
 * Returns the size of this graph's vertex set.
 *
 * @return the size of this graph's vertex set.
 */
unsigned int Graph::n() const {
    return this->vertices.size();
}

/*
 * Returns the id of the specified vertex.
 *
 * @param v the vertex whose id is to be returned.
 *
 * @return the id of the specified vertex.
 */
unsigned int Graph::getVertexId(const Vertex & v) const {
    if (v.v >= this->vertex2id.size()) {
        return 0;
    }

    return this->vertex2id[v.v];
}

/*
 * Returns the id of the specified vertex.
 *
 * @param v the vertex whose id is to be returned.
 *
 * @return the id of the specified vertex.
 */
unsigned int Graph::getVertexId(unsigned int v) const {
    return this->getVertexId(Vertex(v));
}

/*
 * Returns the vertex with the specified id.
 *
 * @param id the whose vertex is to be returned.
 *
 * @return the vertex with the specified id.
 */
Vertex Graph::getVertexById(unsigned int id) const {
    if (id >= this->id2vertex.size()) {
        return Vertex();
    }

    return this->id2vertex[id];
}

/*
 * Returns the vertex with the specified identifier.
 *
 * @param v the identifier of the vertex to be returned.
 *
 * @return the vertex with the specified identifier.
 */
Vertex Graph::getVertex(unsigned int v) const {
    return this->getVertexById(this->getVertexId(v));
}

/*
 * Returns the greatest vertex.
 *
 * @return the greatest vertex.
 */
unsigned int Graph::getMaxV() const {
    return this->maxV;
}

/*
 * Returns the greatest vertex id.
 *
 * @return the greatest vertex id.
 */
unsigned int Graph::getMaxVid() const {
    return this->maxVid;
}

/*
 * Returns true if this graph has the specified vertex with the specified id.
 *
 * @param v  the vertex whose presence in this graph is to be tested.
 * @param id the id of the vertex whose presence in this graph is to be tested.
 *
 * @return true if this graph has the specified vertex with the specified id; 
 *         false otherwise.
 */
bool Graph::hasVertex(const Vertex & v, unsigned int id) const {
    if (id != 0) {
        return (this->getVertexId(v) == id && this->getVertexById(id) == v);
    }

    return false;
}

/*
 * Returns true if this graph has the specified vertex with the specified id.
 *
 * @param v  the vertex whose presence in this graph is to be tested.
 * @param id the id of the vertex whose presence in this graph is to be tested.
 *
 * @return true if this graph has the specified vertex with the specified id; 
 *         false otherwise.
 */
bool Graph::hasVertex(unsigned int v, unsigned int id) const {
    return this->hasVertex(this->getVertex(v), id);
}

/*
 * Returns true if this graph has the specified vertex.
 *
 * @param v the vertex whose presence in this graph is to be tested.
 *
 * @return true if this graph has the specified vertex; false otherwise.
 */
bool Graph::hasVertex(const Vertex & v) const {
    return this->hasVertex(v, this->getVertexId(v));
}

/*
 * Returns true if this graph has the specified vertex.
 *
 * @param v the vertex whose presence in this graph is to be tested.
 *
 * @return true if this graph has the specified vertex; false otherwise.
 */
bool Graph::hasVertex(unsigned int v) const {
    return this->hasVertex(v, this->getVertexId(v));
}

/*
 * Returns true if this graph has a vertex with the specified id.
 *
 * @param id the vertex id whose presence in this graph is to be tested.
 *
 * @return true if this graph has a vertex with the specified id; false otherwise.
 */
bool Graph::hasVertexId(unsigned int id) const {
    return this->hasVertex(this->getVertexById(id), id);
}

/*
 * Adds the specified vertex with the specified id to this graph.
 *
 * @param v  the vertex to be added to this graph.
 * @param id the id of the vertex to be add to this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::addVertex(const Vertex & v, unsigned int id) {
    if (id == 0 || this->hasVertex(v)) {
        return false;
    }

    while (this->vertex2id.size() <= v.v) {
        this->vertex2id.push_back(0);
    }

    while (this->id2vertex.size() <= id) {
        this->id2vertex.push_back(Vertex());
    }

    this->vertex2id[v.v] = id;
    this->id2vertex[id] = v;
    this->vertices.insert(v);
    this->verticesWeight += v.w;

    if (this->maxV < v.v) {
        this->maxV = v.v;
    }

    if (this->maxVid < id) {
        this->maxVid = id;
    }

    while (this->adjacencyLists.size() <= this->maxVid) {
        this->adjacencyLists.push_back(std::list<std::pair<Vertex, double> > ());
    }

    for (unsigned int i = 0; i < this->adjacencyMatrix.size(); i++) {
        while (this->adjacencyMatrix[i].size() <= this->maxVid) {
            this->adjacencyMatrix[i].push_back(DBL_MAX);
        }
    }

    while (this->adjacencyMatrix.size() <= this->maxVid) {
        this->adjacencyMatrix.push_back(std::vector<double>(this->maxVid, DBL_MAX));
    }

    return true;
}

/*
 * Adds the specified vertex with the specified id to this graph.
 *
 * @param v  the vertex to be added to this graph.
 * @param x  the x coordinate of the vertex to be added to this graph.
 * @param y  the y coordinate of the vertex to be added to this graph.
 * @param w  the weight of the vertex to be added to this graph.
 * @param id the id of the vertex to be added to this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::addVertex(unsigned int v, double x, double y, double w, unsigned int id) {
    return this->addVertex(Vertex(v, x, y, w), id);
}

/*
 * Adds the specified vertex with the specified id to this graph.
 *
 * @param v  the vertex to be added to this graph.
 * @param x  the x coordinate of the vertex to be added to this graph.
 * @param y  the y coordinate of the vertex to be added to this graph.
 * @param id the id of the vertex to be added to this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::addVertex(unsigned int v, double x, double y, unsigned int id) {
    return this->addVertex(Vertex(v, x, y), id);
}

/*
 * Adds the specified vertex with the specified id to this graph.
 *
 * @param v  the vertex to be added to this graph.
 * @param w  the weight of the vertex to be added to this graph.
 * @param id the id of the vertex to be added to this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::addVertex(unsigned int v, double w, unsigned int id) {
    return this->addVertex(Vertex(v, w), id);
}

/*
 * Adds the specified vertex with the specified id to this graph.
 *
 * @param v  the vertex to be added to this graph.
 * @param id the id of the vertex to be added to this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::addVertex(unsigned int v, unsigned int id) {
    return this->addVertex(Vertex(v), id);
}

/*
 * Adds the specified vertex to this graph.
 *
 * @param v the vertex to be added to this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::addVertex(const Vertex & v) {
    return this->addVertex(v, this->maxVid + 1);
}

/*
 * Adds the specified vertex to this graph.
 *
 * @param v the vertex to be added to this graph.
 * @param x the x coordinate of the vertex to be added to this graph.
 * @param y the y coordinate of the vertex to be added to this graph.
 * @param w the weight of the vertex to be added to this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::addVertex(unsigned int v, double x, double y, double w) {
    return this->addVertex(v, x, y, w, this->maxVid + 1);
}

/*
 * Adds the specified vertex to this graph.
 *
 * @param v the vertex to be added to this graph.
 * @param x the x coordinate of the vertex to be added to this graph.
 * @param y the y coordinate of the vertex to be added to this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::addVertex(unsigned int v, double x, double y) {
    return this->addVertex(v, x, y, this->maxVid + 1);
}

/*
 * Adds the specified vertex to this graph.
 *
 * @param v the vertex to be added to this graph.
 * @param w the weight of the vertex to be added to this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::addVertex(unsigned int v, double w) {
    return this->addVertex(v, w, this->maxVid + 1);
}

/*
 * Adds the specified vertex to this graph.
 *
 * @param v the vertex to be added to this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::addVertex(unsigned int v) {
    return this->addVertex(v, this->maxVid + 1);
}

/*
 * Removes the specified vertex from this graph.
 *
 * @param v the vertex to be removed from this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::removeVertex(const Vertex & v) {
    if (!this->hasVertex(v)) {
        return false;
    }

    for (const Edge & e : this->getIncidentEdges(v)) {
        this->removeEdge(e);
    }

    this->id2vertex[this->getVertexId(v)] = Vertex();
    this->vertex2id[v.v] = 0;
    this->vertices.erase(v);
    this->verticesWeight -= v.w;

    while (!this->hasVertex(this->maxV)) {
        this->maxV--;
    }

    while (!this->hasVertexId(this->maxVid)) {
        this->maxVid--;
    }

    return true;
}

/*
 * Removes the specified vertex from this graph.
 *
 * @param v the vertex to be removed from this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::removeVertex(unsigned int v) {
    return this->removeVertex(Vertex(v));
}

/*
 * Removes the vertex with the specified if from this graph.
 *
 * @param id the id of the vertex to be removed from this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::removeVertexById(unsigned int id) {
    if (!this->hasVertexId(id)) {
        return false;
    }

    return this->removeVertex(this->getVertexById(id));
}

/*
 * Returns the sum of the weights of this graph's vertices.
 *
 * @return the sum of the weights of this graph's vertices.
 */
double Graph::getVerticesWeight() const {
    return this->verticesWeight;
}

/*
 * Returns this graph's edge set.
 *
 * @return this graph's edge set.
 */
std::set<Edge> Graph::getEdges() const {
    return this->edges;
}

/*
 * Returns this size of this graph's vertex set.
 *
 * @return this size of this graph's vertex set.
 */
unsigned int Graph::m() const {
    return this->edges.size();
}

/*
 * Returns the id of the specified edge.
 *
 * @param e the edge whose id is to be returned.
 *
 * @return the id of the specified edge.
 */
unsigned int Graph::getEdgeId(const Edge & e) const {
    unsigned int id;

    try {
        id = this->edge2id.at(e);
    } catch (const std::out_of_range & orr) {
        id = 0;
    }

    return id;
}

/*
 * Returns the id of the specified edge.
 *
 * @param u the first endpoint of the edge whose id is to be returned.
 * @param v the second endpoint of the edge whose id is to be returned.
 * @param w the weight of the edge whose id is to be returned.
 *
 * @return the id of the specified edge.
 */
unsigned int Graph::getEdgeId(const Vertex & u, const Vertex & v, double w) const {
    return this->getEdgeId(Edge(u, v, w));
}

/*
 * Returns the id of the specified edge.
 *
 * @param u the first endpoint of the edge whose id is to be returned.
 * @param v the second endpoint of the edge whose id is to be returned.
 * @param w the weight of the edge whose id is to be returned.
 *
 * @return the id of the specified edge.
 */
unsigned int Graph::getEdgeId(unsigned int u, unsigned int v, double w) const {
    if (!this->hasVertex(u) || !this->hasVertex(v)) {
        return 0;
    }

    return this->getEdgeId(this->getVertex(u), this->getVertex(v), w);
}

/*
 * Returns the id of the specified edge.
 *
 * @param u the first endpoint of the edge whose id is to be returned.
 * @param v the second endpoint of the edge whose id is to be returned.
 *
 * @return the id of the specified edge.
 */
unsigned int Graph::getEdgeId(const Vertex & u, const Vertex & v) const {
    if (!this->hasVertex(u) || !this->hasVertex(v)) {
        return 0;
    }

    unsigned int idU = this->getVertexId(u);
    unsigned int idV = this->getVertexId(v);
    double w = this->adjacencyMatrix[idU - 1][idV - 1];

    return this->getEdgeId(u, v, w);
}

/*
 * Returns the id of the specified edge.
 *
 * @param u the first endpoint of the edge whose id is to be returned.
 * @param v the second endpoint of the edge whose id is to be returned.
 *
 * @return the id of the specified edge.
 */
unsigned int Graph::getEdgeId(unsigned int u, unsigned int v) const {
    if (!this->hasVertex(u) || !this->hasVertex(v)) {
        return 0;
    }

    return this->getEdgeId(this->getVertex(u), this->getVertex(v));
}

/*
 * Returns the edge with the specified id.
 *
 * @param id the whose edge is to be returned.
 *
 * @return the edge with the specified id.
 */
Edge Graph::getEdgeById(unsigned int id) const {
    if (id >= this->id2edge.size()) {
        return Edge();
    }

    return Edge(this->id2edge[id]);
}

/*
 * Returns the edge with the specified endpoints.
 *
 * @param u the first endpoint of the edge to be returned.
 * @param v the second endpoint of the edge to be returned.
 *
 * @return the edge with the specified endpoints.
 */
Edge Graph::getEdge(const Vertex & u, const Vertex & v) const {
    return this->getEdgeById(this->getEdgeId(u, v));
}

/*
 * Returns the edge with the specified endpoints.
 *
 * @param u the first endpoint of the edge to be returned.
 * @param v the second endpoint of the edge to be returned.
 *
 * @return the edge with the specified endpoints.
 */
Edge Graph::getEdge(unsigned int u, unsigned int v) const {
    return this->getEdge(this->getVertex(u), this->getVertex(v));
}

/*
 * Returns the greatest edge id.
 *
 * @return the greatest edge id.
 */
unsigned int Graph::getMaxEid() const {
    return this->maxEid;
}

/*
 * Returns true if this graph has the specified edge with the specified id.
 *
 * @param e  the edge whose presence in this graph is to be tested.
 * @param id the id of the edge whose presence in this graph is to be tested.
 *
 * @return true if this graph has the specified edge with the specified id;
 *         false otherwise.
 */
bool Graph::hasEdge(const Edge & e, unsigned int id) const {
    if (!this->hasVertex(e.u) || !this->hasVertex(e.v)) {
        return false;
    }

    unsigned int idU = this->getVertexId(e.u);
    unsigned int idV = this->getVertexId(e.v);

    return (e.w < DBL_MAX && 
            this->adjacencyMatrix[idU - 1][idV - 1] == e.w && 
            this->adjacencyMatrix[idV - 1][idU - 1] == e.w && 
            this->getEdgeId(e) == id);
}

/*
 * Returns true if this graph has the specified edge with the specified id.
 *
 * @param u  the first endpoint of the edge whose presence in this graph is to be tested.
 * @param v  the second endpoint of the edge whose presence in this graph is to be tested.
 * @param w  the weight of the edge whose presence in this graph is to be tested.
 * @param id the id of the edge whose presence in this graph is to be tested.
 *
 * @return true if this graph has the specified edge with the specified id;
 *         false otherwise.
 */
bool Graph::hasEdge(const Vertex & u, const Vertex & v, double w, unsigned int id) const {
    return (this->hasEdge(Edge(u, v, w), id));
}

/*
 * Returns true if this graph has the specified edge with the specified id.
 *
 * @param u  the first endpoint of the edge whose presence in this graph is to be tested.
 * @param v  the second endpoint of the edge whose presence in this graph is to be tested.
 * @param w  the weight of the edge whose presence in this graph is to be tested.
 * @param id the id of the edge whose presence in this graph is to be tested.
 *
 * @return true if this graph has the specified edge with the specified id;
 *         false otherwise.
 */
bool Graph::hasEdge(unsigned int u, unsigned int v, double w, unsigned int id) const {
    if (!this->hasVertex(u) || !this->hasVertex(v)) {
        return false;
    }

    return this->hasEdge(this->getVertex(u), this->getVertex(v), w, id);
}

/*
 * Returns true if this graph has the specified edge.
 *
 * @param e  the edge whose presence in this graph is to be tested.
 *
 * @return true if this graph has the specified edge; false otherwise.
 */
bool Graph::hasEdge(const Edge & e) const {
    return this->hasEdge(e, this->getEdgeId(e));
}

/*
 * Returns true if this graph has the specified edge.
 *
 * @param u  the first endpoint of the edge whose presence in this 
 *           graph is to be tested.
 * @param v  the second endpoint of the edge whose presence in this 
 *           graph is to be tested.
 * @param w  the weight of the edge whose presence in this graph is to be tested.
 *
 * @return true if this graph has the specified edge; false otherwise.
 */
bool Graph::hasEdge(const Vertex & u, const Vertex & v, double w) const {
    return this->hasEdge(Edge(u, v, w));
}

/*
 * Returns true if this graph has the specified edge.
 *
 * @param u  the first endpoint of the edge whose presence in this graph is to be tested.
 * @param v  the second endpoint of the edge whose presence in this graph is to be tested.
 * @param w  the weight of the edge whose presence in this graph is to be tested.
 *
 * @return true if this graph has the specified edge; false otherwise.
 */
bool Graph::hasEdge(unsigned int u, unsigned int v, double w) const {
    if (!this->hasVertex(u) || !this->hasVertex(v)) {
        return false;
    }

    return this->hasEdge(this->getVertex(u), this->getVertex(v), w);
}

/*
 * Returns true if this graph has the specified edge with the specified id.
 *
 * @param u  the first endpoint of the edge whose presence in this graph is to be tested.
 * @param v  the second endpoint of the edge whose presence in this 
 *           graph is to be tested.
 * @param id the id of the edge whose presence in this graph is to be tested.
 *
 * @return true if this graph has the specified edge with the specified id;
 *         false otherwise.
 */
bool Graph::hasEdge(const Vertex & u, const Vertex & v, unsigned int id) const {
    if (!this->hasVertex(u) || !this->hasVertex(v)) {
        return false;
    }

    unsigned int idU = this->getVertexId(u);
    unsigned int idV = this->getVertexId(u);
    double w = this->adjacencyMatrix[idU - 1][idV - 1];

    return this->hasEdge(u, v, w, id);
}

/*
 * Returns true if this graph has the specified edge with the specified id.
 *
 * @param u  the first endpoint of the edge whose presence in this graph is to be tested.
 * @param v  the second endpoint of the edge whose presence in this graph is to be tested.
 * @param id the id of the edge whose presence in this graph is to be tested.
 *
 * @return true if this graph has the specified edge with the specified id;
 * false otherwise.
 */
bool Graph::hasEdge(unsigned int u, unsigned int v, unsigned int id) const {
    if (!this->hasVertex(u) || !this->hasVertex(v)) {
        return false;
    }

    return this->hasEdge(this->getVertex(u), this->getVertex(v), id);
}

/*
 * Returns true if this graph has the specified edge.
 *
 * @param u the first endpoint of the edge whose presence in this graph is to be tested.
 * @param v the second endpoint of the edge whose presence in this graph is to be tested.
 *
 * @return true if this graph has the specified edge; false otherwise.
 */
bool Graph::hasEdge(const Vertex & u, const Vertex & v) const {
    if (!this->hasVertex(u) || !this->hasVertex(v)) {
        return false;
    }

    unsigned int idU = this->getVertexId(u);
    unsigned int idV = this->getVertexId(v);
    double w = this->adjacencyMatrix[idU - 1][idV - 1];

    return this->hasEdge(u, v, w);
}

/*
 * Returns true if this graph has the specified edge.
 *
 * @param u the first endpoint of the edge whose presence in this graph is to be tested.
 * @param v the second endpoint of the edge whose presence in this graph is to be tested.
 *
 * @return true if this graph has the specified edge; false otherwise.
 */
bool Graph::hasEdge(unsigned int u, unsigned int v) const {
    if (!this->hasVertex(u) || !this->hasVertex(v)) {
        return false;
    }

    return this->hasEdge(this->getVertex(u), this->getVertex(v));
}

/*
 * Returns true if this graph has an edge with the specified id.
 *
 * @param e  the edge whose presence in this graph is to be tested.
 *
 * @return true if this graph has an edge with the specified id; false otherwise.
 */
bool Graph::hasEdgeId(unsigned int id) const {
    return this->hasEdge(this->getEdgeById(id), id);
}

/*
 * Adds the specified edge with the specified id to this graph.
 *
 * @param e  the edge to be added to this graph.
 * @param id the id of the edge to be add to this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::addEdge(const Edge & e, unsigned int id) {
    Vertex u (e.u), v (e.v);

    if (this->hasVertex(u.v)) {
        u = this->getVertex(u.v);
    }

    if (this->hasVertex(v.v)) {
        v = this->getVertex(v.v);
    }

    Edge ee (u, v, e.w);

    if (this->hasEdge(ee.u, ee.v)) {
        return false;
    }

    if (!this->hasVertex(ee.u)) {
        this->addVertex(ee.u);
    }

    if (!this->hasVertex(ee.v)) {
        this->addVertex(ee.v);
    }

    while (id >= this->id2edge.size()) {
        this->id2edge.push_back(Edge());
    }

    unsigned int idU = this->getVertexId(ee.u);
    unsigned int idV = this->getVertexId(ee.v);

    this->edges.insert(Edge(ee));
    this->edge2id[Edge(ee)] = id;
    this->id2edge[id] = Edge(ee);
    this->adjacencyLists[idU - 1].push_back(std::make_pair(ee.v, ee.w));
    this->adjacencyLists[idV - 1].push_back(std::make_pair(ee.u, ee.w));
    this->adjacencyMatrix[idU - 1][idV - 1] = ee.w;
    this->adjacencyMatrix[idV - 1][idU - 1] = e.w;
    this->edgesWeight += ee.w;

    if (this->maxEid < id) {
        this->maxEid = id;
    }

    return true;
}

/*
 * Adds the specified edge with the specified id to this graph.
 *
 * @param u  the first endpoint of the edge to be added to this graph.
 * @param v  the second endpoint of the edge to be added to this graph.
 * @param w  the weight of the edge to be added to this graph.
 * @param id the id of the edge to be add to this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::addEdge(const Vertex & u, const Vertex & v, double w, unsigned int id) {
    Vertex vu (u), vv (v);

    if (this->hasVertex(vu)) {
        vu = this->getVertex(vu.v);
    }

    if (this->hasVertex(vv)) {
        vv = this->getVertex(vv.v);
    }

    return this->addEdge(Edge(vu, vv, w), id);
}

/*
 * Adds the specified edge with the specified id to this graph.
 *
 * @param u  the first endpoint of the edge to be added to this graph.
 * @param v  the second endpoint of the edge to be added to this graph.
 * @param w  the weight of the edge to be added to this graph.
 * @param id the id of the edge to be add to this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::addEdge(unsigned int u, unsigned int v, double w, unsigned int id) {
    Vertex vu (u), vv (v);

    if (this->hasVertex(u)) {
        vu = this->getVertex(u);
    }

    if (this->hasVertex(v)) {
        vv = this->getVertex(v);
    }

    return this->addEdge(vu, vv, w, id);
}

/*
 * Adds the specified edge to this graph.
 *
 * @param e  the edge to be added to this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::addEdge(const Edge & e) {
    Vertex u (e.u), v (e.v);

    if (this->hasVertex(u)) {
        u = this->getVertex(u.v);
    }

    if (this->hasVertex(v)) {
        v = this->getVertex(v.v);
    }

    Edge ee (u, v, e.w);

    return this->addEdge(ee, this->maxEid + 1);
}

/*
 * Adds the specified edge to this graph.
 *
 * @param u  the first endpoint of the edge to be added to this graph.
 * @param v  the second endpoint of the edge to be added to this graph.
 * @param w  the weight of the edge to be added to this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::addEdge(const Vertex & u, const Vertex & v, double w) {
    Vertex vu (u), vv (v);

    if (this->hasVertex(vu)) {
        vu = this->getVertex(vu.v);
    }

    if (this->hasVertex(vv)) {
        vv = this->getVertex(vv.v);
    }

    return this->addEdge(Edge(vu, vv, w));
}

/*
 * Adds the specified edge to this graph.
 *
 * @param u  the first endpoint of the edge to be added to this graph.
 * @param v  the second endpoint of the edge to be added to this graph.
 * @param w  the weight of the edge to be added to this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::addEdge(unsigned int u, unsigned int v, double w) {
    Vertex vu (u), vv (v);

    if (this->hasVertex(u)) {
        vu = this->getVertex(u);
    }

    if (this->hasVertex(v)) {
        vv = this->getVertex(v);
    }

    return this->addEdge(vu, vv, w);
}

/*
 * Adds the specified edge with the specified id to this graph.
 *
 * @param u  the first endpoint of the edge to be added to this graph.
 * @param v  the second endpoint of the edge to be added to this graph.
 * @param id the id of the edge to be add to this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::addEdge(const Vertex & u, const Vertex & v, unsigned int id) {
    Vertex vu (u), vv (v);

    if (this->hasVertex(vu)) {
        vu = this->getVertex(vu.v);
    }

    if (this->hasVertex(vv)) {
        vv = this->getVertex(vv.v);
    }

    return this->addEdge(Edge(vu, vv), id);
}

/*
 * Adds the specified edge with the specified id to this graph.
 *
 * @param u  the first endpoint of the edge to be added to this graph.
 * @param v  the second endpoint of the edge to be added to this graph.
 * @param id the id of the edge to be add to this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::addEdge(unsigned int u, unsigned int v, unsigned int id) {
    Vertex vu (u), vv (v);

    if (this->hasVertex(u)) {
        vu = this->getVertex(u);
    }

    if (this->hasVertex(v)) {
        vv = this->getVertex(v);
    }

    return this->addEdge(vu, vv, id);
}

/*
 * Adds the specified edge to this graph.
 *
 * @param u the first endpoint of the edge to be added to this graph.
 * @param v the second endpoint of the edge to be added to this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::addEdge(const Vertex & u, const Vertex & v) {
    Vertex vu (u), vv (v);

    if (this->hasVertex(vu)) {
        vu = this->getVertex(vu.v);
    }

    if (this->hasVertex(vv)) {
        vv = this->getVertex(vv.v);
    }

    return this->addEdge(Edge(vu, vv));
}

/*
 * Adds the specified edge to this graph.
 *
 * @param u the first endpoint of the edge to be added to this graph.
 * @param v the second endpoint of the edge to be added to this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::addEdge(unsigned int u, unsigned int v) {
    Vertex vu (u), vv (v);

    if (this->hasVertex(u)) {
        vu = this->getVertex(u);
    }

    if (this->hasVertex(v)) {
        vv = this->getVertex(v);
    }

    return this->addEdge(vu, vv);
}

/*
 * Removes the specified edge from this graph.
 *
 * @param e the edge to be removed from this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::removeEdge(const Edge & e) {
    if (!this->hasEdge(e)) {
        return false;
    }

    unsigned int idU = this->getVertexId(e.u);
    unsigned int idV = this->getVertexId(e.v);

    this->id2edge[this->getEdgeId(e)] = Edge();
    this->edge2id.erase(Edge(e));
    this->edges.erase(Edge(e));
    this->adjacencyLists[idU - 1].remove(std::make_pair(e.v, e.w));
    this->adjacencyLists[idV - 1].remove(std::make_pair(e.u, e.w));
    this->adjacencyMatrix[idU - 1][idV - 1] = DBL_MAX;
    this->adjacencyMatrix[idV - 1][idU - 1] = DBL_MAX;
    this->edgesWeight -= e.w;

    while (!this->hasEdgeId(this->maxEid)) {
        this->maxEid--;
    }

    return true;
}

/*
 * Removes the specified edge from this graph.
 *
 * @param u the first endpoint of the edge to be removed from this graph.
 * @param v the second endpoint of the edge to be removed from this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::removeEdge(const Vertex & u, const Vertex & v) {
    return this->removeEdge(Edge(u, v));
}

/*
 * Removes the specified edge from this graph.
 *
 * @param u the first endpoint of the edge to be removed from this graph.
 * @param v the second endpoint of the edge to be removed from this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::removeEdge(unsigned int u, unsigned int v) {
    return this->removeEdge(Vertex(u), Vertex(v));
}

/*
 * Removes the edge with the specified id from this graph.
 *
 * @param id the id of the edge to be removed from this graph.
 *
 * @return true if the operation succeed; false otherwise.
 */
bool Graph::removeEdgeById(unsigned int id) {
    if (!this->hasEdgeId(id)) {
        return false;
    }

    return this->removeEdge(this->getEdgeById(id));
}

/*
 * Returns the sum of the weights of this graph's edges.
 *
 * @return the sum of the weights of this graph's edges.
 */
double Graph::getEdgesWeight() const {
    return this->edgesWeight;
}

/*
 * Write this graph into the specified output stream.
 *
 * @param os the output stream to write into.
 */
void Graph::write(std::ostream & os) const {
    os << this->n() << std::endl;
    os << this->m() << std::endl;

    for (const Vertex & v : this->vertices) {
        v.write(os);
    }

    for (const Edge & e : this->edges) {
        e.write(os);
    }
}

/*
 * Write this graph into the specified file.
 *
 * @param filename the file to write into.
 */
void Graph::write(const char * filename) const {
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
 * Write this graph into the standard output stream.
 */
void Graph::write() const {
    this->write(std::cout);
}

/*
 * Returns the set of edges incident to the specified vertex.
 *
 * @param v the vertex whose incident edges are to be returned.
 *
 * @return the set of edges incident to the specified vertex.
 */
std::set<Edge> Graph::getIncidentEdges(const Vertex & v) const {
    std::set<Edge> incidentEdges;

    if (this->hasVertex(v)) {
        unsigned int idV = this->getVertexId(v);

        for (const std::pair<Vertex, double> uw : this->adjacencyLists[idV - 1]) {
            Vertex u = uw.first;
            double w = uw.second;
            Edge e (v, u, w);

            incidentEdges.insert(e);
        }
    }

    return incidentEdges;
}

/*
 * Returns the set of edges incident to the specified vertex.
 *
 * @param v the vertex whose incident edges are to be returned.
 *
 * @return the set of edges incident to the specified vertex.
 */
std::set<Edge> Graph::getIncidentEdges(unsigned int v) const {
    std::set<Edge> incidentEdges;

    if (this->hasVertex(v)) {
        incidentEdges = this->getIncidentEdges(this->getVertex(v));
    }

    return incidentEdges;
}

/*
 * Returns the set of vertices adjacent to the specified vertex.
 *
 * @param v the vertex whose adjacent vertices are to be returned.
 *
 * @return the set of vertices adjacent to the specified vertex.
 */
std::set<Vertex> Graph::getAdjacentVertices(const Vertex & v) const {
    std::set<Vertex> adjacentVertices;

    std::set<Edge> incidentEdges = this->getIncidentEdges(v);

    for (const Edge & e : incidentEdges) {
        if (v == e.u) {
            adjacentVertices.insert(e.v);
        } else if (v == e.v) {
            adjacentVertices.insert(e.u);
        }
    }

    return adjacentVertices;
}

/*
 * Returns the set of vertices adjacent to the specified vertex.
 *
 * @param v the vertex whose adjacent vertices are to be returned.
 *
 * @return the set of vertices adjacent to the specified vertex.
 */
std::set<Vertex> Graph::getAdjacentVertices(unsigned int v) const {
    std::set<Vertex> adjacentVertices;

    if (this->hasVertex(v)) {
        adjacentVertices = this->getAdjacentVertices(this->getVertex(v));
    }
    
    return adjacentVertices;
}

/*
 * Returns the set of edges adjacent to the specified edge.
 *
 * @param e the edge whose adjacent edges are to be returned.
 *
 * @return the set of edges adjacent to the specified edge.
 */
std::set<Edge> Graph::getAdjacentEdges(const Edge & e) const {
    std::set<Edge> incidentEdges;

    std::set<Edge> incidentEdgesU = this->getIncidentEdges(e.u);
    incidentEdges.insert(incidentEdgesU.begin(), incidentEdgesU.end());

    std::set<Edge> incidentEdgesV = this->getIncidentEdges(e.v);
    incidentEdges.insert(incidentEdgesV.begin(), incidentEdgesV.end());

    incidentEdges.erase(e);

    return incidentEdges;
}

/*
 * Returns the set of edges adjacent to the specified edges.
 *
 * @param edges the edges whose adjacent edges are to be returned.
 *
 * @return the set of edges adjacent to the specified edges.
 */
std::set<Edge> Graph::getAdjacentEdges(const std::set<Edge> & edges) const {
    std::set<Edge> adjacentEdges;

    for (const Edge & e : edges) {
        std::set<Edge> adjacentEdgesE = this->getAdjacentEdges(e);
        adjacentEdges.insert(adjacentEdgesE.begin(), adjacentEdgesE.end());
    }

    for (const Edge & e : edges) {
        adjacentEdges.erase(e);
    }

    return adjacentEdges;
}

/*
 * Returns the sub-graph induced by the specified vertices.
 *
 * @param vertices the subset of vertices whose induced sub-graph is to be returned.
 *
 * @return the sub-graph induced by the specified vertices.
 */
Graph Graph::getInducedSubGraph(const std::set<Vertex> & vertices) const {
    Graph inducedSubGraph;

    for (const Vertex & v : vertices) {
        inducedSubGraph.addVertex(v, this->getVertexId(v));
    }

    for (const Edge & e : this->edges) {
        if (vertices.find(e.u) != vertices.end() && vertices.find(e.v) != vertices.end()) {
            inducedSubGraph.addEdge(e, this->getEdgeId(e));
        }
    }

    return inducedSubGraph;
}

/*
 * Returns the sub-graph induced by the specified vertices.
 *
 * @param vertices the subset of vertices whose induced sub-graph is to be returned.
 *
 * @return the sub-graph induced by the specified vertices.
 */
Graph Graph::getInducedSubGraph(const std::set<unsigned int> & vertices) const {
    std::set<Vertex> V;

    for (unsigned int v : vertices) {
        V.insert(this->getVertex(v));
    }

    return this->getInducedSubGraph(V);
}

/*
 * Returns the sub-graph induced by the specified edges.
 *
 * @param edges the subset of edges whose induced sub-graph is to be returned.
 *
 * @return the sub-graph induced by the specified edges.
 */
Graph Graph::getInducedSubGraph(const std::set<Edge> & edges) const {
    Graph inducedSubGraph;

    for (const Edge & e : edges) {
        inducedSubGraph.addVertex(e.u, this->getVertexId(e.u));
        inducedSubGraph.addVertex(e.v, this->getVertexId(e.v));
    }

    for (const Edge & e : edges) {
        inducedSubGraph.addEdge(e, this->getEdgeId(e));
    }

    return inducedSubGraph;
}

/*
 * Verifies whether this graph is connected using a Breadth-First Search.
 *
 * @return true if this graph is connected; false otherwise.
 */
bool Graph::isConnected() const {
    if (this->vertices.size() <= 1) {
        return true;
    }

    unsigned int s;

    std::vector<unsigned int> color (this->maxVid, Graph::WHITE);

    std::queue<unsigned int> Q;

    s = this->getVertexId(*(this->vertices.begin()));

    color[s - 1] = GRAY;

    Q.push(s);

    while (!Q.empty()) {
        unsigned int idU = Q.front();
        Q.pop();

        for (const std::pair<Vertex, double> & vw : this->adjacencyLists[idU - 1]) {
            unsigned int idV = this->getVertexId(vw.first);

            if (color[idV - 1] == Graph::WHITE) {
                color[idV - 1] = Graph::GRAY;
                Q.push(idV);
            }
        }

        color[idU - 1] = Graph::BLACK;
    }

    for (const Vertex & v : this->vertices) {
        if (color[this->getVertexId(v) - 1] != Graph::BLACK) {
            return false;
        }
    }

    return true;
}

/*
 * Verifies whether this graph is a tree.
 *
 * @return true if this graph is a tree; false otherwise.
 */
bool Graph::isTree() const {
    return (this->m() == this->n() - 1 && this->isConnected());
}

/*
 * Returns the connected component of the specified vertex using a Depth-First Search.
 *
 * @param v       the vertex whose connected component is to be returned.
 * @param visited a vector that indicates whether each vertex have already been visited.
 *
 * @return the connected component of the specified vertex.
 */
std::set<Vertex> Graph::getConnectedComponent(const Vertex & v, 
        std::vector<bool> & visited) const {
    std::set<Vertex> connectedComponent;

    unsigned int idV = this->getVertexId(v);

    visited[idV - 1] = true;
    connectedComponent.insert(v);

    for (const std::pair<Vertex, double> & uw : this->adjacencyLists[idV - 1]) {
        Vertex u = uw.first;
        unsigned int idU = this->getVertexId(u);

        if (!visited[idU - 1]) {
            std::set<Vertex> subConnectedComponent = this->getConnectedComponent(u, visited);

            for (const Vertex & w : subConnectedComponent) {
                connectedComponent.insert(w);
            }
        }
    }

    return connectedComponent;
}

/*
 * Returns the connected components of this graph using a Depth-First Search.
 *
 * @return the connected components of this graph.
 */
std::vector<Graph> Graph::getConnectedComponents() const {
    std::vector<Graph> connectedComponents;

    std::vector<bool> visited (this->maxVid, false);

    for (const Vertex & v : this->vertices) {
        unsigned int idV = this->getVertexId(v);

        if (!visited[idV - 1]) {
            connectedComponents.push_back(this->getInducedSubGraph(
                        this->getConnectedComponent(v, visited)));
        }
    }

    return connectedComponents;
}

/*
 * Returns this graph's line graph.
 *
 * @return this graph's line graph.
 */
Graph Graph::getLineGraph() const {
    Graph lineGraph;

    for (const Edge & e : this->edges) {
        unsigned int id = this->getEdgeId(e);

        lineGraph.addVertex(Vertex(id - 1, e.w), id);
    }

    for (const Edge & e : this->edges) {
        unsigned int idE = this->getEdgeId(e);

        for (const Edge & f : this->edges) {
            unsigned int idF = this->getEdgeId(f);

            if (!(e.u == f.u && e.v == f.v) && 
                    (e.u == f.u || e.u == f.v || e.v == f.u || e.v == f.v)) {
                lineGraph.addEdge(idE - 1, idF - 1);
            }
        }
    }

    return lineGraph;
}

/*
 * Verifies whether the specified vertex is an articulation point of this graph.
 *
 * @param v the vertex to be verified.
 *
 * @return true if the specified vertex is an articulation point of this graph; 
 * false otherwise.
 */
bool Graph::isArticulationPoint(const Vertex & v) const {
    if (!this->hasVertex(v)) {
        return false;
    }

    std::vector<Graph> oldConnectedComponents = this->getConnectedComponents();

    Graph G (*this);

    G.removeVertex(v);

    std::vector<Graph> newConnectedComponents = G.getConnectedComponents();

    return (newConnectedComponents.size() > oldConnectedComponents.size());
}

/*
 * Verifies whether the specified vertex is an articulation point of this graph.
 *
 * @param v the vertex to be verified.
 *
 * @return true if the specified vertex is an articulation point of this graph; 
 * false otherwise.
 */
bool Graph::isArticulationPoint(unsigned int v) const {
    return this->isArticulationPoint(Vertex(v));
}

/*
 * Verifies whether the specified edge is a bridge of this graph.
 *
 * @param e the edge to be verified.
 *
 * @return true if the specified edge is a bridge of this graph; false otherwise.
 */
bool Graph::isBridge(const Edge & e) const {
    if (!this->hasEdge(e)) {
        return false;
    }

    std::vector<Graph> oldConnectedComponents = this->getConnectedComponents();

    Graph G (*this);

    G.removeEdge(e);

    std::vector<Graph> newConnectedComponents = G.getConnectedComponents();

    return (newConnectedComponents.size() > oldConnectedComponents.size());
}
       
/*
 * Verifies whether the specified edge is a bridge of this graph.
 *
 * @param u the first endpoint of the edge to be verified.
 * @param v the second endpoint of the edge to be verified.
 *
 * @return true if the specified edge is a bridge of this graph; false otherwise.
 */
bool Graph::isBridge(const Vertex & u, const Vertex & v) const {
    return this->isBridge(Edge(u, v));
}

/*
 * Verifies whether the specified edge is a bridge of this graph.
 *
 * @param u the first endpoint of the edge to be verified.
 * @param v the second endpoint of the edge to be verified.
 *
 * @return true if the specified edge is a bridge of this graph; false otherwise.
 */
bool Graph::isBridge(unsigned int u, unsigned int v) const {
    return this->isBridge(Vertex(u), Vertex(v));
}

/*
 * Returns the bridges of the specified vertex's connected component using a DFS.
 *
 * @param v       the vertex.
 * @param time    the time.
 * @param visited the vector that indicates whether each vertex have already been visited.
 * @param tin     the vector that indicates the time each vertex was discovered.
 * @param low     the vector.
 * @param parent  the vector that indicated the parent of each vertex.
 *
 * @return the bridges of this graph.
 */
std::set<Edge> Graph::getBridges(const Vertex & v, unsigned int & time, 
        std::vector<bool> & visited, std::vector<unsigned int > & tin, 
        std::vector<unsigned int> & low, std::vector<unsigned int> & parent) const {
    std::set<Edge> bridges;

    unsigned int idV = this->getVertexId(v);

    visited[idV - 1] = true;
    tin[idV - 1] = low[idV - 1] = time++;

    for (const std::pair<Vertex, double> & uw : this->adjacencyLists[idV - 1]) {
        Vertex u = uw.first;
        double w = uw.second;
        unsigned int idU = this->getVertexId(u);

        if (!visited[idU - 1]) {
            parent[idU - 1] = idV - 1;
            std::set<Edge> bridgesAux = this->getBridges(u, time, visited, tin, low, parent);
            bridges.insert(bridgesAux.begin(), bridgesAux.end());

            if (low[idV - 1] > low[idU - 1]) {
                low[idV - 1] = low[idU - 1];
            }

            if (low[idU - 1] > tin[idV - 1]) {
                bridges.insert(Edge(v, u, w));
            }
        } else if (idU - 1 != parent[idV - 1]) {
            if (low[idV - 1] > tin[idU - 1]) {
                low[idV - 1] = tin[idU - 1];
            }
        }
    }

    return bridges;
}

/*
 * Returns the bridges of this graph using a DFS.
 *
 * @return the bridges of this graph.
 */
std::set<Edge> Graph::getBridges() const {
    std::set<Edge> bridges;

    unsigned int time = 0;
    std::vector<bool> visited (this->maxVid + 1, false);
    std::vector<unsigned int> tin (this->maxVid + 1);
    std::vector<unsigned int> low (this->maxVid + 1);
    std::vector<unsigned int> parent (this->maxVid + 1, this->maxVid + 1);

    for (const Vertex & v : this->vertices) {
        unsigned int idV = this->getVertexId(v);

        if (!visited[idV - 1]) {
            std::set<Edge> bridgesAux = this->getBridges(v, time, visited, tin, low, parent);
            bridges.insert(bridgesAux.begin(), bridgesAux.end());
        }
    }

    return bridges;
}

/*
 * Returns this graph's leaf edges, i.e., the edges of this graph that has 
 * one extreme with degree 1.
 *
 * @return this graph's leaf edges.
 */
std::set<Edge> Graph::getLeafEdges() const {
    std::set<Edge> leafEdges;

    for (const Vertex & v : this->vertices) {
        unsigned int idV = this->getVertexId(v);

        if (this->adjacencyLists[idV - 1].size() == 1) {
            std::pair<Vertex, double> uw = *(this->adjacencyLists[idV - 1].begin());
            Vertex u = uw.first;
            double w = uw.second;
            leafEdges.insert(Edge(v, u, w));
        }
    }

    return leafEdges;
}

/*
 * Returns the edges of a minimum spanning tree of this graph.
 *
 * @return the edges of a minimum spanning tree of this graph.
 */
std::set<Edge> Graph::getMinimumSpanningTree() {
    std::vector<Edge> edgesVector (this->edges.begin(), this->edges.end());

    std::sort(edgesVector.begin(), edgesVector.end(), Edge::weightComparator);

    return Graph::getSpanningTree(edgesVector);
}

/*
 * Generates a new random complete graph.
 *
 * @param n           the size of the vertex set.
 * @param maxDemand   the maximum demand of each edge.
 * @param isEuclidean the flag indicating whether the graph is euclidean or not.
 * @param seed        the seed for the pseudo-random numbers generator.
 *
 * @returns a new random complete graph.
 */
Graph Graph::generateRandomCompleteGraph(unsigned int n, 
        unsigned int maxDemand, bool isEuclidean, unsigned int seed) {
    std::default_random_engine generator (seed);
    std::uniform_real_distribution <double> distribution (0.0, 1.0);
    std::set<Vertex> vertices;

    for (unsigned int v = 0; v < n; v++) {
        double x = distribution(generator);
        double y = distribution(generator);

        vertices.insert(Vertex(v, x, y));
    }

    std::vector<Vertex> verticesVector (vertices.begin(), vertices.end());

    std::set<Edge> edges;

    for (unsigned int i = 0; i < n; i++) {
        Vertex u = verticesVector[i];

        for (unsigned int j = i + 1; j < n; j++) {
            Vertex v = verticesVector[j];
            double dx = u.x - v.x;
            double dy = u.y - v.y;
            double w = 0.0;

            if (isEuclidean) {
                w = round((((double) maxDemand) / sqrt(2.0)) * sqrt(dx * dx + dy - dy));
            } else {
                std::uniform_int_distribution<int> weightDistribution(0, maxDemand);
                w = weightDistribution(generator);
            }

            edges.insert(Edge(u, v, w));
        }
    }

    return Graph(vertices, edges);
}

/*
 * Generates a new random connected graph.
 *
 * @param n           the size of the vertex set.
 * @param m           the size of the edge set.
 * @param maxDemand   the maximum demand of each edge.
 * @param isEuclidean the flag indicating whether the graph is euclidean or not.
 * @param seed        the seed for the pseudo-random numbers generator.
 *
 * @returns a new random connected graph.
 */
Graph Graph::generateRandomConnectedGraph(unsigned int n, unsigned int m, 
        unsigned int maxDemand, bool isEuclidean, unsigned int seed) {
    std::default_random_engine generator (seed);

    Graph G;

    if (m >= n - 1 && n * (n - 1) >= 2 * m) {
        Graph H = Graph::generateRandomCompleteGraph(n, maxDemand, isEuclidean, seed);
        std::set<Edge> allEdges = H.getEdges();
        std::vector<Edge> allEdgesVector (allEdges.begin(), allEdges.end());

        std::sort(allEdgesVector.begin(), allEdgesVector.end(), Edge::weightComparator);

        std::vector<Edge> halfEdgesVector;

        for (unsigned int i = allEdges.size() / 4; i < 3 * allEdges.size() / 4; i++) {
            halfEdgesVector.push_back(allEdgesVector[i]);
        }

        shuffle(halfEdgesVector.begin(), halfEdgesVector.end(), generator);

        shuffle(allEdgesVector.begin(), allEdgesVector.end(), generator);

        std::set<Edge> edges = Graph::getSpanningTree(halfEdgesVector);

        Graph I (H.getVertices(), edges);

        if (!I.isConnected()) {
            edges = Graph::getSpanningTree(allEdgesVector);
        }

        for (unsigned int j = 0; j < halfEdgesVector.size() && edges.size() < m; j++) {
            Edge e = halfEdgesVector[j];

            edges.insert(e);
        }

        for (unsigned int j = 0; j < allEdgesVector.size() && edges.size() < m; j++) {
            Edge e = allEdgesVector[j];

            edges.insert(e);
        }

        G = Graph(H.getVertices(), edges);
    }

    return G;
}

/*
 * Generates a new random connected graph.
 *
 * @param n           the size of the vertex set.
 * @param d           the density of the graph.
 * @param maxDemand   the maximum demand of each edge.
 * @param isEuclidean the flag indicating whether the graph is euclidean or not.
 * @param seed        the seed for the pseudo-random numbers generator.
 *
 * @returns a new random connected graph.
 */
Graph Graph::generateRandomConnectedGraph(unsigned int n, double d, 
        unsigned int maxDemand, bool isEuclidean, unsigned int seed) {
    unsigned int m = n - 1;

    m += round(d * ((double) ((n * (n - 1)) / 2) - (n - 1)));

    return Graph::generateRandomConnectedGraph(n, m, maxDemand, isEuclidean, seed);
}

/*
 * Generates a new random complete grid graph.
 *
 * @param r           the number of rows of the grid graph.
 * @param c           the number of columns of the grid graph.
 * @param maxDemand   the maximum demand of each edge.
 * @param isEuclidean the flag indicating whether the graph is euclidean or not.
 * @param seed        the seed for the pseudo-random numbers generator.
 *
 * @returns a new random complete grid graph.
 */
Graph Graph::generateRandomCompleteGridGraph(unsigned int r, unsigned int c, 
        unsigned int maxDemand, bool isEuclidean, unsigned int seed) {
    std::default_random_engine generator (seed);
    std::uniform_real_distribution <double> distribution (0.0, 0.5);
    std::set<Vertex> vertices;
    std::set<Edge> edges;
    std::vector<std::vector<Vertex> > verticesMatrix (r, std::vector<Vertex> (c));

    for (unsigned int i = 0; i < r; i++) {
        for (unsigned int j = 0; j < c; j++) {
            Vertex v (i * c + j, i + distribution(generator), j + distribution(generator));
            vertices.insert(v);
            verticesMatrix[i][j] = v;
        }
    }

    for (unsigned int i = 0; i < r; i++) {
        for (unsigned int j = 0; j < c; j++) {
            Vertex u = verticesMatrix[i][j];

            if (j < c - 1) {
                Vertex v = verticesMatrix[i][j + 1];
                double dx = v.x - u.x;
                double dy = v.y - u.y;
                double w = 0.0;

                if (isEuclidean) {
                    w = round((((double) maxDemand) / sqrt(2.5)) * sqrt(dx * dx + dy - dy));
                } else {
                    std::uniform_int_distribution<int> weightDistribution(0, maxDemand);
                    w = weightDistribution(generator);
                }

                Edge e (u, v, w);

                edges.insert(e);
            }

            if (i < r - 1) {
                Vertex v = verticesMatrix[i + 1][j];
                double dx = v.x - u.x;
                double dy = v.y - u.y;
                double w = 0.0;

                if (isEuclidean) {
                    w = round((((double) maxDemand) / sqrt(2.5)) * sqrt(dx * dx + dy - dy));
                } else {
                    std::uniform_int_distribution<int> weightDistribution(0, maxDemand);
                    w = weightDistribution(generator);
                }

                Edge e (u, v, w);

                edges.insert(e);
            }
        }
    }

    return Graph(vertices, edges);
}

/*
 * Generates a new random connected grid graph.
 *
 * @param r           the number of rows of the grid graph.
 * @param c           the number of columns of the grid graph.
 * @param m           the size of the edge set.
 * @param maxDemand   the maximum demand of each edge.
 * @param isEuclidean the flag indicating whether the graph is euclidean or not.
 * @param seed        the seed for the pseudo-random numbers generator.
 *
 * @returns a new random connected grid graph.
 */
Graph Graph::generateRandomConnectedGridGraph(unsigned int r, unsigned int c, 
        unsigned int m, unsigned int maxDemand, bool isEuclidean, 
        unsigned int seed) {
    std::default_random_engine generator (seed);

    Graph G;

    if (m >= r * c - 1 && m <= 2 * r * c - r - c) {
        Graph H = Graph::generateRandomCompleteGridGraph(r, c, maxDemand, isEuclidean, seed);
        std::set<Edge> allEdges = H.getEdges();
        std::vector<Edge> allEdgesVector (allEdges.begin(), allEdges.end());

        shuffle(allEdgesVector.begin(), allEdgesVector.end(), generator);

        std::set<Edge> edges = Graph::getSpanningTree(allEdgesVector);

        for (unsigned int j = 0; j < allEdgesVector.size() && edges.size() < m; j++) {
            Edge e = allEdgesVector[j];

            edges.insert(e);
        }

        G = Graph(H.getVertices(), edges);
    }

    return G;
}

/*
 * Generates a new random connected grid graph.
 *
 * @param r           the number of rows of the grid graph.
 * @param c           the number of columns of the grid graph.
 * @param d           the density of the graph.
 * @param maxDemand   the maximum demand of each edge.
 * @param isEuclidean the flag indicating whether the graph is euclidean or not.
 * @param seed        the seed for the pseudo-random numbers generator.
 *
 * @returns a new random connected grid graph.
 */
Graph Graph::generateRandomConnectedGridGraph(unsigned int r, unsigned int c, 
        double d, unsigned int maxDemand, bool isEuclidean, unsigned int seed) {
    unsigned int m = r * c - 1;

    m += round(d * ((double) (2 * r * c - r - c) - (r * c - 1)));

    return Graph::generateRandomConnectedGridGraph(r, c, m, maxDemand, isEuclidean, seed);
}

