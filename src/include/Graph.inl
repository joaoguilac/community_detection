#include "Graph.hpp"

typedef std::pair<Node*, double> Edge;

Graph::Graph(std::set<Node, cmp> n_, std::set<int> c_)
    : nodes{n_}, communities{c_}
{}

//========= GETTERS
std::set<Node, cmp> Graph::getNodes() {
    return nodes;
}
std::set<int> Graph::getCommunities() {
    return communities;
}
bool Graph::edgeExists(Node* node1, Node* node2) {
    return node1->edgeExists(node2);
}

//========= SETTERS
void Graph::removeNode(Node* n_) {
    n_->removeFromAdjacents();
    auto itr = nodes.find(*n_);
    nodes.erase(itr);
}
void Graph::addEdge(Node* node1, Node* node2, double weight) {
    node1->addAdjacent({node2, weight});
    node2->addAdjacent({node1, weight});
}
void Graph::updateWeight(Node* vi, Node* vj, Node* vk) {
    double old_weight = vj->getEdge(vk).second;
    double w_edge1 = vi->getEdge(vj).second;
    double w_edge2 = vi->getEdge(vk).second;
    double new_weight = old_weight + 1/2 * w_edge1 * w_edge2;

    vj->updateWeight(vk, new_weight);
    vk->updateWeight(vj, new_weight);
}