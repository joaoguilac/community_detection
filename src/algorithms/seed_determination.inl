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
    std::sort(centralityIndexes.begin(), centralityIndexes.end());

    // (3) computing the second order diference of the centrality indexes

    std::vector<double> secondDiference;

    int nc = this->nodes.size();
    for(int i{0}; i < nc-2; ++i) {
        double cur_dif = ((centralityIndexes[i].first - centralityIndexes[i+1].first) - 
                          (centralityIndexes[i+1].first - centralityIndexes[i+2].first));
        secondDiference.push_back(cur_dif);
    }

    // (4) finding the knee point

    int kp = 0;

    for(int i{1}; i < nc; ++i){
        if(secondDiference[i] > secondDiference[kp]){
            kp = i;
        }
    }

    // (5) finding the potential comunity seeds

    std::vector<Node*> comunity_seeds;
    for(int i{0}; i < kp; ++i) {
        comunity_seeds.push_back(centralityIndexes[i].second);
    }

    // (6-8) eliminating adjacent seeds

    for(int i{0}; i < kp; ++i) {
        Node* vi = comunity_seeds[i];
        if(vi == nullptr) continue;
        for(int j{i+1}; j < kp; ++j) {
            Node* vj = comunity_seeds[j];
            if(vj == nullptr) continue;

            if(vi->edgeExists(vj)){
                comunity_seeds[j] = nullptr;
            }
        }
    }

    int slow = 0;
    for(int fast{0}; fast < kp; ++fast) {
        if(comunity_seeds[fast] != nullptr){
            comunity_seeds[slow] = comunity_seeds[fast];
            ++slow;
        }
    }
    comunity_seeds.resize(slow);

    // Graph graph_seeded = Graph(this);
    // for(int i{0}; i < kp; ++i) {
    //     Node* cur_node = comunity_seeds[i];
    //     int id = cur_node->getId();
    //     Node* relative = graph_seeded.getNodeReference(id);
    //     relative->setComunity(i);
    // }

    // graph_seeded.setComunity(kp);

    return comunity_seeds;
}