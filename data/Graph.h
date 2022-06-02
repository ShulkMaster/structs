#ifndef REDEMPTION_GRAPH_H
#define REDEMPTION_GRAPH_H

#include "SingleList.h"

namespace Data {

    template<typename T>
    class Graph : public IMutable<GraphNode<T>>, public IEnumerable<GraphNode<T>> {
    private:
        const int maxNodes = 25;
        Data::SingleList<GraphNode<T>*> *list = nullptr;
    public:
        Graph() {
            list = new Data::SingleList<GraphNode<T>>();
        }

        bool Insert(GraphNode<T> *node) override {
            if (list->Count() >= maxNodes) {
                return false;
            }

            return list->Insert(node);
        }

        bool Delete(GraphNode<T> *value) override {
            return false;
        }

        bool Delete(int position) override {
            return false;
        }

        bool Replace(int position) override {
            return false;
        }

        GraphNode<T> *GetCurrent() override {
            return nullptr;
        }

        bool Next() override {
            return false;
        }

        void Next(int forward) override {

        }

        int Count() override {
            return list->Count();
        }

        void ForEach(void (*func)(GraphNode<T> *)) override {
            list->ForEach(func);
        }

    };
}
#endif //REDEMPTION_GRAPH_H
