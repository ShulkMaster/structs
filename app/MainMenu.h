#ifndef REDEMPTION_MAINMENU_H
#define REDEMPTION_MAINMENU_H

#include "Graph.h"
#include "TreeMenu.h"

using namespace Data;

class MainMenu {
private:
    int cursorX = 0;
    int cursorY = 0;
    Graph<Tree<Champion>> *graph = nullptr;
    TreeMenu *submenu;
    const int MaxRows = 10;
    const int MaxConnectionToShow = 10;
    bool isEditing = false;
    bool isInSubmenu = false;

public:
    const wchar_t Name[11] = L"Grafo LOL";

    explicit MainMenu(Graph<Tree<Champion>> *g) {
        this->graph = g;
        this->submenu = new TreeMenu(Name);
    }

    bool HandleKey(int action) {
        if (isInSubmenu) {
            isInSubmenu = submenu->HandleKey(action);
            return true;
        }
        switch (action) {
            case CTRL_KEY('e'): {
                isEditing = !isEditing;
                break;
            }
            case 'w':
            case 'W':
            case UpArrow: {
                cursorY = std::max(0, cursorY - 1);
                cursorX = 0;
                break;
            }
            case 's':
            case 'S':
            case DownArrow: {
                cursorY = std::min(graph->Count() - 1, cursorY + 1);
                cursorX = 0;
                break;
            }
            case LeftArrow: {
                cursorX = std::max(0, cursorX - 1);
                break;
            }
            case RightArrow: {
                int xMax = graph->ConnectionsAt(cursorY);
                cursorX = std::min(xMax - 1, cursorX + 1);
                break;
            }
            case ENTER: {
                isInSubmenu = true;
                graph->Reset();
                graph->Next(cursorY);
                submenu->SetTree(graph->GetCurrent());
            }
            default:
                break;
        }
        return true;
    }

    void Print() {
        if(isInSubmenu){
            submenu->Print();
            return;
        }
        std::wprintf(L"\x1B[31mTexting\033[0m\t\t");
        std::wprintf(L"\x1B[32mTexting\033[0m\t\t");
        std::wprintf(L"\x1B[33mTexting\033[0m\t\t");
        std::wprintf(L"\x1B[34mTexting\033[0m\t\t");
        std::wprintf(L"\x1B[35mTexting\033[0m\n");
        std::wcout << Name << Jump;
        graph->Reset();
        if (graph->Count() < 1) {
            std::wcout << L"El grafo " << Name << " esta vacio" << Jump;
        } else {
            std::wcout << L"Node ID : Conexiones" << Jump;
        }
        RenderNodes();
        if (isEditing) {
            std::wcout << L"me la pela" << Jump;
        }
        std::wcout << L"navigate ← ↑ → ↓      ⏎ enter node      Edit Ctrl + E       Quit Ctrl + Q" << std::endl;
    }

    void RenderNodes() {
        // array bound already check in cursors positions
        int end = std::min(graph->Count(), cursorY + MaxRows);
        int start = std::max(0, end - MaxRows);
        graph->Next(start);
        for (int i = start; i < end; ++i) {
            auto current = graph->GetCurrent();
            std::wcout << (cursorY == i ? L"\x1B[32m=> [" : L"   [");
            std::wcout << current->id << "]\033[0m : ";
            RenderConnections(current, cursorY == i);
            graph->Next();
            std::wcout << Jump;
        }
    }

    void RenderConnections(GraphNode<Tree<Champion>> *node, bool isSelected) {
        int total = graph->ConnectionsAt(node);
        int end = std::min(total, cursorX + MaxConnectionToShow);
        if (!isSelected) {
            end = std::min(total, MaxConnectionToShow);
        }
        int start = std::max(0, end - MaxConnectionToShow);
        auto nCopy = node->connections;
        std::wcout << L"Total: " << total << L" { ";
        for (int i = 0; i < start; ++i) {
            nCopy = nCopy->next;
        }
        for (int i = start; i < end; ++i) {
            if (i == cursorX && isSelected) {
                std::wcout << L" \x1B[31m[" << nCopy->value->id << L"]\033[0m ";
                nCopy = nCopy->next;
                continue;
            }
            std::wcout << nCopy->value->id << L", ";
            nCopy = nCopy->next;
        }
        std::wcout << L"}" << Jump;
    }

};

#endif //REDEMPTION_MAINMENU_H
