#include "Community.hpp"

Community::Community(std::set<Node*> m_)
    : members{m_}
{}

//========= GETTERS
std::set<Node*> Community::getNeighbors() {
    std::set<Node*> neighbors;
    for (auto it = members.begin(); it != members.end(); ++it) {
        Node* node = *it;
        auto adjacents = node->getAdjacents();
        for (auto adj = adjacents.begin(); adj != adjacents.end(); ++adj) {
            neighbors.insert(adj->first);
        }
    }
    for (auto it = members.begin(); it != members.end(); ++it) {
        Node* node = *it;
        auto itr = neighbors.find(node);
        if (itr != neighbors.end()) {
            neighbors.erase(itr);
        }
    }
    return neighbors;
}

bool Community::neighborsIsSubset(Node* node) {
    auto adjacents = node->getAdjacents();
    for (auto it = adjacents.begin(); it != adjacents.end(); ++it) {
        Node* adj = it->first;
        if (members.find(adj) == members.end()) {
            return false;
        }
    }
    return true;
}

double Community::sim(Node* u) {
    auto adjacents = u->getAdjacents();

    // first summation
    double first_sum = 0;
    for (auto it = adjacents.begin(); it != adjacents.end(); ++it) {
        Node* adj = it->first;
        if (members.find(adj) != members.end()) {
            first_sum += it->second;
        }
    }

    // second summation
    double second_sum = 0;
    // sum1 (N(u) intersection Community)
    for (auto itr_1 = adjacents.begin(); itr_1 != adjacents.end(); ++itr_1) {
        Node* adj_v = itr_1->first;
        if (members.find(adj_v) != members.end()) {
            // sum2 (N(u) intersection N(v))
            for (auto itr_2 = adjacents.begin(); itr_2 != adjacents.end(); ++itr_2) {
                Node* adj_v2 = itr_2->first;
                auto v_adjacents = adj_v->getAdjacents();
                if (v_adjacents.find(adj_v2) != v_adjacents.end()) {
                    // sum3
                    double fraction = 0;
                    double denominator = 0;
                    auto v2_adjacents = adj_v2->getAdjacents();
                    for (auto itr_3 = v2_adjacents.begin(); itr_3 != v2_adjacents.end(); ++itr_3) {
                        double weight_v2v3 = itr_3->second;
                        denominator += weight_v2v3;
                    }
                    fraction = 1 / denominator;
                    second_sum += fraction;
                }
            }
        }
    }

    return first_sum + second_sum;
}

//========= SETTERS
void Community::addNodes(std::set<Node*> add_nodes) {
    members.merge(add_nodes);
}

//========= OTHERS
void Community::printCommunity() {
    for (auto it = members.begin(); it != members.end(); ++it) {
        Node* node = *it;
        std::cout << " " << node->getId();
    }
}