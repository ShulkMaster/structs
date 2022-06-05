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
    int cursorX = 0;
    int cursorY = 0;
    Graph<Tree<Champion>> *graph = nullptr;
    const int MaxRows = 10;

public:
    const wchar_t Name[11] = L"Grafo LOL";

    explicit MainMenu(Graph<Tree<Champion>> *g) {
        this->graph = g;
    }

    bool HandleKey(int action) {
        switch (action) {
            case 'q':
                return false;
            case 'w':
            case 'W':
            case UpArrow: {
                cursorY = std::max(0, cursorY - 1);
                break;
            }
            case 's':
            case 'S':
            case DownArrow: {
                cursorY = std::min(graph->Count() - 1, cursorY + 1);
                break;
            }
            default:
                return true;
        }
        return true;
    }

    void Print() {
        std::wcout << Name << Jump;
        graph->Reset();
        if (graph->Count() < 1) {
            std::wcout << L"El grafo " << Name << " esta vacio" << Jump;
        } else {
            std::wcout << L"Node ID : Conexiones" << Jump;
        }
        RenderNodes();
        std::wcout << L"navigate ← ↑ → ↓      ⏎ enter node      Edit Ctrl + E       Del to exit" << std::endl;
    }

    void RenderNodes() {
        // array bound already check in cursors positions
        int end = std::min(graph->Count(), cursorY + MaxRows);
        int start = std::max(0, end - MaxRows);
        graph->Next(start);
        for (int i = start; i < end; ++i) {
            auto current = graph->GetCurrent();
            std::wcout << (cursorY == i ? L"=> [" : L"   [");
            std::wcout << current->id << "] : ";
            //showNodes(gCopy, false);
            graph->Next();
            std::wcout << Jump;
        }
    }

};

#endif //REDEMPTION_MAINMENU_H
