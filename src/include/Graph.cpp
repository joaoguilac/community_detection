#include "Graph.hpp"

Graph::Graph(std::set<Node> n_ = {}, std::set<Edge> e_ = {}, std::set<int> c_ = {})
    : nodes{n_}, edges{e_}, communities{c_}
{}

Graph::~Graph() {
    // TODO: gerenciamento de memória
}

//========= GETTERS
std::set<Node> Graph::getNodes() {
    return nodes;
}
std::set<Edge> Graph::getEdges() {
    return edges;
}
std::set<int> Graph::getCommunities() {
    return communities;
}

//========= SETTERS
void Graph::removeNode(Node* node) {
    auto itr = nodes.find(*node);
    nodes.erase(itr);
}
void Graph::removeEdges(Node* node) {
    for (auto it = node->getAdjacents().begin(); it != node->getAdjacents().end(); ++it) {
        auto edge = *it;
        auto itr = edges.find(*edge);
        edges.erase(itr);
    }
}