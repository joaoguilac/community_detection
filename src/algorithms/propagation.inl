#include "../include/Graph.hpp"

std::vector<Community> Graph::propagation(std::vector<Community> input_communities) {
    //(1)

    int k = input_communities.size();
    for(int i{0}; i < k; ++i) {
        std::set<Node*> community_nodes;
        std::set<Node*> relatives = input_communities[i].getMembers();
        for(auto it = relatives.begin(); it != relatives.end(); ++it) {
            Node* relative = *it;
            auto supernode = relative->getIV();
            for(auto itr = supernode.begin(); itr != supernode.end(); ++itr){
                int id = *itr;
                Node* node = this->getNodeReference(id);
                community_nodes.emplace(node);
            }
        }
        Community cur_community = Community(community_nodes);
        this->addCommunity(cur_community);
    }
    std::vector<Community> C = this->getCommunities();

    return C;
}