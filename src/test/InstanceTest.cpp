#include "../instance/Instance.hpp"
#include <cassert>

int main () {
    Instance instance;
    std::set<Edge> incidentEdges, adjacentEdges, E, bridges, leafEdges;
    std::set<Vertex> adjacentVertices;
    std::vector<Graph> connectedComponents;
    Graph lineGraph, subGraph;

    instance = Instance("instances/exampleA.in");

    assert(instance.getM() ==   2);
    assert(instance.getD() ==   2);
    assert(instance.getB() == 0.0);
    assert(instance.getMinimumDemand() == 2.0);
    assert(instance.getMaximumDemand() == 2.0);

    assert(instance.getG().n() == 3);
    assert(instance.getG().m() == 2);

    assert(instance.getG().hasVertex(0, 1));
    assert(instance.getG().hasVertex(1, 2));
    assert(instance.getG().hasVertex(2, 3));

    assert(instance.getG().hasEdge(0, 1, 1, 1));
    assert(instance.getG().hasEdge(1, 2, 1, 2));

    incidentEdges = instance.getG().getIncidentEdges(0);
    assert(incidentEdges.size() == 1);
    assert(incidentEdges.find(Edge(0, 1, 1)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(1);
    assert(incidentEdges.size() == 2);
    assert(incidentEdges.find(Edge(0, 1, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(1, 2, 1)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(2);
    assert(incidentEdges.size() == 1);
    assert(incidentEdges.find(Edge(1, 2, 1)) != incidentEdges.end());

    adjacentVertices = instance.getG().getAdjacentVertices(0);
    assert(adjacentVertices.size() == 1);
    assert(adjacentVertices.find(Vertex(1)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(1);
    assert(adjacentVertices.size() == 2);
    assert(adjacentVertices.find(Vertex(0)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(2)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(2);
    assert(adjacentVertices.size() == 1);
    assert(adjacentVertices.find(Vertex(1)) != adjacentVertices.end());

    assert(instance.getG().isConnected());

    connectedComponents = instance.getG().getConnectedComponents();

    assert(connectedComponents.size() == 1);
    assert(connectedComponents[0].n() == instance.getG().n());
    assert(connectedComponents[0].m() == instance.getG().m());
    assert(connectedComponents[0].isConnected());

    lineGraph = instance.getG().getLineGraph();

    assert(lineGraph.n() == instance.getG().m());
    assert(lineGraph.m() == 1);
    assert(lineGraph.isConnected());

    E = std::set<Edge> ();

    E.insert(Edge(0, 1, 1));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 1);
    assert(adjacentEdges.find(Edge(1, 2, 1)) != adjacentEdges.end());

    E = std::set<Edge> ();

    E.insert(Edge(1, 2, 1));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 1);
    assert(adjacentEdges.find(Edge(0, 1, 1)) != adjacentEdges.end());

    assert(instance.getC(1, 0) == 1);
    assert(instance.getC(1, 1) == 1);
    assert(instance.getC(2, 0) == 1);
    assert(instance.getC(2, 1) == 1);

    bridges = instance.getG().getBridges();

    assert(bridges.size() == 2);
    assert(bridges.find(Edge(0, 1, 1)) != bridges.end());
    assert(bridges.find(Edge(1, 2, 1)) != bridges.end());

    for (const Edge & e : instance.getG().getEdges()) {
        if (bridges.find(e) != bridges.end()) {
            assert(instance.getG().isBridge(e));
        } else {
            assert(!instance.getG().isBridge(e));
        }
    }

    leafEdges = instance.getG().getLeafEdges();

    assert(leafEdges.size() == 2);
    assert(leafEdges.find(Edge(0, 1, 1)) != leafEdges.end());
    assert(leafEdges.find(Edge(1, 2, 1)) != leafEdges.end());

    instance = Instance("instances/exampleB.in");

    assert(instance.getM() ==   3);
    assert(instance.getD() ==   2);
    assert(instance.getB() == 0.0);
    assert(instance.getMinimumDemand() == 2.0);
    assert(instance.getMaximumDemand() == 2.0);

    assert(instance.getG().n() == 3);
    assert(instance.getG().m() == 3);

    assert(instance.getG().hasVertex(0, 1));
    assert(instance.getG().hasVertex(1, 2));
    assert(instance.getG().hasVertex(2, 3));

    assert(instance.getG().hasEdge(0, 1, 1, 1));
    assert(instance.getG().hasEdge(0, 2, 1, 2));
    assert(instance.getG().hasEdge(1, 2, 1, 3));

    incidentEdges = instance.getG().getIncidentEdges(0);
    assert(incidentEdges.size() == 2);
    assert(incidentEdges.find(Edge(0, 1, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(0, 2, 1)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(1);
    assert(incidentEdges.size() == 2);
    assert(incidentEdges.find(Edge(0, 1, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(1, 2, 1)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(2);
    assert(incidentEdges.size() == 2);
    assert(incidentEdges.find(Edge(0, 2, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(1, 2, 1)) != incidentEdges.end());

    adjacentVertices = instance.getG().getAdjacentVertices(0);
    assert(adjacentVertices.size() == 2);
    assert(adjacentVertices.find(Vertex(1)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(2)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(1);
    assert(adjacentVertices.size() == 2);
    assert(adjacentVertices.find(Vertex(0)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(2)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(2);
    assert(adjacentVertices.size() == 2);
    assert(adjacentVertices.find(Vertex(0)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(1)) != adjacentVertices.end());

    assert(instance.getG().isConnected());

    connectedComponents = instance.getG().getConnectedComponents();

    assert(connectedComponents.size() == 1);
    assert(connectedComponents[0].n() == instance.getG().n());
    assert(connectedComponents[0].m() == instance.getG().m());

    lineGraph = instance.getG().getLineGraph();

    assert(lineGraph.n() == instance.getG().m());
    assert(lineGraph.m() == 3);
    assert(lineGraph.isConnected());

    E = std::set<Edge> ();

    E.insert(Edge(0, 1, 1));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 2);
    assert(adjacentEdges.find(Edge(1, 2, 1)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(0, 2, 1)) != adjacentEdges.end());

    E = std::set<Edge> ();

    E.insert(Edge(1, 2, 1));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 2);
    assert(adjacentEdges.find(Edge(0, 1, 1)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(0, 2, 1)) != adjacentEdges.end());

    E = std::set<Edge> ();

    E.insert(Edge(0, 2, 1));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 2);
    assert(adjacentEdges.find(Edge(0, 1, 1)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(1, 2, 1)) != adjacentEdges.end());

    assert(instance.getC(1, 0) == 1);
    assert(instance.getC(1, 1) == 1);
    assert(instance.getC(1, 2) == 1);
    assert(instance.getC(2, 0) == 1);
    assert(instance.getC(2, 1) == 1);
    assert(instance.getC(2, 2) == 1);
    assert(instance.getC(3, 0) == 1);
    assert(instance.getC(3, 1) == 1);
    assert(instance.getC(3, 2) == 1);

    bridges = instance.getG().getBridges();

    assert(bridges.size() == 0);

    for (const Edge & e : instance.getG().getEdges()) {
        if (bridges.find(e) != bridges.end()) {
            assert(instance.getG().isBridge(e));
        } else {
            assert(!instance.getG().isBridge(e));
        }
    }

    leafEdges = instance.getG().getLeafEdges();

    assert(leafEdges.size() == 0);

    instance = Instance("instances/exampleC.in");

    assert(instance.getM() ==   3);
    assert(instance.getD() ==   8);
    assert(instance.getB() == 0.0);
    assert(instance.getMinimumDemand() == 8.0);
    assert(instance.getMaximumDemand() == 8.0);

    assert(instance.getG().n() ==  9);
    assert(instance.getG().m() == 12);

    assert(instance.getG().hasVertex(0, 1));
    assert(instance.getG().hasVertex(1, 2));
    assert(instance.getG().hasVertex(2, 3));
    assert(instance.getG().hasVertex(3, 4));
    assert(instance.getG().hasVertex(4, 5));
    assert(instance.getG().hasVertex(5, 6));
    assert(instance.getG().hasVertex(6, 7));
    assert(instance.getG().hasVertex(7, 8));
    assert(instance.getG().hasVertex(8, 9));

    assert(instance.getG().hasEdge(0, 1, 1,  1));
    assert(instance.getG().hasEdge(0, 3, 1,  2));
    assert(instance.getG().hasEdge(1, 2, 1,  3));
    assert(instance.getG().hasEdge(1, 4, 1,  4));
    assert(instance.getG().hasEdge(2, 5, 1,  5));
    assert(instance.getG().hasEdge(3, 4, 1,  6));
    assert(instance.getG().hasEdge(3, 6, 1,  7));
    assert(instance.getG().hasEdge(4, 5, 1,  8));
    assert(instance.getG().hasEdge(4, 7, 1,  9));
    assert(instance.getG().hasEdge(5, 8, 1, 10));
    assert(instance.getG().hasEdge(6, 7, 1, 11));
    assert(instance.getG().hasEdge(7, 8, 1, 12));

    incidentEdges = instance.getG().getIncidentEdges(0);
    assert(incidentEdges.size() == 2);
    assert(incidentEdges.find(Edge(0, 1, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(0, 3, 1)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(1);
    assert(incidentEdges.size() == 3);
    assert(incidentEdges.find(Edge(0, 1, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(1, 2, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(1, 4, 1)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(2);
    assert(incidentEdges.size() == 2);
    assert(incidentEdges.find(Edge(1, 2, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(2, 5, 1)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(3);
    assert(incidentEdges.size() == 3);
    assert(incidentEdges.find(Edge(0, 3, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(3, 4, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(3, 6, 1)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(4);
    assert(incidentEdges.size() == 4);
    assert(incidentEdges.find(Edge(1, 4, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(3, 4, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(4, 5, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(4, 7, 1)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(5);
    assert(incidentEdges.size() == 3);
    assert(incidentEdges.find(Edge(2, 5, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(4, 5, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(5, 8, 1)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(6);
    assert(incidentEdges.size() == 2);
    assert(incidentEdges.find(Edge(3, 6, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(6, 7, 1)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(7);
    assert(incidentEdges.size() == 3);
    assert(incidentEdges.find(Edge(4, 7, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(6, 7, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(7, 8, 1)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(8);
    assert(incidentEdges.size() == 2);
    assert(incidentEdges.find(Edge(5, 8, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(7, 8, 1)) != incidentEdges.end());

    adjacentVertices = instance.getG().getAdjacentVertices(0);
    assert(adjacentVertices.size() == 2);
    assert(adjacentVertices.find(Vertex(1)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(3)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(1);
    assert(adjacentVertices.size() == 3);
    assert(adjacentVertices.find(Vertex(0)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(2)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(4)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(2);
    assert(adjacentVertices.size() == 2);
    assert(adjacentVertices.find(Vertex(1)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(5)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(3);
    assert(adjacentVertices.size() == 3);
    assert(adjacentVertices.find(Vertex(0)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(4)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(6)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(4);
    assert(adjacentVertices.size() == 4);
    assert(adjacentVertices.find(Vertex(1)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(3)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(5)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(7)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(5);
    assert(adjacentVertices.size() == 3);
    assert(adjacentVertices.find(Vertex(2)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(4)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(8)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(6);
    assert(adjacentVertices.size() == 2);
    assert(adjacentVertices.find(Vertex(3)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(7)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(7);
    assert(adjacentVertices.size() == 3);
    assert(adjacentVertices.find(Vertex(4)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(6)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(8)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(8);
    assert(adjacentVertices.size() == 2);
    assert(adjacentVertices.find(Vertex(5)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(7)) != adjacentVertices.end());

    assert(instance.getG().isConnected());

    connectedComponents = instance.getG().getConnectedComponents();

    assert(connectedComponents.size() == 1);
    assert(connectedComponents[0].n() == instance.getG().n());
    assert(connectedComponents[0].m() == instance.getG().m());

    lineGraph = instance.getG().getLineGraph();

    assert(lineGraph.n() == instance.getG().m());
    assert(lineGraph.m() == 22);
    assert(lineGraph.isConnected());

    E = std::set<Edge> ();

    E.insert(Edge(0, 1, 1));
    E.insert(Edge(0, 3, 1));
    E.insert(Edge(1, 2, 1));
    E.insert(Edge(2, 5, 1));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 5);
    assert(adjacentEdges.find(Edge(1, 4, 1)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(3, 4, 1)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(3, 6, 1)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(4, 5, 1)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(5, 8, 1)) != adjacentEdges.end());

    E = std::set<Edge> ();

    E.insert(Edge(1, 4, 1));
    E.insert(Edge(3, 4, 1));
    E.insert(Edge(4, 5, 1));
    E.insert(Edge(4, 7, 1));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 8);
    assert(adjacentEdges.find(Edge(0, 1, 1)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(0, 3, 1)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(1, 2, 1)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(2, 5, 1)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(3, 6, 1)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(5, 8, 1)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(6, 7, 1)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(7, 8, 1)) != adjacentEdges.end());

    E = std::set<Edge> ();

    E.insert(Edge(3, 6, 1));
    E.insert(Edge(5, 8, 1));
    E.insert(Edge(6, 7, 1));
    E.insert(Edge(7, 8, 1));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 5);
    assert(adjacentEdges.find(Edge(0, 3, 1)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(2, 5, 1)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(3, 4, 1)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(4, 5, 1)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(4, 7, 1)) != adjacentEdges.end());

    assert(instance.getC( 1, 0) == 1);
    assert(instance.getC( 1, 1) == 0);
    assert(instance.getC( 1, 2) == 0);
    assert(instance.getC( 2, 0) == 1);
    assert(instance.getC( 2, 1) == 0);
    assert(instance.getC( 2, 2) == 0);
    assert(instance.getC( 3, 0) == 1);
    assert(instance.getC( 3, 1) == 0);
    assert(instance.getC( 3, 2) == 0);
    assert(instance.getC( 4, 0) == 0);
    assert(instance.getC( 4, 1) == 1);
    assert(instance.getC( 4, 2) == 0);
    assert(instance.getC( 5, 0) == 1);
    assert(instance.getC( 5, 1) == 0);
    assert(instance.getC( 5, 2) == 0);
    assert(instance.getC( 6, 0) == 0);
    assert(instance.getC( 6, 1) == 1);
    assert(instance.getC( 6, 2) == 0);
    assert(instance.getC( 7, 0) == 0);
    assert(instance.getC( 7, 1) == 0);
    assert(instance.getC( 7, 2) == 1);
    assert(instance.getC( 8, 0) == 0);
    assert(instance.getC( 8, 1) == 1);
    assert(instance.getC( 8, 2) == 0);
    assert(instance.getC( 9, 0) == 0);
    assert(instance.getC( 9, 1) == 1);
    assert(instance.getC( 9, 2) == 0);
    assert(instance.getC(10, 0) == 0);
    assert(instance.getC(10, 1) == 0);
    assert(instance.getC(10, 2) == 1);
    assert(instance.getC(11, 0) == 0);
    assert(instance.getC(11, 1) == 0);
    assert(instance.getC(11, 2) == 1);
    assert(instance.getC(12, 0) == 0);
    assert(instance.getC(12, 1) == 0);
    assert(instance.getC(12, 2) == 1);

    bridges = instance.getG().getBridges();

    assert(bridges.size() == 0);

    for (const Edge & e : instance.getG().getEdges()) {
        if (bridges.find(e) != bridges.end()) {
            assert(instance.getG().isBridge(e));
        } else {
            assert(!instance.getG().isBridge(e));
        }
    }

    leafEdges = instance.getG().getLeafEdges();

    assert(leafEdges.size() == 0);

    instance = Instance("instances/exampleD.in");

    assert(instance.getM() ==   2);
    assert(instance.getD() ==   8);
    assert(instance.getB() == 0.0);
    assert(instance.getMinimumDemand() == 8.0);
    assert(instance.getMaximumDemand() == 8.0);

    assert(instance.getG().n() == 7);
    assert(instance.getG().m() == 8);

    assert(instance.getG().hasVertex(0, 1));
    assert(instance.getG().hasVertex(1, 2));
    assert(instance.getG().hasVertex(2, 3));
    assert(instance.getG().hasVertex(3, 4));
    assert(instance.getG().hasVertex(4, 5));
    assert(instance.getG().hasVertex(5, 6));
    assert(instance.getG().hasVertex(6, 7));

    assert(instance.getG().hasEdge(0, 1, 1, 1));
    assert(instance.getG().hasEdge(0, 6, 1, 2));
    assert(instance.getG().hasEdge(1, 2, 1, 3));
    assert(instance.getG().hasEdge(2, 3, 1, 4));
    assert(instance.getG().hasEdge(2, 5, 1, 5));
    assert(instance.getG().hasEdge(2, 6, 1, 6));
    assert(instance.getG().hasEdge(3, 4, 1, 7));
    assert(instance.getG().hasEdge(4, 5, 1, 8));

    incidentEdges = instance.getG().getIncidentEdges(0);
    assert(incidentEdges.size() == 2);
    assert(incidentEdges.find(Edge(0, 1, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(0, 6, 1)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(1);
    assert(incidentEdges.size() == 2);
    assert(incidentEdges.find(Edge(0, 1, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(1, 2, 1)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(2);
    assert(incidentEdges.size() == 4);
    assert(incidentEdges.find(Edge(1, 2, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(2, 3, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(2, 5, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(2, 6, 1)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(3);
    assert(incidentEdges.size() == 2);
    assert(incidentEdges.find(Edge(2, 3, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(3, 4, 1)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(4);
    assert(incidentEdges.size() == 2);
    assert(incidentEdges.find(Edge(3, 4, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(4, 5, 1)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(5);
    assert(incidentEdges.size() == 2);
    assert(incidentEdges.find(Edge(2, 5, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(4, 5, 1)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(6);
    assert(incidentEdges.size() == 2);
    assert(incidentEdges.find(Edge(0, 6, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(2, 6, 1)) != incidentEdges.end());

    adjacentVertices = instance.getG().getAdjacentVertices(0);
    assert(adjacentVertices.size() == 2);
    assert(adjacentVertices.find(Vertex(1)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(6)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(1);
    assert(adjacentVertices.size() == 2);
    assert(adjacentVertices.find(Vertex(0)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(2)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(2);
    assert(adjacentVertices.size() == 4);
    assert(adjacentVertices.find(Vertex(1)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(3)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(5)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(6)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(3);
    assert(adjacentVertices.size() == 2);
    assert(adjacentVertices.find(Vertex(2)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(4)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(4);
    assert(adjacentVertices.size() == 2);
    assert(adjacentVertices.find(Vertex(3)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(5)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(5);
    assert(adjacentVertices.size() == 2);
    assert(adjacentVertices.find(Vertex(2)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(4)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(6);
    assert(adjacentVertices.size() == 2);
    assert(adjacentVertices.find(Vertex(0)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(2)) != adjacentVertices.end());

    assert(instance.getG().isConnected());

    connectedComponents = instance.getG().getConnectedComponents();

    assert(connectedComponents.size() == 1);
    assert(connectedComponents[0].n() == instance.getG().n());
    assert(connectedComponents[0].m() == instance.getG().m());

    lineGraph = instance.getG().getLineGraph();

    assert(lineGraph.n() == instance.getG().m());
    assert(lineGraph.m() == 12);
    assert(lineGraph.isConnected());

    E = std::set<Edge> ();

    E.insert(Edge(0, 1, 1));
    E.insert(Edge(0, 6, 1));
    E.insert(Edge(1, 2, 1));
    E.insert(Edge(2, 6, 1));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 2);
    assert(adjacentEdges.find(Edge(2, 3, 1)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(2, 5, 1)) != adjacentEdges.end());

    E = std::set<Edge> ();

    E.insert(Edge(2, 3, 1));
    E.insert(Edge(2, 5, 1));
    E.insert(Edge(3, 4, 1));
    E.insert(Edge(4, 5, 1));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 2);
    assert(adjacentEdges.find(Edge(1, 2, 1)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(2, 6, 1)) != adjacentEdges.end());

    assert(instance.getC(1, 0) == 1);
    assert(instance.getC(1, 1) == 2);
    assert(instance.getC(2, 0) == 1);
    assert(instance.getC(2, 1) == 2);
    assert(instance.getC(3, 0) == 2);
    assert(instance.getC(3, 1) == 1);
    assert(instance.getC(4, 0) == 2);
    assert(instance.getC(4, 1) == 1);
    assert(instance.getC(5, 0) == 2);
    assert(instance.getC(5, 1) == 1);
    assert(instance.getC(6, 0) == 2);
    assert(instance.getC(6, 1) == 1);
    assert(instance.getC(7, 0) == 1);
    assert(instance.getC(7, 1) == 2);
    assert(instance.getC(8, 0) == 1);
    assert(instance.getC(8, 1) == 2);

    bridges = instance.getG().getBridges();

    assert(bridges.size() == 0);

    for (const Edge & e : instance.getG().getEdges()) {
        if (bridges.find(e) != bridges.end()) {
            assert(instance.getG().isBridge(e));
        } else {
            assert(!instance.getG().isBridge(e));
        }
    }

    leafEdges = instance.getG().getLeafEdges();

    assert(leafEdges.size() == 0);

    instance = Instance("instances/exampleE.in");

    assert(instance.getM() ==    3);
    assert(instance.getD() ==  375);
    assert(instance.getB() == 0.25);
    assert(instance.getMinimumDemand() == 234.5);
    assert(instance.getMaximumDemand() == 375.0);

    assert(instance.getG().n() == 5);
    assert(instance.getG().m() == 10);

    assert(instance.getG().hasVertex(0, 1));
    assert(instance.getG().hasVertex(1, 2));
    assert(instance.getG().hasVertex(2, 3));
    assert(instance.getG().hasVertex(3, 4));
    assert(instance.getG().hasVertex(4, 5));

    assert(instance.getG().hasEdge(0, 1, 77,  1));
    assert(instance.getG().hasEdge(0, 2, 18,  2));
    assert(instance.getG().hasEdge(0, 3, 52,  3));
    assert(instance.getG().hasEdge(0, 4, 88,  4));
    assert(instance.getG().hasEdge(1, 2, 59,  5));
    assert(instance.getG().hasEdge(1, 3, 25,  6));
    assert(instance.getG().hasEdge(1, 4, 11,  7));
    assert(instance.getG().hasEdge(2, 3, 34,  8));
    assert(instance.getG().hasEdge(2, 4, 69,  9));
    assert(instance.getG().hasEdge(3, 4, 36, 10));

    incidentEdges = instance.getG().getIncidentEdges(0);
    assert(incidentEdges.size() == 4);
    assert(incidentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(1, 0.1640250, 0.806579), 77)) != 
            incidentEdges.end());
    assert(incidentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(2, 0.7495650, 0.106392), 18)) != 
            incidentEdges.end());
    assert(incidentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(3, 0.4125580, 0.359334), 52)) != 
            incidentEdges.end());
    assert(incidentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(4, 0.0565772, 0.314136), 88)) != 
            incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(1);
    assert(incidentEdges.size() == 4);
    assert(incidentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(1, 0.1640250, 0.806579), 77)) != 
            incidentEdges.end());
    assert(incidentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(2, 0.7495650, 0.106392), 59)) != 
            incidentEdges.end());
    assert(incidentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(3, 0.4125580, 0.359334), 25)) != 
            incidentEdges.end());
    assert(incidentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(4, 0.0565772, 0.314136), 11)) != 
            incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(2);
    assert(incidentEdges.size() == 4);
    assert(incidentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(2, 0.7495650, 0.106392), 18)) != 
            incidentEdges.end());
    assert(incidentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(2, 0.7495650, 0.106392), 59)) != 
            incidentEdges.end());
    assert(incidentEdges.find(Edge(Vertex(2, 0.749565, 0.106392), 
                    Vertex(3, 0.4125580, 0.359334), 34)) != 
            incidentEdges.end());
    assert(incidentEdges.find(Edge(Vertex(2, 0.749565, 0.106392), 
                    Vertex(4, 0.0565772, 0.314136), 69)) != 
            incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(3);
    assert(incidentEdges.size() == 4);
    assert(incidentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(3, 0.4125580, 0.359334), 52)) != 
            incidentEdges.end());
    assert(incidentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(3, 0.4125580, 0.359334), 25)) != 
            incidentEdges.end());
    assert(incidentEdges.find(Edge(Vertex(2, 0.749565, 0.106392), 
                    Vertex(3, 0.4125580, 0.359334), 34)) != 
            incidentEdges.end());
    assert(incidentEdges.find(Edge(Vertex(3, 0.412558, 0.359334), 
                    Vertex(4, 0.0565772, 0.314136), 36)) != 
            incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(4);
    assert(incidentEdges.size() == 4);
    assert(incidentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(4, 0.0565772, 0.314136), 88)) != 
            incidentEdges.end());
    assert(incidentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(4, 0.0565772, 0.314136), 11)) != 
            incidentEdges.end());
    assert(incidentEdges.find(Edge(Vertex(2, 0.749565, 0.106392), 
                    Vertex(4, 0.0565772, 0.314136), 69)) != 
            incidentEdges.end());
    assert(incidentEdges.find(Edge(Vertex(3, 0.412558, 0.359334), 
                    Vertex(4, 0.0565772, 0.314136), 36)) != 
            incidentEdges.end());

    adjacentVertices = instance.getG().getAdjacentVertices(0);
    assert(adjacentVertices.size() == 4);
    assert(adjacentVertices.find(Vertex(1, 0.1640250, 0.806579)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(2, 0.7495650, 0.106392)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(3, 0.4125580, 0.359334)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(4, 0.0565772, 0.314136)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(1);
    assert(adjacentVertices.size() == 4);
    assert(adjacentVertices.find(Vertex(0, 0.9340490, 0.799424)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(2, 0.7495650, 0.106392)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(3, 0.4125580, 0.359334)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(4, 0.0565772, 0.314136)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(2);
    assert(adjacentVertices.size() == 4);
    assert(adjacentVertices.find(Vertex(0, 0.9340490, 0.799424)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(1, 0.1640250, 0.806579)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(3, 0.4125580, 0.359334)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(4, 0.0565772, 0.314136)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(3);
    assert(adjacentVertices.size() == 4);
    assert(adjacentVertices.find(Vertex(0, 0.9340490, 0.799424)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(1, 0.1640250, 0.806579)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(2, 0.7495650, 0.106392)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(4, 0.0565772, 0.314136)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(4);
    assert(adjacentVertices.size() == 4);
    assert(adjacentVertices.find(Vertex(0, 0.9340490, 0.799424)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(1, 0.1640250, 0.806579)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(2, 0.7495650, 0.106392)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(3, 0.4125580, 0.359334)) != adjacentVertices.end());

    assert(instance.getG().isConnected());

    connectedComponents = instance.getG().getConnectedComponents();

    assert(connectedComponents.size() == 1);
    assert(connectedComponents[0].n() == instance.getG().n());
    assert(connectedComponents[0].m() == instance.getG().m());
    assert(connectedComponents[0].isConnected());

    lineGraph = instance.getG().getLineGraph();

    assert(lineGraph.n() == instance.getG().m());
    assert(lineGraph.m() == 30);
    assert(lineGraph.isConnected());

    E = std::set<Edge> ();

    E.insert(Edge(Vertex(0, 0.934049, 0.799424), Vertex(1, 0.1640250, 0.806579), 77));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 6);
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(2, 0.7495650, 0.106392), 18)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(3, 0.4125580, 0.359334), 52)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(4, 0.0565772, 0.314136), 88)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(2, 0.7495650, 0.106392), 59)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(3, 0.4125580, 0.359334), 25)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(4, 0.0565772, 0.314136), 11)) != 
            adjacentEdges.end());

    E = std::set<Edge> ();

    E.insert(Edge(Vertex(0, 0.934049, 0.799424), Vertex(2, 0.7495650, 0.106392), 18));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 6);
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(1, 0.1640250, 0.806579), 77)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(3, 0.4125580, 0.359334), 52)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(4, 0.0565772, 0.314136), 88)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(2, 0.7495650, 0.106392), 59)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(2, 0.749565, 0.106392), 
                    Vertex(3, 0.4125580, 0.359334), 34)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(2, 0.749565, 0.106392), 
                    Vertex(4, 0.0565772, 0.314136), 69)) != 
            adjacentEdges.end());

    E = std::set<Edge> ();

    E.insert(Edge(Vertex(0, 0.934049, 0.799424), Vertex(3, 0.4125580, 0.359334), 52));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 6);
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(1, 0.1640250, 0.806579), 77)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(2, 0.7495650, 0.106392), 18)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(4, 0.0565772, 0.314136), 88)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(3, 0.4125580, 0.359334), 25)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(2, 0.749565, 0.106392), 
                    Vertex(3, 0.4125580, 0.359334), 34)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(3, 0.412558, 0.359334), 
                    Vertex(4, 0.0565772, 0.314136), 36)) != 
            adjacentEdges.end());

    E = std::set<Edge> ();

    E.insert(Edge(Vertex(0, 0.934049, 0.799424), Vertex(4, 0.0565772, 0.314136), 88));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 6);
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(1, 0.1640250, 0.806579), 77)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(2, 0.7495650, 0.106392), 18)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(3, 0.4125580, 0.359334), 52)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(4, 0.0565772, 0.314136), 11)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(2, 0.749565, 0.106392), 
                    Vertex(4, 0.0565772, 0.314136), 69)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(3, 0.412558, 0.359334), 
                    Vertex(4, 0.0565772, 0.314136), 36)) != 
            adjacentEdges.end());

    E = std::set<Edge> ();

    E.insert(Edge(Vertex(1, 0.164025, 0.806579), Vertex(2, 0.7495650, 0.106392), 59));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 6);
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(1, 0.1640250, 0.806579), 77)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(3, 0.4125580, 0.359334), 25)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(4, 0.0565772, 0.314136), 11)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(2, 0.7495650, 0.106392), 18)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(2, 0.749565, 0.106392), 
                    Vertex(3, 0.4125580, 0.359334), 34)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(2, 0.749565, 0.106392), 
                    Vertex(4, 0.0565772, 0.314136), 69)) != 
            adjacentEdges.end());

    E = std::set<Edge> ();

    E.insert(Edge(Vertex(1, 0.164025, 0.806579), Vertex(3, 0.4125580, 0.359334), 25));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 6);
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(1, 0.1640250, 0.806579), 77)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(2, 0.7495650, 0.106392), 59)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(4, 0.0565772, 0.314136), 11)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(3, 0.4125580, 0.359334), 52)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(2, 0.749565, 0.106392), 
                    Vertex(3, 0.4125580, 0.359334), 34)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(3, 0.412558, 0.359334), 
                    Vertex(4, 0.0565772, 0.314136), 36)) != 
            adjacentEdges.end());

    E = std::set<Edge> ();

    E.insert(Edge(Vertex(1, 0.164025, 0.806579), Vertex(4, 0.0565772, 0.314136), 11));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 6);
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(1, 0.1640250, 0.806579), 77)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(2, 0.7495650, 0.106392), 59)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(3, 0.4125580, 0.359334), 25)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(4, 0.0565772, 0.314136), 88)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(2, 0.749565, 0.106392), 
                    Vertex(4, 0.0565772, 0.314136), 69)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(3, 0.412558, 0.359334), 
                    Vertex(4, 0.0565772, 0.314136), 36)) != 
            adjacentEdges.end());

    E = std::set<Edge> ();

    E.insert(Edge(Vertex(2, 0.749565, 0.106392), Vertex(3, 0.4125580, 0.359334), 34));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 6);
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(2, 0.7495650, 0.106392), 18)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(2, 0.7495650, 0.106392), 59)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(2, 0.749565, 0.106392), 
                    Vertex(4, 0.0565772, 0.314136), 69)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(3, 0.4125580, 0.359334), 52)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(3, 0.4125580, 0.359334), 25)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(3, 0.412558, 0.359334), 
                    Vertex(4, 0.0565772, 0.314136), 36)) != 
            adjacentEdges.end());

    E = std::set<Edge> ();

    E.insert(Edge(Vertex(2, 0.749565, 0.106392), Vertex(4, 0.0565772, 0.314136), 69));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 6);
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(2, 0.7495650, 0.106392), 18)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(2, 0.7495650, 0.106392), 59)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(2, 0.749565, 0.106392), 
                    Vertex(3, 0.4125580, 0.359334), 34)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(4, 0.0565772, 0.314136), 88)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(4, 0.0565772, 0.314136), 11)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(3, 0.412558, 0.359334), 
                    Vertex(4, 0.0565772, 0.314136), 36)) != 
            adjacentEdges.end());

    E = std::set<Edge> ();

    E.insert(Edge(Vertex(3, 0.412558, 0.359334), Vertex(4, 0.0565772, 0.314136), 36));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 6);
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(3, 0.4125580, 0.359334), 52)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(3, 0.4125580, 0.359334), 25)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(2, 0.749565, 0.106392), 
                    Vertex(3, 0.4125580, 0.359334), 34)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(0, 0.934049, 0.799424), 
                    Vertex(4, 0.0565772, 0.314136), 88)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(1, 0.164025, 0.806579), 
                    Vertex(4, 0.0565772, 0.314136), 11)) != 
            adjacentEdges.end());
    assert(adjacentEdges.find(Edge(Vertex(2, 0.749565, 0.106392), 
                    Vertex(4, 0.0565772, 0.314136), 69)) != 
            adjacentEdges.end());

    assert(instance.getC( 1, 0) == 17);
    assert(instance.getC( 1, 1) == 24);
    assert(instance.getC( 1, 2) == 2);
    assert(instance.getC( 2, 0) == 6);
    assert(instance.getC( 2, 1) == 14);
    assert(instance.getC( 2, 2) == 4);
    assert(instance.getC( 3, 0) == 5);
    assert(instance.getC( 3, 1) == 26);
    assert(instance.getC( 3, 2) == 26);
    assert(instance.getC( 4, 0) == 7);
    assert(instance.getC( 4, 1) == 11);
    assert(instance.getC( 4, 2) == 29);
    assert(instance.getC( 5, 0) == 23);
    assert(instance.getC( 5, 1) == 15);
    assert(instance.getC( 5, 2) == 8);
    assert(instance.getC( 6, 0) == 25);
    assert(instance.getC( 6, 1) == 10);
    assert(instance.getC( 6, 2) == 29);
    assert(instance.getC( 7, 0) == 3);
    assert(instance.getC( 7, 1) == 10);
    assert(instance.getC( 7, 2) == 15);
    assert(instance.getC( 8, 0) == 4);
    assert(instance.getC( 8, 1) == 24);
    assert(instance.getC( 8, 2) == 21);
    assert(instance.getC( 9, 0) == 21);
    assert(instance.getC( 9, 1) == 13);
    assert(instance.getC( 9, 2) == 12);
    assert(instance.getC(10, 0) == 14);
    assert(instance.getC(10, 1) == 6);
    assert(instance.getC(10, 2) == 26);

    bridges = instance.getG().getBridges();

    assert(bridges.size() == 0);

    for (const Edge & e : instance.getG().getEdges()) {
        assert(!instance.getG().isBridge(e));
    }

    leafEdges = instance.getG().getLeafEdges();

    assert(leafEdges.size() == 0);

    instance = Instance("instances/exampleF.in");

    assert(instance.getM() ==   3);
    assert(instance.getD() ==  56);
    assert(instance.getB() == 0.2);
    assert(instance.getMinimumDemand() - 41.067 < 0.001);
    assert(instance.getMaximumDemand() == 56.0);

    assert(instance.getG().n() == 10);
    assert(instance.getG().m() == 15);

    assert(instance.getG().hasVertex(0,  1));
    assert(instance.getG().hasVertex(1,  2));
    assert(instance.getG().hasVertex(2,  3));
    assert(instance.getG().hasVertex(3,  4));
    assert(instance.getG().hasVertex(4,  5));
    assert(instance.getG().hasVertex(5,  6));
    assert(instance.getG().hasVertex(6,  7));
    assert(instance.getG().hasVertex(7,  8));
    assert(instance.getG().hasVertex(8,  9));
    assert(instance.getG().hasVertex(9, 10));

    assert(instance.getG().hasEdge(0, 1, 1,  1));
    assert(instance.getG().hasEdge(0, 4, 3,  2));
    assert(instance.getG().hasEdge(0, 5, 3,  3));
    assert(instance.getG().hasEdge(1, 2, 2,  4));
    assert(instance.getG().hasEdge(1, 6, 4,  5));
    assert(instance.getG().hasEdge(2, 3, 3,  6));
    assert(instance.getG().hasEdge(2, 7, 5,  7));
    assert(instance.getG().hasEdge(3, 4, 4,  8));
    assert(instance.getG().hasEdge(3, 8, 6,  9));
    assert(instance.getG().hasEdge(4, 9, 7, 10));
    assert(instance.getG().hasEdge(5, 7, 7, 11));
    assert(instance.getG().hasEdge(5, 8, 7, 12));
    assert(instance.getG().hasEdge(6, 8, 8, 13));
    assert(instance.getG().hasEdge(6, 9, 8, 14));
    assert(instance.getG().hasEdge(7, 9, 9, 15));

    incidentEdges = instance.getG().getIncidentEdges(0);
    assert(incidentEdges.size() == 3);
    assert(incidentEdges.find(Edge(0, 1, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(0, 4, 3)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(0, 5, 3)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(1);
    assert(incidentEdges.size() == 3);
    assert(incidentEdges.find(Edge(0, 1, 1)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(1, 2, 2)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(1, 6, 4)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(2);
    assert(incidentEdges.size() == 3);
    assert(incidentEdges.find(Edge(1, 2, 2)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(2, 3, 3)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(2, 7, 5)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(3);
    assert(incidentEdges.size() == 3);
    assert(incidentEdges.find(Edge(2, 3, 3)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(3, 4, 4)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(3, 8, 6)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(4);
    assert(incidentEdges.size() == 3);
    assert(incidentEdges.find(Edge(0, 4, 3)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(3, 4, 4)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(4, 9, 7)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(5);
    assert(incidentEdges.size() == 3);
    assert(incidentEdges.find(Edge(0, 5, 3)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(5, 7, 7)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(5, 8, 7)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(6);
    assert(incidentEdges.size() == 3);
    assert(incidentEdges.find(Edge(1, 6, 4)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(6, 8, 8)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(6, 9, 8)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(7);
    assert(incidentEdges.size() == 3);
    assert(incidentEdges.find(Edge(2, 7, 5)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(5, 7, 7)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(7, 9, 9)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(8);
    assert(incidentEdges.size() == 3);
    assert(incidentEdges.find(Edge(3, 8, 6)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(5, 8, 7)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(6, 8, 8)) != incidentEdges.end());

    incidentEdges = instance.getG().getIncidentEdges(9);
    assert(incidentEdges.size() == 3);
    assert(incidentEdges.find(Edge(4, 9, 7)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(6, 9, 8)) != incidentEdges.end());
    assert(incidentEdges.find(Edge(7, 9, 9)) != incidentEdges.end());

    adjacentVertices = instance.getG().getAdjacentVertices(0);
    assert(adjacentVertices.size() == 3);
    assert(adjacentVertices.find(Vertex(1)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(4)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(5)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(1);
    assert(adjacentVertices.size() == 3);
    assert(adjacentVertices.find(Vertex(0)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(2)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(6)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(2);
    assert(adjacentVertices.size() == 3);
    assert(adjacentVertices.find(Vertex(1)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(3)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(7)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(3);
    assert(adjacentVertices.size() == 3);
    assert(adjacentVertices.find(Vertex(2)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(4)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(8)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(4);
    assert(adjacentVertices.size() == 3);
    assert(adjacentVertices.find(Vertex(0)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(3)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(9)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(5);
    assert(adjacentVertices.size() == 3);
    assert(adjacentVertices.find(Vertex(0)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(7)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(8)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(6);
    assert(adjacentVertices.size() == 3);
    assert(adjacentVertices.find(Vertex(1)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(8)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(9)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(7);
    assert(adjacentVertices.size() == 3);
    assert(adjacentVertices.find(Vertex(2)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(5)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(9)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(8);
    assert(adjacentVertices.size() == 3);
    assert(adjacentVertices.find(Vertex(3)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(5)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(6)) != adjacentVertices.end());

    adjacentVertices = instance.getG().getAdjacentVertices(9);
    assert(adjacentVertices.size() == 3);
    assert(adjacentVertices.find(Vertex(4)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(6)) != adjacentVertices.end());
    assert(adjacentVertices.find(Vertex(7)) != adjacentVertices.end());

    assert(instance.getG().isConnected());

    connectedComponents = instance.getG().getConnectedComponents();

    assert(connectedComponents.size() == 1);
    assert(connectedComponents[0].n() == instance.getG().n());
    assert(connectedComponents[0].m() == instance.getG().m());

    lineGraph = instance.getG().getLineGraph();

    assert(lineGraph.n() == instance.getG().m());
    assert(lineGraph.m() == 30);
    assert(lineGraph.isConnected());

    E = std::set<Edge> ();

    E.insert(Edge(0, 1, 1));
    E.insert(Edge(0, 4, 3));
    E.insert(Edge(0, 5, 3));
    E.insert(Edge(1, 2, 2));
    E.insert(Edge(1, 6, 4));
    E.insert(Edge(5, 7, 7));
    E.insert(Edge(6, 8, 8));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 8);
    assert(adjacentEdges.find(Edge(2, 3, 3)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(2, 7, 5)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(3, 4, 4)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(3, 8, 6)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(4, 9, 7)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(5, 8, 7)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(6, 9, 8)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(7, 9, 9)) != adjacentEdges.end());

    E = std::set<Edge> ();

    E.insert(Edge(2, 3, 3));
    E.insert(Edge(2, 7, 5));
    E.insert(Edge(3, 4, 4));
    E.insert(Edge(3, 8, 6));
    E.insert(Edge(5, 8, 7));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 7);
    assert(adjacentEdges.find(Edge(0, 4, 3)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(0, 5, 3)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(1, 2, 2)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(4, 9, 7)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(5, 7, 7)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(6, 8, 8)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(7, 9, 9)) != adjacentEdges.end());

    E = std::set<Edge> ();

    E.insert(Edge(4, 9, 7));
    E.insert(Edge(6, 9, 8));
    E.insert(Edge(7, 9, 9));

    adjacentEdges = instance.getG().getAdjacentEdges(E);

    assert(adjacentEdges.size() == 6);
    assert(adjacentEdges.find(Edge(0, 4, 3)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(1, 6, 4)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(2, 7, 5)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(3, 4, 4)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(5, 7, 7)) != adjacentEdges.end());
    assert(adjacentEdges.find(Edge(6, 8, 8)) != adjacentEdges.end());

    assert(instance.getC( 1, 0) ==  0);
    assert(instance.getC( 1, 1) ==  1);
    assert(instance.getC( 1, 2) ==  1);
    assert(instance.getC( 2, 0) ==  4);
    assert(instance.getC( 2, 1) ==  3);
    assert(instance.getC( 2, 2) ==  2);
    assert(instance.getC( 3, 0) ==  4);
    assert(instance.getC( 3, 1) ==  3);
    assert(instance.getC( 3, 2) ==  2);
    assert(instance.getC( 4, 0) ==  2);
    assert(instance.getC( 4, 1) ==  2);
    assert(instance.getC( 4, 2) ==  1);
    assert(instance.getC( 5, 0) ==  6);
    assert(instance.getC( 5, 1) ==  4);
    assert(instance.getC( 5, 2) ==  2);
    assert(instance.getC( 6, 0) ==  4);
    assert(instance.getC( 6, 1) ==  3);
    assert(instance.getC( 6, 2) ==  2);
    assert(instance.getC( 7, 0) ==  9);
    assert(instance.getC( 7, 1) ==  5);
    assert(instance.getC( 7, 2) ==  2);
    assert(instance.getC( 8, 0) ==  6);
    assert(instance.getC( 8, 1) ==  4);
    assert(instance.getC( 8, 2) ==  2);
    assert(instance.getC( 9, 0) == 12);
    assert(instance.getC( 9, 1) ==  6);
    assert(instance.getC( 9, 2) ==  2);
    assert(instance.getC(10, 0) == 15);
    assert(instance.getC(10, 1) ==  7);
    assert(instance.getC(10, 2) ==  3);
    assert(instance.getC(11, 0) == 15);
    assert(instance.getC(11, 1) ==  7);
    assert(instance.getC(11, 2) ==  3);
    assert(instance.getC(12, 0) == 15);
    assert(instance.getC(12, 1) ==  7);
    assert(instance.getC(12, 2) ==  3);
    assert(instance.getC(13, 0) == 19);
    assert(instance.getC(13, 1) ==  8);
    assert(instance.getC(13, 2) ==  3);
    assert(instance.getC(14, 0) == 19);
    assert(instance.getC(14, 1) ==  8);
    assert(instance.getC(14, 2) ==  3);
    assert(instance.getC(15, 0) == 22);
    assert(instance.getC(15, 1) ==  9);
    assert(instance.getC(15, 2) ==  3);

    bridges = instance.getG().getBridges();

    assert(bridges.size() == 0);

    for (const Edge & e : instance.getG().getEdges()) {
        if (bridges.find(e) != bridges.end()) {
            assert(instance.getG().isBridge(e));
        } else {
            assert(!instance.getG().isBridge(e));
        }
    }

    leafEdges = instance.getG().getLeafEdges();

    assert(leafEdges.size() == 0);

    return 0;
}

