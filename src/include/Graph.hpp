#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Node.hpp"

struct cmp {
    bool operator() (Node a, Node b) const {
        return a.getId() == b.getId();
    }
};

class Graph {
    private:
        // TODO: change to vector
        std::set<Node, cmp> nodes;
        // TODO: why vector?
        std::set<int> communities;
    public:
        Graph(std::set<Node, cmp> = {}, std::set<int> = {});
        ~Graph() = default;

        std::set<Node, cmp> getNodes();
        std::set<int> getCommunities();
        bool edgeExists(Node*, Node*);

        void removeNode(Node*);
        void addEdge(Node*, Node*, double);
        void updateWeight(Node*, Node*, Node*);

        // TODO: retirar de Graph e colocar na main
        Graph compression();
        // Graph seed_determination();
        // Graph expansion();
        // Graph propagation();
};

#include "Graph.inl"
#include "../algorithms/compression.inl"
#include "../algorithms/expansion.inl"
#include "../algorithms/propagation.inl"
#include "../algorithms/seed_determination.inl"

#endif