#ifndef REDEMPTION_LIST_H
#define REDEMPTION_LIST_H

#include "Node.h"
#include "Capabilities.h"

namespace Data {

    template<typename T>
    class SingleList : public IMutable<T>, public IEnumerable<T> {
    private:
        SingleNode<T> *root = nullptr;
        SingleNode<T> *stack = nullptr;
        int count = 0;

    public:

        virtual ~SingleList() {
            while (root != nullptr) {
                auto temp = root->next;
                delete root->value;
                root = temp;
            }
        }

        bool Insert(T node) override {
            if (root == nullptr) {
                root = new SingleNode<T>(node);
                count++;
                return true;
            }

            auto temp = root;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = new SingleNode<T>(node);
            count++;
            return true;
        }

        bool Delete(T node) override {
            Reset();
            if (node == nullptr) return false;
            if (stack->value == node) {
                auto temp = stack->next;
                delete stack;
                root = temp;
                stack = temp;
                count--;
                return true;
            }
            auto prev = stack;
            stack = stack->next;
            while (stack != nullptr) {
                auto temp = stack->next;
                if (stack->value == node) {
                    prev->next = temp;
                    delete stack;
                    stack = temp;
                    count--;
                    continue;
                }
                prev = stack;
                stack = temp;
            }
            return true;
        }

        void Reset() override {
            stack = root;
        }

        bool Replace(int position) override {
            return false;
        }

        T GetCurrent() override {
            return stack->value;
        }

        bool Next() override {
            if (stack == nullptr || stack->next == nullptr) return false;
            stack = stack->next;
            return true;
        }

        bool Next(int forward) override {
            for (int i = 0; i < forward; ++i) {
                if (!Next()) {
                    return false;
                }
            }
            return true;
        }

        int Count() override {
            return count;
        }

    };

}

#endif //REDEMPTION_LIST_H
