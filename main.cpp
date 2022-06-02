#include <iostream>
#include "SingleList.h"

int main() {
    Data::SingleList<int> list;
    for (int i = 0; i < 20; ++i) {
        list.Insert(new Data::SingleNode<int>(i));
    }
    list.ForEach([](auto x) -> void {
        std::cout << x->value << "\n";
    });
    std::cout << std::endl;
    return 0;
}
