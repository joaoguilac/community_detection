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
Edge* Graph::getEdge(Node* node1, Node* node2) {
    Edge boundEdge1 = Edge(node1, node2, 0);
    auto itr = edges.lower_bound(boundEdge1);
    Edge edgeSearch1 = *itr;

    // if the edge was stored in inverse order of nodes
    Edge boundEdge2 = Edge(node2, node1, 0);
    itr = edges.lower_bound(boundEdge2);
    Edge edgeSearch2 = *itr;

    Edge edge;
    if (boundEdge1.getFirstNode() == edgeSearch1.getFirstNode()
        && boundEdge1.getSecondNode() == edgeSearch1.getSecondNode()) {
        edge = edgeSearch1;
    }
    if (boundEdge2.getFirstNode() == edgeSearch2.getFirstNode()
        && boundEdge2.getSecondNode() == edgeSearch2.getSecondNode()) {
        edge = edgeSearch2;
    }
    return &edge;
}
bool Graph::edgeExists(Node* node1, Node* node2) {
    Edge* edge = getEdge(node1, node2);
    return edge != nullptr;
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
void Graph::updateWeight(Node* vi, Node* vj, Node* vk) {
    Edge* edgeUpdate = getEdge(vj, vk);
    double w_edge1 = getEdge(vi, vj)->getWeight();
    double w_edge2 = getEdge(vi, vk)->getWeight();
    edgeUpdate->updateWeight(w_edge1, w_edge2);
}