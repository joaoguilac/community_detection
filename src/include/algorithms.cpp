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
        // 6 - 11 (for D1)
        for (auto vi = D1.begin(); vi != D1.end(); ++vi) {
            auto node = *vi;
            auto vj = (*(node->getAdjacents().begin()))->getAdjacent(node);
            // 7. remove adjacents edges of vi from compressed graph
            graph_compressed.removeEdges(node);
            // 7. remove vi from compressed graph
            graph_compressed.removeNode(node);
            // 8. update supernodes
            vj->addSuperNode(node);
            // 9. add vj to D1 or D2
            if (vj->getDegree() == 1) {
                D1.insert(vj);
            }
            else if (vj->getDegree() == 2) {
                D2.insert(vj);
            }
            // 10. update D1 (remove vi)
            D1.erase(vi);
        }
        // 12 - 23 (for D2)
        for (auto vi = D2.begin(); vi != D2.end(); ++vi) {
            auto node = *vi;
            // TODO: 13 - 21. vi is a bridge node?
            if (false) {
                auto vj = (*(node->getAdjacents().begin()))->getAdjacent(node);
                auto vk = (*(node->getAdjacents().begin()++))->getAdjacent(node);
                // 14. remove adjacents edges of vi from compressed graph
                graph_compressed.removeEdges(node);
                // 14. remove vi from compressed graph
                graph_compressed.removeNode(node);
                // 14. (vj, vk) exist in graph?
                if (!graph_compressed.edgeExists(vj, vk)) {
                    // 14. add edge (vj, vk)
                    graph_compressed.addEdge(vj, vk);
                }
                // 15 - 17. automatically done with Node::addAdjacent()
            }
            // 22. update D2 (remove vi)
            D2.erase(vi);
        }
    }
    return graph_compressed;
}