#include "Node.hpp"

Node::Node(int identifier, std::set<Edge*> lists = {})
    : id{identifier}, adjacentEdges{lists},
      community{-1}, degree{lists.size()},
      superNode{{this->id}}
{ /* empty */ }

Node::~Node() {
}

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
std::set<Edge*> Node::getAdjacents() {
    return adjacentEdges;
}
std::set<int> Node::getSuperNode() {
    return superNode;
}

//========= SETTERS
void Node::addAdjacent(Edge* edge) {
    adjacentEdges.insert(edge);
    degree = adjacentEdges.size();
}
void Node::removeAdjacent(Edge* edge) {
    auto itr = adjacentEdges.find(edge);
    adjacentEdges.erase(itr);
    degree = adjacentEdges.size();
}
void Node::addSuperNode(Node* node) {
    // superNode.merge(node->getSuperNode());
}