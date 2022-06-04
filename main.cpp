#include <iostream>
#include "Tree.h"

int main() {
    Data::Tree<int> tree;
    for (int i = 0; i < 10; ++i) {
        tree.Insert(new Data::TreeNode<int>(i));
    }
//    do {
//        std::cout << tree. << "\n";
//    } while (graph.Next());
    std::cout << std::endl;
    return 0;
}
