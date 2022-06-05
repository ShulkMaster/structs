#include <iostream>
#include "Tree.h"

int main() {
    Data::Tree<int> tree;
    tree.Insert(new Data::TreeNode<int>(5));
    tree.Insert(new Data::TreeNode<int>(2));
    tree.Insert(new Data::TreeNode<int>(7));
    tree.Insert(new Data::TreeNode<int>(8));
    tree.Insert(new Data::TreeNode<int>(9));
    tree.Insert(new Data::TreeNode<int>(6));
    tree.Insert(new Data::TreeNode<int>(3));
    tree.Insert(new Data::TreeNode<int>(1));
    do {
        std::cout << tree.GetCurrent()->value << "\n";
    } while (tree.Next());
    std::cout << std::endl;
    return 0;
}
