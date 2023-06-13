#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Node.hpp"

#include <set>
#include <iterator>

class Graph {
    private:
        std::set<Node> nodes;
        std::set<int> communities;
    public:
        Graph(std::set<Node> = {}, std::set<int> = {});
        ~Graph() = default;

        std::set<Node> getNodes();
        std::set<int> getCommunities();
        bool edgeExists(Node*, Node*);

        void removeNode(Node*);
        void addEdge(Node*, Node*, double);
        void updateWeight(Node*, Node*, Node*);

        Graph compression();
        Graph seed_determination();
        Graph expansion();
        Graph propagation();
};

#endif