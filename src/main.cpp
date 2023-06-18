#include "include/Graph.hpp"

#include "executor.cpp"

// #include <chrono>

int main(int argc, char const *argv[]) {
    Graph graph;
    readFile(argv[1], &graph);

    graph.printGraph();

    std::cout << "\n====================================\n";

    auto start = std::chrono::steady_clock::now();
    graph.zhao();
    auto end = std::chrono::steady_clock::now();

    std::cout << "Batata\n";

    printResult(start, end, graph);

    return 0;
}