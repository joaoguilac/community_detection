#include "Graph.hpp"

Graph::Graph(std::set<Node> n_, std::set<Edge, EdgeComparator> e_, std::set<int> c_)
    : nodes{n_}, edges{e_}, communities{c_}
{}

Graph::~Graph() {
    // TODO: gerenciamento de memória
}

//========= GETTERS
std::set<Node> Graph::getNodes() {
    return nodes;
}
std::set<Edge, EdgeComparator> Graph::getEdges() {
    return edges;
}
std::set<int> Graph::getCommunities() {
    return communities;
}
bool Graph::edgeExists(Node* node1, Node* node2) {
    Edge edgeTest = Edge(node1, node2, 0);
    auto itr = edges.lower_bound(edgeTest);
    Edge edgeSearch = *itr;

    if (edgeTest.getFirstNode() == edgeSearch.getFirstNode()
        && edgeTest.getSecondNode() == edgeSearch.getSecondNode()) {
        return true;
    }

    // if the edge was stored in inverse order of nodes
    edgeTest = Edge(node2, node1, 0);
    itr = edges.lower_bound(edgeTest);
    edgeSearch = *itr;

    return edgeTest.getFirstNode() == edgeSearch.getFirstNode()
        && edgeTest.getSecondNode() == edgeSearch.getSecondNode();
}

//========= SETTERS
void Graph::addEdge(Node* node1, Node* node2) {
    Edge newEdge = Edge(node1, node2, 0);
    edges.insert(newEdge);
    node1->addAdjacent(&newEdge);
    node2->addAdjacent(&newEdge);
}
void Graph::removeNode(Node* node) {
    auto itr = nodes.find(*node);
    nodes.erase(itr);
}
void Graph::removeEdges(Node* node) {
    std::set<Node*> adjacents;
    for (auto it = node->getAdjacents().begin(); it != node->getAdjacents().end(); ++it) {
        auto edge = *it;

        adjacents.insert(edge->getFirstNode());
        adjacents.insert(edge->getSecondNode());

        auto itr = edges.find(*edge);
        edges.erase(itr);
    }

    auto itr = adjacents.find(node);
    adjacents.erase(itr);
    for (auto it = adjacents.begin(); it != adjacents.end(); ++it) {
        auto cur_node = *it;
        cur_node->updateDegree();
    }
}