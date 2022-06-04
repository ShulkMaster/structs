#include <iostream>
#include "Graph.h"

int main() {
    Data::Graph<int> graph;
    for (int i = 0; i < 10; ++i) {
        graph.Insert(new Data::GraphNode<int>(i, i));
    }
    do {
        std::cout << graph.GetCurrent()->value << "\n";
    } while (graph.Next());
    std::cout << std::endl;
    return 0;
}
