#ifndef _NODE_H_
#define _NODE_H_

#include <map>
#include <set>
#include <iostream>
#include <utility>
#include <queue>
#include <algorithm>

class Node {
    private:
        int id;
        int community;
        int degree;

        std::map<Node*, double> adjacentNodes;
        std::set<int> IV; //? use DSU
    public:
        Node(int, std::set<int> = {}, std::map<Node*, double> = {});
        ~Node() = default;

        // getters
        int getId();
        int getDegree();
        int getQuality();
        int getCommunity();
        std::map<Node*, double> getAdjacents();
        std::set<int> getIV();
        bool edgeExists(Node*);
        std::pair<Node*, double> getEdge(Node*);
        double getNormalizedDensity(int);
        double getNormalizedQuality(int);
        double getCentralityIndex(int, int);

        // setters
        void updateDegree();
        void addAdjacent(std::pair<Node*, double>);
        void removeAdjacent(Node*);
        void addIV(Node*);
        void removeFromAdjacents();
        void updateWeight(Node*, double);
        void setComunity(int);

        void printNode();
};

#include "Node.inl"

#endif