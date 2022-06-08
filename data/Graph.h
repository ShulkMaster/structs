#ifndef REDEMPTION_GRAPH_H
#define REDEMPTION_GRAPH_H

#include "SingleList.h"
#include <cstdlib>

namespace Data {

    template<typename T>
    class Graph : public IMutable<GraphNode<T> *>, public IEnumerable<GraphNode<T> *> {
    private:
        Data::SingleList<GraphNode<T> *> *list = nullptr;

        bool Contains(int id) {
            Reset();
            for (int i = 0; i < Count(); ++i) {
                auto current = list->GetCurrent();
                if (current->id == id) {
                    return true;
                }
                list->Next();
            }
            return false;
        }

    public:
        static const int maxNodes = 25;

        Graph() {
            list = new Data::SingleList<GraphNode<T> *>();
        }

        virtual ~Graph() {
            std::wcout << L"Deleting list" << Jump;
            delete list;
        }

        GraphNode<T> *FindById(int id) {
            Reset();
            for (int i = 0; i < Count(); ++i) {
                if (GetCurrent()->id == id) return GetCurrent();
                Next();
            }
            return nullptr;
        }

        int ConnectionsAt(GraphNode<T> *node) {
            auto copy = node->connections;
            int count = 0;
            while (copy != nullptr) {
                copy = copy->next;
                count++;
            }
            return count;
        }

        int ConnectionsAt(int index) {
            list->Reset();
            list->Next(index);
            auto node = list->GetCurrent();
            if (node == nullptr) return 0;
            return ConnectionsAt(node);
        }

        bool Insert(GraphNode<T> *node) override {
            if (list->Count() >= maxNodes || Contains(node->id)) {
                return false;
            }

            Reset();
            for (int i = 0; i < Count(); ++i) {
                auto gNode = list->GetCurrent();
                if (std::rand() % 2 == 0) {
                    if (node->connections == nullptr) {
                        node->connections = new SingleNode<GraphNode<T> *>(gNode);
                    } else {
                        auto temp = node->connections;
                        while (temp->next != nullptr) {
                            temp = temp->next;
                        }
                        temp->next = new SingleNode<GraphNode<T> *>(gNode);
                    }
                    auto conns = gNode->connections;
                    if (conns == nullptr) {
                        gNode->connections = new SingleNode<GraphNode<T> *>(node);
                    } else {
                        while (conns->next != nullptr) {
                            conns = conns->next;
                        }
                        conns->next = new SingleNode<GraphNode<T> *>(node);
                    }
                }
                list->Next();
            }
            return list->Insert(node);
        }

        bool Delete(GraphNode<T> *value) override {
            Reset();
            do {
                auto listNode = list->GetCurrent();
                if (listNode == nullptr || listNode->connections == nullptr) continue;
                SingleNode<GraphNode<T> *> *prev;
                SingleNode<GraphNode<T> *> *cons = listNode->connections;
                if (value->id == cons->value->id) {
                    auto temp = cons;
                    listNode->connections = cons->next;
                    delete temp;
                    continue;
                }
                prev = cons;
                cons = cons->next;

                while (cons != nullptr) {
                    auto temp = cons->next;
                    if (cons->value->id == value->id) {
                        prev->next = temp;
                        delete cons;
                        cons = temp;
                        continue;
                    }
                    prev = cons;
                    cons = cons->next;
                }
            } while (list->Next());
            bool wasDeleted = list->Delete(value);
            delete value;
            return wasDeleted;
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
