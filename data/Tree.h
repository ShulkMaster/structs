#ifndef REDEMPTION_THREE_H
#define REDEMPTION_THREE_H

#include "Node.h"
#include "Capabilities.h"

namespace Data {

    template<typename T>
    class Tree : public IMutable<TreeNode<T> *> {
    public:
        int level = 0;
    private:
        TreeNode<T> *root = nullptr;
        TreeNode<T> *stack = nullptr;
        int count = 0;

        bool Insert(TreeNode<T> *node, TreeNode<T> *tree) {
            node->up = tree;
            if (node->value < tree->value) {
                if (tree->left == nullptr) {
                    tree->left = node;
                    count++;
                    return true;
                }
                return Insert(node, tree->left);
            }

            if (tree->right == nullptr) {
                tree->right = node;
                count++;
                return true;
            }
            return Insert(node, tree->right);
        }

        TreeNode<T> *JumpToNext(TreeNode<T> *tree) {
            if (tree->up == nullptr) return tree;
            auto up = tree->up;
            for (int i = level; i > 0; --i) {
                level--;
                up = up->up;
            }
            if (up->right == nullptr) {
                while (up->right == nullptr && up != nullptr) {
                    up = up->up;
                }
            }
            return up;
        }

    public:

        TreeNode<T> *GetRoot() {
            return root;
        }

        bool Insert(TreeNode<T> *node) override {
            if (root == nullptr) {
                root = node;
                stack = root;
                count++;
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

        TreeNode<T> *GetCurrent() {
            return stack;
        }

        bool NextRight() {
            if (stack->right == nullptr) {
                return false;
            }
            level++;
            stack = stack->right;
            return true;
        }

        bool NextLeft() {
            if (stack->left == nullptr) {
                return false;
            }
            level++;
            stack = stack->left;
            return true;
        }

        bool NextUp() {
            if (stack->up == nullptr) {
                return false;
            }
            level--;
            stack = stack->up;
            return true;
        }

        int Count() {
            return count;
        }

        void Reset() {
            stack = root;
        }
    };

}

#endif //REDEMPTION_THREE_H
