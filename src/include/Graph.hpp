#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Node.hpp"

struct cmp {
    bool operator() (Node* a, Node* b) const {
        return a->getId() < b->getId();
    }
};

class Graph {
    private:
        std::set<Node*, cmp> nodes;
        int communities; // TODO: comunidades detectadas
        int numberOfEdges;
    public:
        Graph(std::set<Node*, cmp> = {}, int = 0, int = 0);
        Graph(Graph*);
        ~Graph();

        std::set<Node*, cmp> getNodes();
        int getCommunities();
        int getNumberOfEdges();
        Node* getNodeReference(int);
        bool nodeExists(int);
        bool edgeExists(Node*, Node*);
        bool isBridge(Node*);

        void addNode(Node*);
        void removeNode(Node*);
        void addEdge(Node*, Node*, double);
        void setNumberOfEdges(int);
        void updateWeight(Node*, Node*, Node*);
        void setComunity(int);

        void printGraph();

        //? retirar de Graph e colocar na main
        void zhao();
        Graph compression();
        std::vector<Node*> seed_determination();
        Graph expansion(std::vector<Node*>);
        // Graph propagation();
};

#include "Graph.inl"
#include "../algorithms/compression.inl"
#include "../algorithms/expansion.inl"
#include "../algorithms/propagation.inl"
#include "../algorithms/seed_determination.inl"

#endif