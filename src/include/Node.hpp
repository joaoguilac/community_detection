#ifndef _NODE_H_
#define _NODE_H_

#include "Edge.hpp"

#include <set>
#include <iostream>

class Node {
    private:
        int id;
        int community;
        int degree;

        std::set<Edge*> adjacentEdges;
        std::set<int> superNode;
    public:
        Node(int, std::set<Edge*> = {});
        ~Node();

        int getId();
        int getDegree();
        int getCommunity();
        std::set<Edge*> getAdjacents();
        std::set<int> getSuperNode();

        void updateDegree();
        void addAdjacent(Edge*);
        void removeAdjacent(Edge*);
        void addSuperNode(Node*);
};

#endif