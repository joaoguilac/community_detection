#ifndef _EDGE_H_
#define _EDGE_H_

#include "Node.hpp"

#include <exception>

class Edge {
    private:
        Node* node1;
        Node* node2;
        double weight;
    public:
        Edge(Node*, Node*, double = 1);
        ~Edge();

        Node* getFirstNode() const;
        Node* getSecondNode() const;
        double getWeight() const;
        Node* getAdjacent(Node*);
};

#endif