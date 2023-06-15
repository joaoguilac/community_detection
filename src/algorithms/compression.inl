#include "../include/Graph.hpp"

Graph Graph::compression() {
    // 3. Initialize sets of vertices with a degree of 1 and 2
    std::set<Node*> D1, D2;
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        Node* node = *it;
        if (node->getDegree() == 1) {
            D1.insert(node);
        }
        else if (node->getDegree() == 2) {
            D2.insert(node);
        }
    }

    // 4. Initialize the compressed graph
    // TODO: verificar se é cópia profunda ou rasa
    Graph graph_compressed = Graph(this->nodes, this->communities);

    // 5 - 24 (Repeat until)
    while (not D1.empty() || not D2.empty()) {
        // 6 - 11 (for D1)
        for (auto node = D1.begin(); node != D1.end(); ++node) {
            Node* vi = *node;
            Node* vj = vi->getAdjacents().begin()->first;
            // 8. update including vertices
            vj->addIV(vi);
            // 7. remove adjacents edges of vi from compressed graph
            // 7. remove vi from compressed graph
            graph_compressed.removeNode(vi);
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
        for (auto node = D2.begin(); node != D2.end(); ++node) {
            auto vi = *node;
            // TODO: 13 - 21. vi is a bridge node?
            if (false) {
                auto vj = vi->getAdjacents().begin()->first;
                auto vk = (vi->getAdjacents().begin()++)->first;
                // 19. update including vertices
                if (vj->getDegree() >= vk->getDegree()) {
                    vj->addIV(vi);
                }
                else {
                    vk->addIV(vi);
                }
                // 14. remove adjacents edges of vi from compressed graph
                // 14. remove vi from compressed graph
                graph_compressed.removeNode(vi);
                // 14. (vj, vk) exist in graph?
                if (not graph_compressed.edgeExists(vj, vk)) {
                    // 14. add edge (vj, vk)
                    graph_compressed.addEdge(vj, vk, 0);
                }
                // 15 - 17. automatically done with Graph::addEdge() and Graph::removeEdges
                // 18. update weight (vj, vk)
                graph_compressed.updateWeight(vi, vj, vk);
                // 20. add vj to D1 or D2
                if (vj->getDegree() == 1) {
                    D1.insert(vj);
                }
                else if (vj->getDegree() == 2) {
                    D2.insert(vj);
                }
                // 20. add vK to D1 or D2
                if (vk->getDegree() == 1) {
                    D1.insert(vk);
                }
                else if (vk->getDegree() == 2) {
                    D2.insert(vk);
                }
            }
            // 22. update D2 (remove vi)
            D2.erase(vi);
        }
    }
    return graph_compressed;
}