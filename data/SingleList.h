#ifndef REDEMPTION_LIST_H
#define REDEMPTION_LIST_H

#include "Node.h"
#include "Capabilities.h"

namespace Data {

    template<typename T>
    class SingleList : public IMutable<SingleNode<T>>, public IEnumerable<SingleNode<T>> {
    private:
        SingleNode<T> *root = nullptr;
        int count = 0;

    public:
        bool Insert(SingleNode<T> *node) override {
            if (root == nullptr) {
                root = node;
                count++;
                return true;
            }

            auto temp = root;
            while (temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = node;
            count++;
            return true;
        }

        bool Delete(SingleNode<T> *node) override {
            return false;
        }

        bool Delete(int position) override {
            return false;
        }


        void ForEach(void (*func)(SingleNode<T>*)) override {
            auto temp = root;
            for (; temp != nullptr; temp = temp->next) {
                func(temp);
            }
        }

        bool Replace(int position) override {
            return false;
        }

        SingleNode<T> *GetCurrent() override {
            return root;
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
