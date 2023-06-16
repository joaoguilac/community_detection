#include "Graph.hpp"

typedef std::pair<Node*, double> Edge;

Graph::Graph(std::set<Node*, cmp> n_, int c_, int e_)
    : nodes{n_}, communities{c_}, numberOfEdges{e_}
{}

Graph::Graph(Graph* g_)
    : communities{g_->getCommunities()}, numberOfEdges{g_->getNumberOfEdges()}
{
    auto nodesOldGraph = g_->getNodes();
    // Create nodes
    for (auto itr = nodesOldGraph.begin(); itr != nodesOldGraph.end(); ++itr) {
        Node* node = *itr;
        nodes.insert(new Node(node->getId(), node->getIV()));
    }
    // Set adjacent nodes
    for (auto itr = nodesOldGraph.begin(); itr != nodesOldGraph.end(); ++itr) {
        Node* relative_node = *itr;
        Node* node = getNodeReference(relative_node->getId());
        auto relative_adjacents = relative_node->getAdjacents();
        for (auto it = relative_adjacents.begin(); it != relative_adjacents.end(); ++it) {
            Node* relative_adj = (*it).first;
            int id = relative_adj->getId();
            double weight = (*it).second;
            Node* adj = getNodeReference(id);
            node->addAdjacent({adj, weight});
        }
    }
}

Graph::~Graph() {
    // for (auto it = nodes.begin(); it != nodes.end(); ++it) {
    //     delete *it;
    // }
}

//========= GETTERS
std::set<Node*, cmp> Graph::getNodes() {
    return nodes;
}
int Graph::getCommunities() {
    return communities;
}
int Graph::getNumberOfEdges() {
    return numberOfEdges;
}
Node* Graph::getNodeReference(int id) {
    // auto itr_node = std::find_if(nodes.begin(),
    //                              nodes.end(),
    //                              find_by_id(id));
    Node* node_test = new Node(id);
    auto itr_node = nodes.lower_bound(node_test);
    delete node_test;
    Node* node = *itr_node;
    if (itr_node != nodes.end() && (*itr_node)->getId() == id) {
        return node;
    }
    return nullptr;
}
bool Graph::nodeExists(int id) {
    return getNodeReference(id) != nullptr;
}
bool Graph::edgeExists(Node* node1, Node* node2) {
    return node1->edgeExists(node2);
}

//========= SETTERS
void Graph::addNode(Node* n_) {
    nodes.insert(n_);
}
void Graph::removeNode(Node* n_) {
    n_->removeFromAdjacents();
    auto itr = nodes.find(n_);
    nodes.erase(itr);
    delete *itr;
}
void Graph::addEdge(Node* node1, Node* node2, double weight) {
    node1->addAdjacent({node2, weight});
    node2->addAdjacent({node1, weight});
}
void Graph::setNumberOfEdges(int nb_) {
    numberOfEdges = nb_;
}
void Graph::updateWeight(Node* vi, Node* vj, Node* vk) {
    double old_weight = vj->getEdge(vk).second;
    double w_edge1 = vi->getEdge(vj).second;
    double w_edge2 = vi->getEdge(vk).second;
    double new_weight = old_weight + 1/2 * w_edge1 * w_edge2;

    vj->updateWeight(vk, new_weight);
    vk->updateWeight(vj, new_weight);
}

//========= OTHERS
void Graph::printGraph() {
    std::cout << ">> Número de vértices: " << nodes.size() << std::endl;
    std::cout << ">> Número de arestas: " << numberOfEdges << std::endl;
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        Node* node = *it;
        node->printNode();
    }
}
void Graph::zhao() {
    Graph graph_compressed = compression();
}