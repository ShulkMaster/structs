#ifndef REDEMPTION_THREE_H
#define REDEMPTION_THREE_H

#include "Node.h"
#include "Capabilities.h"

namespace Data {

    template<typename T>
    class Tree : public IMutable<TreeNode<T> *> {
    private:
        TreeNode<T> *root = nullptr;
        TreeNode<T> *stack = nullptr;

        bool Insert(TreeNode<T> *node, TreeNode<T> *tree) {
            node->up = tree;
            if (node->value < tree->value) {
                if (tree->left == nullptr) {
                    tree->left = node;
                    return true;
                }
                return Insert(node, tree->left);
            }

            if (tree->right == nullptr) {
                tree->right = node;
                return true;
            }
            return Insert(node, tree->right);
        }

    public:
        bool Insert(TreeNode<T> *node) override {
            if (root == nullptr) {
                root = node;
                stack = root;
                return true;
            }
            return Insert(node, root);
        }

        bool Delete(TreeNode<T> *value) override {
            return false;
        }

        bool Replace(int position) override {
            return false;
        }
    };

}

#endif //REDEMPTION_THREE_H
