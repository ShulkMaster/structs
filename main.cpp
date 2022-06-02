#include <iostream>
#include "Graph.h"

int main() {
    Data::Graph<int> graph;
    for (int i = 0; i < 20; ++i) {
        graph.Insert(new Data::GraphNode<int>(i));
    }
    graph.ForEach([](auto x) -> void {
        std::cout << x->value << "\n";
    });
    std::cout << std::endl;
    return 0;
}
