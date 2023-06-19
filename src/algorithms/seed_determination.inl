#include "../include/Graph.hpp"

std::vector<Node*> Graph::seed_determination() {

    // (1) Calculating max density and max quality
    // the normalization will be done whith a function call
    int maxDensity{0};
    int maxQuality{0};

    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        Node* node = *it;

        maxDensity = std::max(maxDensity, node->getDegree());
        maxQuality = std::max(maxQuality, node->getQuality());
    }

    // (2) calculating the centrality index and finding the decreassing order
    std::vector< std::pair<double, Node*> > centralityIndexes;

    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        Node* node = *it;

        centralityIndexes.push_back({node->getCentralityIndex(maxDensity, maxQuality), node});
    }
    std::sort(centralityIndexes.rbegin(), centralityIndexes.rend());

    // (3) computing the second order diference of the centrality indexes
    std::vector<double> secondDiference;

    int nc = this->nodes.size();
    for(int i{0}; i < nc-2; ++i) {
        double cur_dif = ((centralityIndexes[i].first - centralityIndexes[i+1].first) -
                          (centralityIndexes[i+1].first - centralityIndexes[i+2].first));
        secondDiference.push_back(cur_dif);
    }

    // (4) finding the knee point
    int knee_point = 0;

    for(int i{1}; i < nc; ++i){
        if(secondDiference[i] > secondDiference[knee_point]){
            knee_point = i;
        }
    }
    knee_point++;

    // (5) finding the potential comunity seeds
    std::vector<Node*> community_seeds;
    for(int i{0}; i < knee_point; ++i) {
        community_seeds.push_back(centralityIndexes[i].second);
    }

    // (6-8) eliminating adjacent seeds
    for(int i{0}; i < knee_point; ++i) {
        Node* vi = community_seeds[i];
        if(vi == nullptr) continue;
        for(int j{i+1}; j < knee_point; ++j) {
            Node* vj = community_seeds[j];
            if(vj == nullptr) continue;

            if(vi->edgeExists(vj)){
                community_seeds[j] = nullptr;
            }
        }
    }

    int slow = 0;
    for(int fast{0}; fast < knee_point; ++fast) {
        if(community_seeds[fast] != nullptr){
            community_seeds[slow] = community_seeds[fast];
            ++slow;
        }
    }
    community_seeds.resize(slow);
    for (size_t i{0}; i < community_seeds.size(); i++) {
        community_seeds[i]->setCommunity(i);
    }

    // Graph graph_seeded = Graph(this);
    // for(int i{0}; i < knee_point; ++i) {
    //     Node* cur_node = community_seeds[i];
    //     int id = cur_node->getId();
    //     Node* relative = graph_seeded.getNodeReference(id);
    //     relative->setCommunity(i);
    // }

    // graph_seeded.setCommunity(knee_point);

    return community_seeds;
}