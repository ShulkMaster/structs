#ifndef REDEMPTION_THREE_H
#define REDEMPTION_THREE_H

#include "Node.h"
#include "Capabilities.h"

namespace Data {

    template<typename T>
    class Tree : public IMutable<TreeNode<T> *>, public IEnumerable<TreeNode<T> *> {
    private:
        TreeNode<T> *root = nullptr;
        TreeNode<T> *stack = nullptr;
        int jumps = 0;
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
            for (int i = jumps; i > 0; --i) {
                jumps--;
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

        TreeNode<T> * GetRoot() {
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

        TreeNode<T> *GetCurrent() override {
            return stack;
        }

        bool Next() override {
            if (stack->left != nullptr) {
                stack = stack->left;
                return true;
            }
            if (stack->right != nullptr) {
                stack = stack->right;
                jumps++;
                return true;
            }

            auto next = JumpToNext(stack);
            if (stack == next || stack == root) {
                return false;
            }
            if(next->right == stack){
                next = JumpToNext(next);
            }
            jumps++;
            stack = next->right;
            return true;
        }

        bool Next(int forward) override {
            return false;
        }

        int Count() override {
            return count;
        }

        void Reset() override {
            stack = root;
        }
    };

}

#endif //REDEMPTION_THREE_H
