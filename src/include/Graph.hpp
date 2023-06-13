#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Node.hpp"
#include "Edge.hpp"

#include <set>
#include <iterator>

struct EdgeComparator {
    bool operator()(const Edge& a, const Edge& b) const {
        if (a.getFirstNode() < b.getFirstNode()) {
            return true;
        }
        if (a.getFirstNode() > b.getFirstNode()) {
            return false;
        }
        if (a.getSecondNode() < b.getSecondNode()) {
            return true;
        }
        if (a.getSecondNode() > b.getSecondNode()) {
            return false;
        }
        return a.getWeight() < b.getWeight();
    }
};

class Graph {
    private:
        std::set<Node> nodes;
        std::set<Edge, EdgeComparator> edges;
        std::set<int> communities;
    public:
        Graph(std::set<Node> = {}, std::set<Edge, EdgeComparator> = {}, std::set<int> = {});
        ~Graph();

        std::set<Node> getNodes();
        std::set<Edge, EdgeComparator> getEdges();
        std::set<int> getCommunities();
        Edge* getEdge(Node*, Node*);
        bool edgeExists(Node*, Node*);

        void removeNode(Node*);
        void removeEdges(Node*);
        void addEdge(Node*, Node*);
        void updateWeight(Node*, Node*, Node*);

        Graph compression();
};

#endif