#include "include/Graph.hpp"

#include "executor.cpp"

int main(int argc, char const *argv[]) {
    Graph graph;
    std::string input_file = argv[1];
    readFile(input_file, &graph);

    auto start = std::chrono::steady_clock::now();
    graph.zhao();
    auto end = std::chrono::steady_clock::now();

    std::string output_file = argv[2];
    printResult(start, end, graph, output_file);

    return 0;
}