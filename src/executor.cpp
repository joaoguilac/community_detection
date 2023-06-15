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

void processLine(std::string line, Graph* graph) {
    std::istringstream edge(line);
    int id_node1, id_node2;
    edge >> id_node1;
    edge >> id_node2;

    // Node node1(-1), node2(-1);
    // // Criar nós
    // if (not graph->nodeExists(id_node1)) {
    //     node1 = Node(id_node1);
    // }
    // else {
    //     node1 = graph->getNodeReference(id_node1);
    // }

    // if (not graph->nodeExists(id_node2)) {
    //     node2 = Node(id_node2);
    // }
    // else {
    //     node1 = graph->getNodeReference(id_node1);
    // }

    // // Adicionar na lista de adjacência de cada nó
    // if ()
    // node1.addAdjacent({&node2, 1});
    // node2.addAdjacent({&node1, 1});
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
    while (std::getline(file_data, line)) {
        processLine(line, graph);
    }
}