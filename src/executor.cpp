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

#include <fstream>   // std::ifstream
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

void readFile(char const fileName[], Graph* graph) {
    // Validação inicial dos argumentos
    if (fileName == nullptr) {
        std::cerr << "ERRO :: Argumento com o caminho para o arquivo de teste não foi especificado." << std::endl;
        exit(1);
    }

    std::ifstream file_data(fileName);

    if (not file_data.is_open()) {
        std::cerr << "ERRO :: Arquivo " << fileName << " informado é inválido." << std::endl << std::endl;
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
                       Graph graph) {
    auto time = end - start;

    std::ofstream out_file{"results/test.txt"};

    // Milliseconds (10^-3)
    out_file << ">> Tempo para encontrar as comunidades: ";
    out_file << std::chrono::duration <double, std::milli> (time).count();
    out_file << "ms\n" << std::endl;

    out_file << ">> Número de comunidades detectadas: " << graph.getCommunities().size() << "\n" << std::endl;

    out_file << ">> Comunidades detectadas:\n";

    // for(auto comp : components) {
    //     out_file << "\t > ";
    //     for(int v : comp) {
    //         out_file << v << " ";
    //     }
    //     out_file << "\n";
    // }

    out_file << "\n>> Número de vértices: " << graph.getNodes().size() << std::endl;
    out_file << "\n>> Número de arestas: " << graph.getNumberOfEdges() << std::endl;
}