#include "../include/Graph.hpp"

std::vector<Community> Graph::expansion(std::vector<Node*> seeds) {

    Graph graph_seeding = Graph(this);

    // (1) initializing the communities set
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

    std::vector<Community> communities = graph_seeding.getCommunities();
    // (3-17) while UL isn't empty
    while (not UL.empty()) {
        // (4) initializing TC
        std::vector<std::set<Node*>> TC;
        for (int i{0}; i < k; i++) {
            TC.push_back({});
        }
        // (5) Compute common neighbors of the communities
        std::set<Node*> CV;
        for (int i{0}; i < k; i++) {
            Community community = communities[i];
            auto neighbors = community.getNeighbors();
            CV.merge(neighbors);
        }
        // 6 - 15 (for CV)
        while (not CV.empty()) {
            auto it = CV.begin();
            Node* u = *it;
            CV.erase(it);
            // 7 - 14 (u is unlabeled)
            if (UL.find(u) != UL.end()) {
                // 8 - 9 adjacents of u are subset of C_i
                bool is_subset = false;
                for (int i{0}; i < k; i++) {
                    if (communities[i].neighborsIsSubset(u)) {
                        TC[i].insert(u);
                        is_subset = true;
                        break;
                    }
                }
                if (not is_subset) {
                    // 11 - calculate argmaxsim
                    double argmaxsim = -1;
                    int index_maxsim = -1;
                    for (int i{0}; i < k; i++) {
                        double actual_sim = communities[i].sim(u);
                        if (actual_sim >= argmaxsim) {
                            argmaxsim = actual_sim;
                            index_maxsim = i;
                        }
                    }
                    TC[index_maxsim].insert(u);
                }
            }
            // (13) remove u from UL
            UL.erase(u);
        }
        // (16) update C_i
        for (int i{0}; i < k; i++) {
            communities[i].addNodes(TC[i]);
        }
    }

    return communities;
}