#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Node.hpp"
#include "Edge.hpp"

#include <set>
#include <iterator>

class Graph {
    private:
        std::set<Node> nodes;
        std::set<Edge> edges;
        std::set<int> communities;
    public:
        Graph(std::set<Node>, std::set<Edge>, std::set<int>);
        ~Graph();

        std::set<Node> getNodes();
        std::set<Edge> getEdges();
        std::set<int> getCommunities();

        void removeNode(Node*);
        void removeEdges(Node*);

        Graph compression();
};

#endif