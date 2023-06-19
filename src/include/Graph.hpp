#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Node.hpp"
#include "Community.hpp"

struct cmp {
    bool operator() (Node* a, Node* b) const {
        return a->getId() < b->getId();
    }
};

class Graph {
    private:
        std::set<Node*, cmp> nodes;
        std::vector<Community> communities;
        int numberOfEdges;
    public:
        Graph(std::set<Node*, cmp> = {}, std::vector<Community> = {}, int = 0);
        Graph(Graph*);
        ~Graph() = default;

        std::set<Node*, cmp> getNodes();
        std::vector<Community> getCommunities();
        int getNumberOfEdges();
        Node* getNodeReference(int);
        bool nodeExists(int);
        bool edgeExists(Node*, Node*);
        bool isBridge(Node*);

        void addNode(Node*);
        void removeNode(Node*);
        void addCommunity(Community);
        void setCommunity(std::vector<Community>);
        void addEdge(Node*, Node*, double);
        void setNumberOfEdges(int);
        void updateWeight(Node*, Node*, Node*);

        void printGraph();
        void printCommunities();

        //? retirar de Graph e colocar na main
        void zhao();
        Graph compression();
        std::vector<Node*> seed_determination();
        std::vector<Community> expansion(std::vector<Node*>);
        std::vector<Community> propagation(std::vector<Community>);
};

#include "Graph.inl"
#include "../algorithms/compression.inl"
#include "../algorithms/seed_determination.inl"
#include "../algorithms/expansion.inl"
#include "../algorithms/propagation.inl"

#endif