#ifndef _NODE_H_
#define _NODE_H_

#include <set>
#include <iostream>

class Node {
    typedef std::pair<Node*, double> Edge;

    private:
        int id;
        int community;
        int degree;

        std::set<Edge> adjacentEdges;
        std::set<int> superNode;
    public:
        Node(int, std::set<Edge> = {});
        ~Node() = default;

        int getId();
        int getDegree();
        int getCommunity();
        std::set<Edge> getAdjacents();
        std::set<int> getSuperNode();
        Edge getEdge(Node*);
        bool edgeExists(Node*);

        void updateDegree();
        void addAdjacent(Edge);
        void removeAdjacent(Node*);
        void addSuperNode(Node*);
        void removeFromAdjacents();
        void updateWeight(Node*, double);
};

#endif