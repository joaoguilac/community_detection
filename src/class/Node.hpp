#include <set>

class Node {
    private:
        int id;
        std::set<Node*> adjacents;
        int community;
    public:
        Node(int identifier, std::set<Node*> lists = {});
        ~Node();

        int getId();
        std::set<Node*> getAdjacents();
        int getCommunity();

        void addAdjacent(Node* node);
        void removeAdjacent(Node* node);
};

Node::Node(int identifier, std::set<Node*> lists = {})
    : id{identifier}, adjacents{lists}, community{-1}
{ /* empty */ }

Node::~Node() {
}

// GETTERS
int Node::getId() {
    return id;
}
std::set<Node*> Node::getAdjacents() {
    return adjacents;
}
int Node::getCommunity() {
    return community;
}

// SETTERS
void Node::addAdjacent(Node* node) {
    adjacents.insert(node);
}
void Node::removeAdjacent(Node* node) {
    auto itr = adjacents.find(node);
    adjacents.erase(itr);
}