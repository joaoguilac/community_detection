#include "Node.hpp"

#include <set>

class Graph {
    private:
        std::set<Node> nodes;
        std::set<int> communities;
    public:
        Graph(/* args */);
        ~Graph();
};

Graph::Graph(/* args */) {
}

Graph::~Graph() {
}
