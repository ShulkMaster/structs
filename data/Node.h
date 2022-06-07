#include <utility>

#ifndef REDEMPTION_NODE_H
#define REDEMPTION_NODE_H

namespace Data {


    template<typename T>
    class Node {
    public:
        T value;

        explicit Node(T val) : value(val) {}
    };

    template<typename T>
    class SingleNode : public Node<T> {
    public:
        SingleNode<T> *next = nullptr;

        explicit SingleNode(T val) : Node<T>(val) {}

        virtual ~SingleNode() {
            std::wcout << L"L";
        }
    };

    template<typename T>
    class GraphNode : public Node<T> {
    public:
        int id;
        std::wstring name;
        SingleNode<GraphNode<T> *> *connections = nullptr;

        explicit GraphNode(int id, std::wstring name, T val) : id(id), name(name), Node<T>(val) {}

        virtual ~GraphNode() {
            std::wcout << L"Deleting node" << id << Jump;
            std::wcout << L"\tDeleting connections :";
            auto curren = connections;
            while (curren != nullptr) {
                auto next = curren->next;
                std::wcout << curren->value->id << L',';
                delete curren;
                curren = next;
            }
            std::wcout << Jump;
        }
    };

    template<typename T>
    class TreeNode : public Node<T> {
    public:
        TreeNode<T>* up = nullptr;
        TreeNode<T>* left = nullptr;
        TreeNode<T>* right = nullptr;

        explicit TreeNode(T val) : Node<T>(val) {}
    };

}
#endif //REDEMPTION_NODE_H
