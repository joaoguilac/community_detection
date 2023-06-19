/**
 * @file executor.cpp
 * @author your name (you@domain.com)
 * @brief Contém as funções utilizadas pra leitura e manipulação dos dados
 * @version 0.1
 * @date 2023-06-14
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "include/Graph.hpp"
#include "include/Node.hpp"

#include <fstream>   // std::ifstream std::ofstream
#include <ios>       // ios_base::in
#include <iostream>  // st::cout, std::cin, std::endl
#include <istream>   // std::istringstream
#include <sstream>   // std::stringstream
#include <string>    // std::string
#include <chrono>

void processLine(std::string line, Graph* graph) {
    std::istringstream edge(line);
    int id_node1, id_node2;
    edge >> id_node1;
    edge >> id_node2;

    // Criar nós
    Node *node1, *node2;
    if (not graph->nodeExists(id_node1)) {
        node1 = new Node(id_node1);
        graph->addNode(node1);
    }
    else {
        node1 = graph->getNodeReference(id_node1);
    }

    if (not graph->nodeExists(id_node2)) {
        node2 = new Node(id_node2);
        graph->addNode(node2);
    }
    else {
        node2 = graph->getNodeReference(id_node2);
    }

    // Adicionar na lista de adjacência de cada nó
    node1->addAdjacent({node2, 1});
    node2->addAdjacent({node1, 1});
}

void readFile(std::string file_path, Graph* graph) {
    // Validação inicial dos argumentos
    if (file_path.empty()) {
        std::cerr << "ERRO :: Argumento com o caminho para o arquivo de teste não foi especificado." << std::endl;
        exit(1);
    }

    std::ifstream file_data(file_path);

    if (not file_data.is_open()) {
        std::cerr << "ERRO :: Arquivo " << file_path << " informado é inválido." << std::endl << std::endl;
        exit(1);
    }

    std::string line;
    int numberOfEdges{0};
    while (std::getline(file_data, line)) {
        processLine(line, graph);
        numberOfEdges++;
    }
    graph->setNumberOfEdges(numberOfEdges);
}

void printResult(const std::chrono::time_point<std::chrono::steady_clock> &start,
                 const std::chrono::time_point<std::chrono::steady_clock> &end,
                 Graph graph, std::string file_path) {
    auto time = end - start;

    std::ofstream results("results/" + file_path, std::ios::app);
    results << "=================================================\n";

    // Milliseconds (10^-3)
    results << ">> Tempo para encontrar as comunidades: ";
    results << std::chrono::duration <double, std::milli> (time).count();
    results << "ms\n" << std::endl;

    results << ">> Número de vértices: " << graph.getNodes().size() << std::endl;
    results << ">> Número de arestas: " << graph.getNumberOfEdges() << std::endl;

    auto communities = graph.getCommunities();
    results << ">> Número de comunidades detectadas: " << communities.size() << "\n" << std::endl;
    results << ">> Comunidades detectadas:\n";

    for (size_t i{0}; i < communities.size(); i++) {
        results << "\tComunidade " << i << ": [";
        auto members = communities[i].getMembers();
        for (auto it = members.begin(); it != members.end(); ++it) {
            Node* node = *it;
            results << " " << node->getId();
        }
        results << " ]" << std::endl;
    }
    results << std::endl;
    results.close();
}