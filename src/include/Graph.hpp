#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Node.hpp"

#include <algorithm> // std::find_if

struct find_by_id {
    private:
        int node_id;
    public:
        find_by_id(int id) : node_id{id} {}
        bool operator() (Node node) const {
            return node.getId() == node_id;
        }
};
struct cmp {
    bool operator() (Node a, Node b) const {
        return a.getId() == b.getId();
    }
};

class Graph {
    private:
        std::set<Node, cmp> nodes; // TODO: change to vector
        std::set<int> communities; // TODO: why vector?
    public:
        Graph(std::set<Node, cmp> = {}, std::set<int> = {});
        ~Graph() = default;

        std::set<Node, cmp> getNodes();
        std::set<int> getCommunities();
        Node* getNodeReference(int);
        bool nodeExists(int);
        bool edgeExists(Node*, Node*);

        void addNode(Node*); // TODO
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