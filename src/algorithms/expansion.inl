#include "../include/Graph.hpp"

Graph Graph::expansion(std::vector<Node*> seeds) {

    Graph graph_seeding = Graph(this);

    // (1) initializing the comunities set

    std::set< std::set<Node*> > com_set;

    int k = seeds.size();
    for(int i{0}; i < k; ++i) {
        Node* relative = seeds[i];
        int id = relative->getId();
        Node* cur_node = graph_seeding.getNodeReference(id);
        cur_node->setComunity(i);
        std::set<Node*> new_set = {cur_node};
        com_set.emplace(new_set);
    }

    // (2) initializing the unleabeled nodes set

    std::set<Node*, cmp> UL;
    UL = graph_seeding.getNodes();

    for (int i{0}; i < k; ++i) {
        Node* relative = seeds[i];
        int id = relative->getId();
        Node* cur_node = graph_seeding.getNodeReference(id);
        auto itr = UL.find(cur_node);
        UL.erase(itr);
    }

    // (3-17) while UL isn't empty

    while (not UL.empty()) {
        // (4) initializing TC


    }
    









}