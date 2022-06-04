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
    };

    template<typename T>
    class GraphNode : public Node<T> {
    public:
        int id;
        SingleNode<GraphNode<T> *> *connections = nullptr;

        explicit GraphNode(int id, T val) : id(id), Node<T>(val) {}
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
