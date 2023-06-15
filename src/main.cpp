#include "include/Graph.hpp"

#include "executor.cpp"

int main(int argc, char const *argv[]) {
    Graph graph;
    readFile(argv[1], &graph);

    Graph graph_compressed = graph.compression();

    return 0;
}