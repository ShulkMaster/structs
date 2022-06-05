#ifndef REDEMPTION_MAINMENU_H
#define REDEMPTION_MAINMENU_H

#include "Controls.h"
#include <iostream>
#include "Graph.h"
#include "Tree.h"
#include "Champion.h"

using namespace Data;

class MainMenu {
private:
    Graph<Tree<Champion> *> *graph = new Graph<Tree<Champion> *>();

public:
    MainMenu() {
        for (int i = 0; i < 10; ++i) {
            auto *tree = new Tree<Champion>();
            graph->Insert(new GraphNode<Tree<Champion> *>(i, tree));
        }
    }

    bool TakeAction(int action) {
        if(action == 'q') {
            return false;
        }
        std::wcout << L"__________________ Main Menu _______________________________\r\n";
        return true;
    }

};

#endif //REDEMPTION_MAINMENU_H
