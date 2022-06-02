#include <iostream>
#include "Graph.h"

int main() {
    Data::SingleList<int> graph;
    for (int i = 0; i < 20; ++i) {
        graph.Insert(i);
    }
    graph.ForEach([](auto x) -> void {
        std::cout << x << "\n";
    });
    std::cout << std::endl;
    return 0;
}
