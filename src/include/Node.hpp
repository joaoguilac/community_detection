#ifndef _NODE_H_
#define _NODE_H_

#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <utility>

class Node {
    private:
        int id;
        int community;
        int degree;

        // TODO: change to std::map
        std::map<Node*, double> adjacentEdges;
        // TODO: use DSU
        std::set<int> superNode;
    public:
        Node(int, std::map<Node*, double> = {});
        ~Node() = default;

        int getId();
        int getDegree();
        int getCommunity();
        std::map<Node*, double> getAdjacents();
        std::set<int> getSuperNode();
        bool edgeExists(Node*);
        std::pair<Node*, double> getEdge(Node*);

        void updateDegree();
        void addAdjacent(std::pair<Node*, double>);
        void removeAdjacent(Node*);
        void addSuperNode(Node*);
        void removeFromAdjacents();
        void updateWeight(Node*, double);
};

#include "Node.inl"

#endif