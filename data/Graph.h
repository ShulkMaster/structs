#ifndef REDEMPTION_GRAPH_H
#define REDEMPTION_GRAPH_H

#include "SingleList.h"
#include <cstdlib>

namespace Data {

    template<typename T>
    class Graph : public IMutable<GraphNode<T> *>, public IEnumerable<GraphNode<T> *> {
    private:
        const int maxNodes = 25;
        Data::SingleList<GraphNode<T> *> *list = nullptr;
        Data::SingleList<GraphNode<T> *> *lCopy = nullptr;

    public:
        Graph() {
            list = new Data::SingleList<GraphNode<T> *>();
        }

        bool Insert(GraphNode<T> *node) override {
            if (list->Count() >= maxNodes) {
                return false;
            }

            // todo check if id exist
            while (list->Next()) {
                auto gNode = list->GetCurrent();
                if (node->value % gNode->value == 0) {
                    node->connections = new SingleNode<GraphNode<T> *>(gNode);
                    auto conns = gNode->connections;
                    while (conns != nullptr) {
                        conns = conns->next;
                    }
                    conns = new SingleNode<GraphNode<T> *>(node);
                }
            }
            list->Reset();
            return list->Insert(node);
        }

        bool Delete(GraphNode<T> *value) override {
            return false;
        }

        bool Replace(int position) override {
            return false;
        }

        GraphNode<T> *GetCurrent() override {
            return list->GetCurrent();
        }

        bool Next() override {
            return list->Next();
        }

        bool Next(int forward) override {
            return list->Next(forward);
        }

        int Count() override {
            return list->Count();
        }

        void Reset() override {
            list->Reset();
        }

    };
}
#endif //REDEMPTION_GRAPH_H
