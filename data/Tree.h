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

        bool Contains(TreeNode<T> *node, TreeNode<T> *subtree) {
            if(subtree == nullptr) return false;
            if(subtree->value == node->value) return true;
            return Contains(node, subtree->left) || Contains(node, subtree->right);
        }

        bool Insert(TreeNode<T> *node, TreeNode<T> *tree) {
            if (node == nullptr) return false;
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

        bool Delete(TreeNode<T> *node, TreeNode<T> *tree) {
            if (tree == nullptr) return false;
            if (tree->value == node->value) {
                auto parent = tree->up;
                auto left = tree->left;
                auto right = tree->right;
                if (parent->left == tree) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
                delete tree;
                Insert(left, parent);
                Insert(right, parent);
                return Delete(node, parent->left) || Delete(node, parent->right);
            }
            return Delete(node, tree->left) || Delete(node, tree->right);
        }

        void DeleteTree(TreeNode<T> *node, int printed) {
            if (node == nullptr) return;
            if (printed > 4) {
                printed = 0;
                std::wcout << Jump;
            } else {
                printed++;
            }
            if (printed == 0) {
                std::wcout << L"\t\t";
            }
            std::wcout << node->value << L", ";
            DeleteTree(node->left, printed);
            DeleteTree(node->right, printed);
            delete node;
        }

    public:

        virtual ~Tree() {
            std::wcout << L"\tDeleting " << L"Tree" << Jump << L"\t\t";
            DeleteTree(root, 0);
            std::wcout << Jump;
        }

        TreeNode<T> *GetRoot() {
            return root;
        }

        bool Insert(TreeNode<T> *node) override {
            if (node == nullptr) return false;
            if (root == nullptr) {
                root = node;
                stack = root;
                count++;
                return true;
            }
            if(Contains(node, root)) return false;
            return Insert(node, root);
        }

        bool Delete(TreeNode<T> *value) override {
            Reset();
            if (value == nullptr) return false;
            if (value->value == stack->value) {
                auto left = stack->left;
                auto right = stack->right;
                if (left != nullptr) {
                    left->up = nullptr;
                    Insert(right, left);
                    stack = left;
                    delete root;
                    root = stack;
                    return true;
                }
                if (right != nullptr) {
                    stack = right;
                    right->up = nullptr;
                    stack = right;
                    delete root;
                    root = stack;
                    return true;
                }
                delete root;
                root = stack = nullptr;
                return true;
            }
            return Delete(value, stack->left) || Delete(value, stack->right);
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
            if (stack == nullptr || stack->up == nullptr) {
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
