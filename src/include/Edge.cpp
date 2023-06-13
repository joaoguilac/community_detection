#include "Edge.hpp"

Edge::Edge(Node* n1, Node* n2, double w)
    : node1{n1}, node2{n2}, weight{w}
{ /* empty */ }

Edge::~Edge()
{
}

//========= GETTERS
Node* Edge::getFirstNode() const {
    return node1;
}
Node* Edge::getSecondNode() const {
    return node2;
}
double Edge::getWeight() const {
    return weight;
}
Node* Edge::getAdjacent(Node* node) {
    if (node == node1) {
        return node2;
    }
    else if (node == node2) {
        return node1;
    }
    else {
        // TODO: exceção
    }
}

//========= SETTERS
void Edge::updateWeight(double w_edge1, double w_edge2) {
    weight += 1/2 * w_edge1 * w_edge2;
}