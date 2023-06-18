#include "../include/Graph.hpp"

std::vector<Community> Graph::expansion(std::vector<Node*> seeds) {

    Graph graph_seeding = Graph(this);

    // (1) initializing the comunities set
    int k = seeds.size();
    for (int i{0}; i < k; ++i) {
        Node* relative_node = seeds[i];
        int id = relative_node->getId();
        Node* cur_node = graph_seeding.getNodeReference(id);
        cur_node->setCommunity(i);
        Community community = Community({cur_node});
        graph_seeding.addCommunity(community);
    }

    // (2) initializing the unleabeled nodes set
    std::set<Node*, cmp> UL;
    UL = graph_seeding.getNodes();

    for (int i{0}; i < k; ++i) {
        Node* relative_node = seeds[i];
        int id = relative_node->getId();
        Node* cur_node = graph_seeding.getNodeReference(id);
        auto itr = UL.find(cur_node);
        UL.erase(itr);
    }

    // (3-17) while UL isn't empty
    while (not UL.empty()) {
        // (4) initializing TC
        std::vector<std::set<Node*>> TC;
        for (size_t i{0}; i < k; i++) {
            TC.push_back({});
        }
        // (5) Compute common neighbors of the communities
        std::set<Node*> CV;
        std::vector<Community> communities = graph_seeding.getCommunities();
        for (size_t i{0}; i < k; i++) {
            Community community = communities[i];
            auto neighbors = community.getNeighbors();
            CV.merge(neighbors);
        }
        // 6 - 15 (for CV)
        for (auto it = CV.begin(); it != CV.end(); ++it) {
            Node* u = *it;
            // 7 - 14 (u is unlabeled)
            if (UL.find(u) != UL.end()) {
                for (size_t i{0}; i < k; i++) {
                    if (communities[i].neighborsIsSubset(u)) {
                        TC[i].insert(u);
                    }
                    else {

                    }
                }

            }
            // (13) remove u from UL
            UL.erase(u);
        }
    }

    return graph_seeding.getCommunities();
}