#include "Graph.hpp"

Graph Graph::compression() {
    // 3. Initialize sets of vertices with a degree of 1 and 2
    std::set<Node*> D1, D2;
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        auto node = *it;
        if (node.getDegree() == 1) {
            D1.insert(&node);
        }
        else if (node.getDegree() == 2) {
            D2.insert(&node);
        }
    }

    // 4. Initialize the compressed graph
    Graph graph_compressed = Graph(this->nodes, this->edges, this->communities);

    // 5 - 24 (Repeat until)
    while (!D1.empty() || !D2.empty()) {
        // 6 - 11
        for (auto vi = D1.begin(); vi != D1.end(); ++vi) {
            auto node = *vi;
            auto vj = (*(node->getAdjacents().begin()))->getAdjacent(node);
            // 7 - remove edges
            graph_compressed.removeEdges(node);
            // 7 - remove nodes
            graph_compressed.removeNode(node);
            // 8 - update supernodes
            // vj->
        }
        // 12 - 23
        for (auto vi = D2.begin(); vi != D2.end(); ++vi) {
            auto node = *vi;
        }
    }

    return graph_compressed;
}