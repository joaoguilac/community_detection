#include "Edge.hpp"

Edge::Edge(Node* n1, Node* n2, double w)
    : node1{n1}, node2{n2}, weight{w}
{ /* empty */ }

Edge::~Edge()
{
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