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
bool Graph::isBridge(Node* vi) {
    // assumes that vi's degree is 2

    // adjacent nodes to vi
    auto adjacents = vi->getAdjacents();
    auto it = adjacents.begin();
    Node* vj = it->first;
    it++;
    Node* vk = it->first;

    bool value = !vk->edgeExists(vj);

    return value;

    // /*
    //     Does a bfs to find vj begining from vk without passing trough vi.
    //     If vk is found means that taking vi from the graph doesn't disconet it,
    //     in other words, vi is not a bridge.
    // */

    // std::queue<Node*> my_queue;
    // std::set<Node*> visited_nodes;
    // my_queue.push(vj);
    // visited_nodes.emplace(vi);
    // visited_nodes.emplace(vj);

    // // bfs
    // while (!my_queue.empty() && visited_nodes.find(vk) == visited_nodes.end()) {
    //     Node* cur_node = my_queue.front();
    //     my_queue.pop();
    //     std::map<Node*, double> adjacent_nodes = cur_node->getAdjacents();
    //     for(auto it = adjacent_nodes.begin(); it != adjacent_nodes.end(); ++it) {
    //         Node* cur_adjacent = it->first;
    //         if(visited_nodes.find(cur_adjacent) != visited_nodes.end()){
    //             my_queue.emplace(cur_adjacent);
    //             visited_nodes.emplace(cur_adjacent);
    //         }
    //     }
    // }

    // // check if vk is visited
    // return visited_nodes.find(vk) == visited_nodes.end();
}

//========= SETTERS
void Graph::addNode(Node* n_) {
    nodes.insert(n_);
}
void Graph::removeNode(Node* n_) {
    n_->removeFromAdjacents();
    auto itr = nodes.find(n_);
    nodes.erase(itr);
    // delete *itr;
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
void Graph::setComunity(int comunityNumber){
    communities = comunityNumber;
}

//========= OTHERS
void Graph::printGraph() {
    std::cout << "====================================\n";
    std::cout << ">> Número de vértices: " << nodes.size() << std::endl;
    std::cout << ">> Número de arestas: " << numberOfEdges << std::endl;
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        Node* node = *it;
        node->printNode();
    }
    std::cout << std::endl;
}
void Graph::zhao() {
    Graph graph_compressed = compression();
    std::vector<Node*> seeds = graph_compressed.seed_determination();
}