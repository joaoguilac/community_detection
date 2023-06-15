#include "Node.hpp"

Node::Node(int identifier, std::map<Node*, double> lists)
    : id{identifier}, adjacentNodes{lists},
      community{-1}, degree{(int) lists.size()},
      IV{{this->id}}
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
std::map<Node*, double> Node::getAdjacents() {
    return adjacentNodes;
}
std::set<int> Node::getIV() {
    return IV;
}
bool Node::edgeExists(Node* adjacent) {
    return adjacentNodes.find(adjacent) != adjacentNodes.end();
}
std::pair<Node*, double> Node::getEdge(Node* adjacent) {
    if (edgeExists(adjacent)) {
        return std::pair<Node*, double>({adjacent, adjacentNodes[adjacent]});
    }
    return std::pair<Node*, double>({adjacent, -1});
}

//========= SETTERS
void Node::updateDegree() {
    degree = adjacentNodes.size();
}
void Node::addAdjacent(std::pair<Node*, double> edge) {
    adjacentNodes.insert(edge);
    updateDegree();
}
void Node::removeAdjacent(Node* adjacent) {
    adjacentNodes.erase(adjacent);
    updateDegree();
}
void Node::addIV(Node* node) {
    IV.merge(node->getIV());
    node->updateDegree();
}
void Node::removeFromAdjacents() {
    for (auto adj = adjacentNodes.begin(); adj != adjacentNodes.end(); ++adj) {
        adj->first->removeAdjacent(this);
    }
}
void Node::updateWeight(Node* adjacent, double new_weight) {
    adjacentNodes.erase(adjacent);
    adjacentNodes.insert({adjacent, new_weight});
}