#pragma once

#include "Edge.hpp"
#include <list>
#include <map>
#include <random>
#include <set>

/*
 * The Graph class represents an undirected weighted graph.
 */
class Graph {
    private:
        /* The greatest vertex. */
        unsigned int maxV;

        /* The greatest vertex id. */
        unsigned int maxVid;

        /* The greatest edge id. */
        unsigned int maxEid;

        /* This graph's vertex set. */
        std::set<Vertex> vertices;

        /* A vector that maps each vertex to its id. */
        std::vector<unsigned int> vertex2id;

        /* A vector that maps each id to its vertex. */
        std::vector<Vertex> id2vertex;

        /* This graph's edge set. */
        std::set<Edge> edges;

        /* A map that maps each edge to its id. */
        std::map<Edge, unsigned int> edge2id;

        /* A vector that maps each id to its edge. */
        std::vector<Edge> id2edge;

        /* This graph's adjacency lists. */
        std::vector<std::list<std::pair<Vertex, double> > > adjacencyLists;

        /* This graph's adjacency matrix. */
        std::vector<std::vector<double> > adjacencyMatrix;

        /* The sum of the weight of this graph's vertices. */
        double verticesWeight;

        /* The sum of the weight of this graph's edges. */
        double edgesWeight;

        /*
         * Initializes a new graph.
         *
         * @param vertices the new graph's weighted vertex set.
         * @param edges    the new graph's edge set.
         */
        void init(const std::set<Vertex> & vertices, const std::set<Edge> & edges);

        /*
         * Initializes a new graph.
         *
         * @param vertices the new graph's unweighted vertex set.
         * @param edges    the new graph's edge set.
         */
        void init(const std::set<unsigned int> & vertices, const std::set<Edge> & edges);

        /*
         * Initializes a new graph.
         *
         * @param is the input stream to read from.
         */
        void init(std::istream & is);

        /*
         * Returns the edges of a spanning tree of the graph defined by the specified edges.
         *
         * @param E the edges of the graph whose spanning tree is to be returned.
         *
         * @return the edges of a spanning tree of the graph defined by the specified edges.
         */
        static std::set<Edge> getSpanningTree(const std::vector<Edge> E);

    public:
        /* White color constant */
        static const unsigned int WHITE;

        /* Gray color constant */
        static const unsigned int GRAY;

        /* Black color constant */
        static const unsigned int BLACK;

        /*
         * Constructs a new graph.
         *
         * @param vertices the new graph's weighted vertex set.
         * @param edges    the new graph's edge set.
         */
        Graph(const std::set<Vertex> & vertices, const std::set<Edge> & edges);

        /*
         * Constructs a new graph.
         *
         * @param vertices the new graph's unweighted vertex set.
         * @param edges    the new graph's edge set.
         */
        Graph(const std::set<unsigned int> & vertices, const std::set<Edge> & edges);

        /*
         * Constructs a new graph.
         *
         * @param vertices the new graph's weighted vertex set.
         */
        Graph(const std::set<Vertex> & vertices);

        /*
         * Constructs a new graph.
         *
         * @param vertices the new graph's unweighted vertex set.
         */
        Graph(const std::set<unsigned int> & vertices);

        /*
         * Constructs a new graph.
         *
         * @param edges    the new graph's edge set.
         */
        Graph(const std::set<Edge> & edges);

        /*
         * Constructs a new graph.
         *
         * @param n the size of the new graph's vertex set.
         */
        Graph(unsigned int n);

        /*
         * Constructs a new graph.
         *
         * @param is the input stream to read from.
         */
        Graph(std::istream & is);

        /*
         * Constructs a new graph.
         *
         * @param filename the file to read from.
         */
        Graph(const char * filename);

        /* Constructs a new empty graph. */
        Graph();

        /*
         * Verifies whether this graph is empty.
         *
         * @return true if this graph is empty; false otherwise.
         */
        bool isEmpty() const;

        /*
         * Returns this graph's vertex set.
         *
         * @return this graph's vertex set.
         */
        std::set<Vertex> getVertices() const;

        /*
         * Returns the size of this graph's vertex set.
         *
         * @return the size of this graph's vertex set.
         */
        unsigned int n() const;

        /*
         * Returns the id of the specified vertex.
         *
         * @param v the vertex whose id is to be returned.
         *
         * @return the id of the specified vertex.
         */
        unsigned int getVertexId(const Vertex & v) const;

        /*
         * Returns the id of the specified vertex.
         *
         * @param v the vertex whose id is to be returned.
         *
         * @return the id of the specified vertex.
         */
        unsigned int getVertexId(unsigned int v) const;

        /*
         * Returns the vertex with the specified id.
         *
         * @param id the whose vertex is to be returned.
         *
         * @return the vertex with the specified id.
         */
        Vertex getVertexById(unsigned int id) const;

        /*
         * Returns the vertex with the specified identifier.
         *
         * @param v the identifier of the vertex to be returned.
         *
         * @return the vertex with the specified identifier.
         */
        Vertex getVertex(unsigned int v) const;

        /*
         * Returns the greatest vertex.
         *
         * @return the greatest vertex.
         */
        unsigned int getMaxV() const;

        /*
         * Returns the greatest vertex id.
         *
         * @return the greatest vertex id.
         */
        unsigned int getMaxVid() const;

        /*
         * Returns true if this graph has the specified vertex with the specified id.
         *
         * @param v  the vertex whose presence in this graph is to be tested.
         * @param id the id of the vertex whose presence in this graph is to be tested.
         *
         * @return true if this graph has the specified vertex with the specified id; 
         *         false otherwise.
         */
        bool hasVertex(const Vertex & v, unsigned int id) const;

        /*
         * Returns true if this graph has the specified vertex with the specified id.
         *
         * @param v  the vertex whose presence in this graph is to be tested.
         * @param id the id of the vertex whose presence in this graph is to be tested.
         *
         * @return true if this graph has the specified vertex with the specified id; 
         *         false otherwise.
         */
        bool hasVertex(unsigned int v, unsigned int id) const;

        /*
         * Returns true if this graph has the specified vertex.
         *
         * @param v the vertex whose presence in this graph is to be tested.
         *
         * @return true if this graph has the specified vertex; false otherwise.
         */
        bool hasVertex(const Vertex & v) const;

        /*
         * Returns true if this graph has the specified vertex.
         *
         * @param v the vertex whose presence in this graph is to be tested.
         *
         * @return true if this graph has the specified vertex; false otherwise.
         */
        bool hasVertex(unsigned int v) const;

        /*
         * Returns true if this graph has a vertex with the specified id.
         *
         * @param id the vertex id whose presence in this graph is to be tested.
         *
         * @return true if this graph has a vertex with the specified id; false otherwise.
         */
        bool hasVertexId(unsigned int id) const;

        /*
         * Adds the specified vertex with the specified id to this graph.
         *
         * @param v  the vertex to be added to this graph.
         * @param id the id of the vertex to be add to this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool addVertex(const Vertex & v, unsigned int id);

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
        bool addVertex(unsigned int v, double x, double y, double w, unsigned int id);

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
        bool addVertex(unsigned int v, double x, double y, unsigned int id);

        /*
         * Adds the specified vertex with the specified id to this graph.
         *
         * @param v  the vertex to be added to this graph.
         * @param w  the weight of the vertex to be added to this graph.
         * @param id the id of the vertex to be added to this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool addVertex(unsigned int v, double w, unsigned int id);

        /*
         * Adds the specified vertex with the specified id to this graph.
         *
         * @param v  the vertex to be added to this graph.
         * @param id the id of the vertex to be added to this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool addVertex(unsigned int v, unsigned int id);

        /*
         * Adds the specified vertex to this graph.
         *
         * @param v the vertex to be added to this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool addVertex(const Vertex & v);

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
        bool addVertex(unsigned int v, double x, double y, double w);

        /*
         * Adds the specified vertex to this graph.
         *
         * @param v the vertex to be added to this graph.
         * @param x the x coordinate of the vertex to be added to this graph.
         * @param y the y coordinate of the vertex to be added to this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool addVertex(unsigned int v, double x, double y);

        /*
         * Adds the specified vertex to this graph.
         *
         * @param v the vertex to be added to this graph.
         * @param w the weight of the vertex to be added to this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool addVertex(unsigned int v, double w);

        /*
         * Adds the specified vertex to this graph.
         *
         * @param v the vertex to be added to this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool addVertex(unsigned int v);

        /*
         * Removes the specified vertex from this graph.
         *
         * @param v the vertex to be removed from this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool removeVertex(const Vertex & v);

        /*
         * Removes the specified vertex from this graph.
         *
         * @param v the vertex to be removed from this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool removeVertex(unsigned int v);

        /*
         * Removes the vertex with the specified if from this graph.
         *
         * @param id the id of the vertex to be removed from this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool removeVertexById(unsigned int id);

        /*
         * Returns the sum of the weights of this graph's vertices.
         *
         * @return the sum of the weights of this graph's vertices.
         */
        double getVerticesWeight() const;

        /*
         * Returns this graph's edge set.
         *
         * @return this graph's edge set.
         */
        std::set<Edge> getEdges() const;

        /*
         * Returns this size of this graph's vertex set.
         *
         * @return this size of this graph's vertex set.
         */
        unsigned int m() const;

        /*
         * Returns the id of the specified edge.
         *
         * @param e the edge whose id is to be returned.
         *
         * @return the id of the specified edge.
         */
        unsigned int getEdgeId(const Edge & e) const;

        /*
         * Returns the id of the specified edge.
         *
         * @param u the first endpoint of the edge whose id is to be returned.
         * @param v the second endpoint of the edge whose id is to be returned.
         * @param w the weight of the edge whose id is to be returned.
         *
         * @return the id of the specified edge.
         */
        unsigned int getEdgeId(const Vertex & u, const Vertex & v, double w) const;

        /*
         * Returns the id of the specified edge.
         *
         * @param u the first endpoint of the edge whose id is to be returned.
         * @param v the second endpoint of the edge whose id is to be returned.
         * @param w the weight of the edge whose id is to be returned.
         *
         * @return the id of the specified edge.
         */
        unsigned int getEdgeId(unsigned int u, unsigned int v, double w) const;

        /*
         * Returns the id of the specified edge.
         *
         * @param u the first endpoint of the edge whose id is to be returned.
         * @param v the second endpoint of the edge whose id is to be returned.
         *
         * @return the id of the specified edge.
         */
        unsigned int getEdgeId(const Vertex & u, const Vertex & v) const;

        /*
         * Returns the id of the specified edge.
         *
         * @param u the first endpoint of the edge whose id is to be returned.
         * @param v the second endpoint of the edge whose id is to be returned.
         *
         * @return the id of the specified edge.
         */
        unsigned int getEdgeId(unsigned int u, unsigned int v) const;

        /*
         * Returns the edge with the specified id.
         *
         * @param id the whose edge is to be returned.
         *
         * @return the edge with the specified id.
         */
        Edge getEdgeById(unsigned int id) const;

        /*
         * Returns the edge with the specified endpoints.
         *
         * @param u the first endpoint of the edge to be returned.
         * @param v the second endpoint of the edge to be returned.
         *
         * @return the edge with the specified endpoints.
         */
        Edge getEdge(const Vertex & u, const Vertex & v) const;

        /*
         * Returns the edge with the specified endpoints.
         *
         * @param u the first endpoint of the edge to be returned.
         * @param v the second endpoint of the edge to be returned.
         *
         * @return the edge with the specified endpoints.
         */
        Edge getEdge(unsigned int u, unsigned int v) const;

        /*
         * Returns the greatest edge id.
         *
         * @return the greatest edge id.
         */
        unsigned int getMaxEid() const;

        /*
         * Returns true if this graph has the specified edge with the specified id.
         *
         * @param e  the edge whose presence in this graph is to be tested.
         * @param id the id of the edge whose presence in this graph is to be tested.
         *
         * @return true if this graph has the specified edge with the specified id;
         *         false otherwise.
         */
        bool hasEdge(const Edge & e, unsigned int id) const;

        /*
         * Returns true if this graph has the specified edge with the specified id.
         *
         * @param u  the first endpoint of the edge whose presence in this graph is to be tested.
         * @param v  the second endpoint of the edge whose presence in this 
         *           graph is to be tested.
         * @param w  the weight of the edge whose presence in this graph is to be tested.
         * @param id the id of the edge whose presence in this graph is to be tested.
         *
         * @return true if this graph has the specified edge with the specified id;
         *         false otherwise.
         */
        bool hasEdge(const Vertex & u, const Vertex & v, double w, unsigned int id) const;

        /*
         * Returns true if this graph has the specified edge with the specified id.
         *
         * @param u  the first endpoint of the edge whose presence in this 
         *           graph is to be tested.
         * @param v  the second endpoint of the edge whose presence in this 
         *           graph is to be tested.
         * @param w  the weight of the edge whose presence in this graph is to be tested.
         * @param id the id of the edge whose presence in this graph is to be tested.
         *
         * @return true if this graph has the specified edge with the specified id;
         *         false otherwise.
         */
        bool hasEdge(unsigned int u, unsigned int v, double w, unsigned int id) const;

        /*
         * Returns true if this graph has the specified edge.
         *
         * @param e  the edge whose presence in this graph is to be tested.
         *
         * @return true if this graph has the specified edge; false otherwise.
         */
        bool hasEdge(const Edge & e) const;

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
        bool hasEdge(const Vertex & u, const Vertex & v, double w) const;

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
        bool hasEdge(unsigned int u, unsigned int v, double w) const;

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
        bool hasEdge(const Vertex & u, const Vertex & v, unsigned int id) const;

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
        bool hasEdge(unsigned int u, unsigned int v, unsigned int id) const;

        /*
         * Returns true if this graph has the specified edge.
         *
         * @param u the first endpoint of the edge whose presence in this 
         *          graph is to be tested.
         * @param v the second endpoint of the edge whose presence in this 
         *          graph is to be tested.
         *
         * @return true if this graph has the specified edge; false otherwise.
         */
        bool hasEdge(const Vertex & u, const Vertex & v) const;

        /*
         * Returns true if this graph has the specified edge.
         *
         * @param u  the first endpoint of the edge whose presence in this 
         *           graph is to be tested.
         * @param v  the second endpoint of the edge whose presence in this 
         *           graph is to be tested.
         *
         * @return true if this graph has the specified edge; false otherwise.
         */
        bool hasEdge(unsigned int u, unsigned int v) const;

        /*
         * Returns true if this graph has an edge with the specified id.
         *
         * @param e  the edge whose presence in this graph is to be tested.
         *
         * @return true if this graph has an edge with the specified id; false otherwise.
         */
        bool hasEdgeId(unsigned int id) const;

        /*
         * Adds the specified edge with the specified id to this graph.
         *
         * @param e  the edge to be added to this graph.
         * @param id the id of the edge to be add to this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool addEdge(const Edge & e, unsigned int id);

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
        bool addEdge(const Vertex & u, const Vertex & v, double w, unsigned int id);

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
        bool addEdge(unsigned int u, unsigned int v, double w, unsigned int id);

        /*
         * Adds the specified edge to this graph.
         *
         * @param e  the edge to be added to this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool addEdge(const Edge & e);

        /*
         * Adds the specified edge to this graph.
         *
         * @param u  the first endpoint of the edge to be added to this graph.
         * @param v  the second endpoint of the edge to be added to this graph.
         * @param w  the weight of the edge to be added to this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool addEdge(const Vertex & u, const Vertex & v, double w);

        /*
         * Adds the specified edge to this graph.
         *
         * @param u  the first endpoint of the edge to be added to this graph.
         * @param v  the second endpoint of the edge to be added to this graph.
         * @param w  the weight of the edge to be added to this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool addEdge(unsigned int u, unsigned int v, double w);

        /*
         * Adds the specified edge with the specified id to this graph.
         *
         * @param u  the first endpoint of the edge to be added to this graph.
         * @param v  the second endpoint of the edge to be added to this graph.
         * @param id the id of the edge to be add to this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool addEdge(const Vertex & u, const Vertex & v, unsigned int id);

        /*
         * Adds the specified edge with the specified id to this graph.
         *
         * @param u  the first endpoint of the edge to be added to this graph.
         * @param v  the second endpoint of the edge to be added to this graph.
         * @param id the id of the edge to be add to this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool addEdge(unsigned int u, unsigned int v, unsigned int id);

        /*
         * Adds the specified edge to this graph.
         *
         * @param u the first endpoint of the edge to be added to this graph.
         * @param v the second endpoint of the edge to be added to this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool addEdge(const Vertex & u, const Vertex & v);

        /*
         * Adds the specified edge to this graph.
         *
         * @param u the first endpoint of the edge to be added to this graph.
         * @param v the second endpoint of the edge to be added to this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool addEdge(unsigned int u, unsigned int v);

        /*
         * Removes the specified edge from this graph.
         *
         * @param e the edge to be removed from this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool removeEdge(const Edge & e);

        /*
         * Removes the specified edge from this graph.
         *
         * @param u the first endpoint of the edge to be removed from this graph.
         * @param v the second endpoint of the edge to be removed from this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool removeEdge(const Vertex & u, const Vertex & v);

        /*
         * Removes the specified edge from this graph.
         *
         * @param u the first endpoint of the edge to be removed from this graph.
         * @param v the second endpoint of the edge to be removed from this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool removeEdge(unsigned int u, unsigned int v);

        /*
         * Removes the edge with the specified id from this graph.
         *
         * @param id the id of the edge to be removed from this graph.
         *
         * @return true if the operation succeed; false otherwise.
         */
        bool removeEdgeById(unsigned int id);

        /*
         * Returns the sum of the weights of this graph's edges.
         *
         * @return the sum of the weights of this graph's edges.
         */
        double getEdgesWeight() const;

        /*
         * Write this graph into the specified output stream.
         *
         * @param os the output stream to write into.
         */
        void write(std::ostream & os) const;

        /*
         * Write this graph into the specified file.
         *
         * @param filename the file to write into.
         */
        void write(const char * filename) const;

        /*
         * Write this graph into the standard output stream.
         */
        void write() const;

        /*
         * Returns the set of edges incident to the specified vertex.
         *
         * @param v the vertex whose incident edges are to be returned.
         *
         * @return the set of edges incident to the specified vertex.
         */
        std::set<Edge> getIncidentEdges(const Vertex & v) const;

        /*
         * Returns the set of edges incident to the specified vertex.
         *
         * @param v the vertex whose incident edges are to be returned.
         *
         * @return the set of edges incident to the specified vertex.
         */
        std::set<Edge> getIncidentEdges(unsigned int v) const;

        /*
         * Returns the set of vertices adjacent to the specified vertex.
         *
         * @param v the vertex whose adjacent vertices are to be returned.
         *
         * @return the set of vertices adjacent to the specified vertex.
         */
        std::set<Vertex> getAdjacentVertices(const Vertex & v) const;

        /*
         * Returns the set of vertices adjacent to the specified vertex.
         *
         * @param v the vertex whose adjacent vertices are to be returned.
         *
         * @return the set of vertices adjacent to the specified vertex.
         */
        std::set<Vertex> getAdjacentVertices(unsigned int v) const;

        /*
         * Returns the set of edges adjacent to the specified edge.
         *
         * @param e the edge whose adjacent edges are to be returned.
         *
         * @return the set of edges adjacent to the specified edge.
         */
        std::set<Edge> getAdjacentEdges(const Edge & e) const;

        /*
         * Returns the set of edges adjacent to the specified edges.
         *
         * @param edges the edges whose adjacent edges are to be returned.
         *
         * @return the set of edges adjacent to the specified edges.
         */
        std::set<Edge> getAdjacentEdges(const std::set<Edge> & edges) const;

        /*
         * Returns the sub-graph induced by the specified vertices.
         *
         * @param vertices the subset of vertices whose induced sub-graph is to be returned.
         *
         * @return the sub-graph induced by the specified vertices.
         */
        Graph getInducedSubGraph(const std::set<Vertex> & vertices) const;

        /*
         * Returns the sub-graph induced by the specified vertices.
         *
         * @param vertices the subset of vertices whose induced sub-graph is to be returned.
         *
         * @return the sub-graph induced by the specified vertices.
         */
        Graph getInducedSubGraph(const std::set<unsigned int> & vertices) const;

        /*
         * Returns the sub-graph induced by the specified edges.
         *
         * @param edges the subset of edges whose induced sub-graph is to be returned.
         *
         * @return the sub-graph induced by the specified edges.
         */
        Graph getInducedSubGraph(const std::set<Edge> & edges) const;

        /*
         * Verifies whether this graph is connected using a Breadth-First Search.
         *
         * @return true if this graph is connected; false otherwise.
         */
        bool isConnected() const;

        /*
         * Verifies whether this graph is a tree.
         *
         * @return true if this graph is a tree; false otherwise.
         */
        bool isTree() const;

        /*
         * Returns the connected component of the specified vertex using a Depth-First Search.
         *
         * @param v       the vertex whose connected component is to be returned.
         * @param visited a vector that indicates whether each vertex have already been visited.
         *
         * @return the connected component of the specified vertex.
         */
        std::set<Vertex> getConnectedComponent(const Vertex & v, 
                std::vector<bool> & visited) const;

        /*
         * Returns the connected components of this graph using a Depth-First Search.
         *
         * @return the connected components of this graph.
         */
        std::vector<Graph> getConnectedComponents() const;

        /*
         * Returns this graph's line graph.
         *
         * @return this graph's line graph.
         */
        Graph getLineGraph() const;

        /*
         * Verifies whether the specified vertex is an articulation point of this graph.
         *
         * @param v the vertex to be verified.
         *
         * @return true if the specified vertex is an articulation point of this graph; 
         * false otherwise.
         */
        bool isArticulationPoint(const Vertex & v) const;

        /*
         * Verifies whether the specified vertex is an articulation point of this graph.
         *
         * @param v the vertex to be verified.
         *
         * @return true if the specified vertex is an articulation point of this graph; 
         * false otherwise.
         */
        bool isArticulationPoint(unsigned int v) const;

        /*
         * Verifies whether the specified edge is a bridge of this graph.
         *
         * @param e the edge to be verified.
         *
         * @return true if the specified edge is a bridge of this graph; false otherwise.
         */
        bool isBridge(const Edge & e) const;

        /*
         * Verifies whether the specified edge is a bridge of this graph.
         *
         * @param u the first endpoint of the edge to be verified.
         * @param v the second endpoint of the edge to be verified.
         *
         * @return true if the specified edge is a bridge of this graph; false otherwise.
         */
        bool isBridge(const Vertex & u, const Vertex & v) const;

        /*
         * Verifies whether the specified edge is a bridge of this graph.
         *
         * @param u the first endpoint of the edge to be verified.
         * @param v the second endpoint of the edge to be verified.
         *
         * @return true if the specified edge is a bridge of this graph; false otherwise.
         */
        bool isBridge(unsigned int u, unsigned int v) const;

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
        std::set<Edge> getBridges(const Vertex & v, unsigned int & time, 
                std::vector<bool> & visited, std::vector<unsigned int > & tin, 
                std::vector<unsigned int> & low, std::vector<unsigned int> & parent) const;

        /*
         * Returns the bridges of this graph using a DFS.
         *
         * @return the bridges of this graph.
         */
        std::set<Edge> getBridges() const;

        /*
         * Returns this graph's leaf edges, i.e., the edges of this graph 
         * that has one extreme with degree 1.
         *
         * @return this graph's leaf edges.
         */
        std::set<Edge> getLeafEdges() const;

        /*
         * Returns the edges of a minimum spanning tree of this graph.
         *
         * @return the edges of a minimum spanning tree of this graph.
         */
        std::set<Edge> getMinimumSpanningTree();

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
        static Graph generateRandomCompleteGraph(unsigned int n, 
                unsigned int maxDemand, bool isEuclidean, unsigned int seed);

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
        static Graph generateRandomConnectedGraph(unsigned int n, 
                unsigned int m, unsigned int maxDemand, bool isEuclidean, 
                unsigned int seed);

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
        static Graph generateRandomConnectedGraph(unsigned int n, double d, 
                unsigned int maxDemand, bool isEuclidean, unsigned int seed);

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
        static Graph generateRandomCompleteGridGraph(unsigned int r, 
                unsigned int c, unsigned int maxDemand, bool isEuclidean, 
                unsigned int seed);

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
        static Graph generateRandomConnectedGridGraph(unsigned int r, 
                unsigned int c, unsigned int m, unsigned int maxDemand, 
                bool isEuclidean, unsigned int seed);

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
        static Graph generateRandomConnectedGridGraph(unsigned int r, 
                unsigned int c, double d, unsigned int maxDemand, 
                bool isEuclidean, unsigned int seed);
};

