#include "../include/Graph.hpp"

Graph Graph::compression() {
    // 4. Initialize the compressed graph
    Graph graph_compressed = Graph(this);

    // 3. Initialize sets of vertices with a degree of 1 and 2
    std::queue<Node*> D1, D2;
    auto new_nodes = graph_compressed.getNodes();
    for (auto it = new_nodes.begin(); it != new_nodes.end(); ++it) {
        Node* node = *it;
        if (node->getDegree() == 1) {
            D1.push(node);
        }
        else if (node->getDegree() == 2) {
            D2.push(node);
        }
    }

    // 5 - 24 (Repeat until)
    while (not D1.empty() || not D2.empty()) {
        // 6 - 11 (for D1)
        // auto node = D1.front();
        while (not D1.empty()) {
            Node* vi = D1.front();
            Node* vj = vi->getAdjacents().begin()->first;
            // 8. update including vertices
            vj->addIV(vi);
            // 7. remove adjacents edges of vi from compressed graph
            // 7. remove vi from compressed graph
            graph_compressed.removeNode(vi);
            // 9. add vj to D1 or D2
            if (vj->getDegree() == 1) {
                D1.push(vj);
            }
            else if (vj->getDegree() == 2) {
                D2.push(vj);
            }
            // 10. update D1 (remove vi)
            D1.pop();
            delete vi;

        }
        // 12 - 23 (for D2)
        // TODO: segmentation fault
        while (not D2.empty()) {
            Node* vi = D2.front();
            // TODO: 13 - 21. vi is a bridge node?
            if (!graph_compressed.isBridge(vi)) {
                auto adjacents = vi->getAdjacents();
                auto it = adjacents.begin();

                Node* vj = it->first;
                ++it;
                Node* vk = it->first;
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
                    D1.push(vj);
                }
                else if (vj->getDegree() == 2) {
                    D2.push(vj);
                }
                // 20. add vK to D1 or D2
                if (vk->getDegree() == 1) {
                    D1.push(vk);
                }
                else if (vk->getDegree() == 2) {
                    D2.push(vk);
                }
            }
            // 22. update D2 (remove vi)
            D2.pop();
            delete vi;
        }
    }
    graph_compressed.printGraph();
    return graph_compressed;
}