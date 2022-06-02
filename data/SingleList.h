#ifndef REDEMPTION_LIST_H
#define REDEMPTION_LIST_H

#include "Node.h"
#include "Capabilities.h"

namespace Data {

    template<typename T>
    class SingleList : public IMutable<T>, public IEnumerable<T> {
    private:
        SingleNode<T> *root = nullptr;
        int count = 0;

    public:
        bool Insert(T node) override {
            if (root == nullptr) {
                root = new SingleNode<T>(node);
                count++;
                return true;
            }

            auto temp = root;
            while (temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = new SingleNode<T>(node);
            count++;
            return true;
        }

        bool Delete(T node) override {
            return false;
        }


        void ForEach(void (*func)(T node)) override {
            auto temp = root;
            for (; temp != nullptr; temp = temp->next) {
                func(temp->value);
            }
        }

        bool Replace(int position) override {
            return false;
        }

        T GetCurrent() override {
            return root->value;
        }

        bool Next() override {

            return false;
        }

        void Next(int forward) override {

        }

        int Count() override {
            return count;
        }

    };

}

#endif //REDEMPTION_LIST_H
