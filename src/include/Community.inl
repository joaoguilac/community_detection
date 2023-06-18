#include "Community.hpp"

Community::Community(std::set<Node*> m_)
    : members{m_}
{}

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