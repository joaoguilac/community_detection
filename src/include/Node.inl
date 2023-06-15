#include "Node.hpp"

Node::Node(int identifier, std::map<Node*, double> lists)
    : id{identifier}, adjacentEdges{lists},
      community{-1}, degree{(int) lists.size()},
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
std::map<Node*, double> Node::getAdjacents() {
    return adjacentEdges;
}
std::set<int> Node::getSuperNode() {
    return superNode;
}
bool Node::edgeExists(Node* adjacent) {
    return adjacentEdges.find(adjacent) != adjacentEdges.end();
}
std::pair<Node*, double> Node::getEdge(Node* adjacent) {
    if (edgeExists(adjacent)) {
        return std::pair<Node*, double>({adjacent, adjacentEdges[adjacent]});
    }
    return std::pair<Node*, double>({adjacent, -1});
}

//========= SETTERS
void Node::updateDegree() {
    degree = adjacentEdges.size();
}
void Node::addAdjacent(std::pair<Node*, double> edge) {
    adjacentEdges.insert(edge);
    updateDegree();
}
void Node::removeAdjacent(Node* adjacent) {
    adjacentEdges.erase(adjacent);
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
    adjacentEdges.erase(adjacent);
    adjacentEdges.insert({adjacent, new_weight});
}