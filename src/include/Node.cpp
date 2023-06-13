#include "Node.hpp"

Node::Node(int identifier, std::set<Edge> lists = {})
    : id{identifier}, adjacentEdges{lists},
      community{-1}, degree{lists.size()},
      superNode{{this->id}}
{}

//========= GETTERS
int Node::getId() {
    return id;
}
int Node::getDegree() {
    return degree;
}
int Node::getCommunity() {
    return community;
}
std::set<Edge> Node::getAdjacents() {
    return adjacentEdges;
}
std::set<int> Node::getSuperNode() {
    return superNode;
}
Edge Node::getEdge(Node* adjacent) {
    return *adjacentEdges.lower_bound({adjacent, 0});
}
bool Node::edgeExists(Node* adjacent) {
    Edge edge = getEdge(adjacent);
    return edge->first == adjacent;
}

//========= SETTERS
void Node::updateDegree() {
    degree = adjacentEdges.size();
}
void Node::addAdjacent(Edge edge) {
    adjacentEdges.insert(edge);
    updateDegree();
}
void Node::removeAdjacent(Node* adjacent) {
    auto itr = adjacentEdges.lower_bound({adjacent, 0});
    adjacentEdges.erase(itr);
    updateDegree();
}
void Node::addSuperNode(Node* node) {
    superNode.merge(node->getSuperNode());
    node->updateDegree();
}
void Node::removeFromAdjacents() {
    for (auto adj = adjacentEdges.begin(); adj != adjacentEdges.end(); ++adj) {
        adj->first->removeAdjacent(this);
    }
}
void Node::updateWeight(Node* adjacent, double new_weight) {
    auto itr = adjacentEdges.lower_bound({adjacent, 0});
    adjacentsEdges.erase(itr);
    adjacentsEdges.insert({adjacent, new_weight});
}