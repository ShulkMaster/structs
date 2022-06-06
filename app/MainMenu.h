#ifndef REDEMPTION_MAINMENU_H
#define REDEMPTION_MAINMENU_H

#include "Graph.h"
#include "TreeMenu.h"

using namespace Data;

class MainMenu {
private:
    enum State {
        Neutral,
        Adding,
        Editing,
        Submenu,
    };
    int cursorX = 0;
    int cursorY = 0;
    Graph<Tree<Champion>> *graph = nullptr;
    TreeMenu *submenu;
    const int MaxRows = 10;
    const int MaxConnectionToShow = 10;
    State state = Neutral;
    ushort editOptionIndex = 0;
    std::wstring buff;
    std::wstring errors;
    char m_digits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    const wchar_t *options[4] = {
            L"1) Create node 😎\t",
            L"2) Update node 😅\t",
            L"3) Delete node 😈\t",
            L"4) End edit",
    };

    const ushort optionNumber = sizeof(options) / sizeof(wchar_t *);

private:
    void handleMain(int action) {
        switch (action) {
            case CTRL_KEY('e'): {
                // toggle state logic
                state = state == Neutral ? Editing : Neutral;
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
                state = Submenu;
                graph->Reset();
                graph->Next(cursorY);
                submenu->SetTree(graph->GetCurrent());
            }
            default:
                break;
        }
    }

    void handleAction() {
        switch (editOptionIndex) {
            case 0: {
                state = Adding;
                break;
            }
            case 1:
                break;
            case 2:
                graph->Reset();
                graph->Next(cursorY);
                graph->Delete(graph->GetCurrent());
                state = Neutral;
                break;
            case 3:
            default:
                state = Neutral;
                editOptionIndex = 0;
                break;
        }
    }


    bool HandleEditKey(int action) {
        switch (action) {
            case CTRL_KEY('e'): {
                // toggle state logic
                state = state == Neutral ? Editing : Neutral;
                break;
            }
            case RightArrow:
            case 'd':
            case 'D': {
                editOptionIndex = std::min(optionNumber - 1, editOptionIndex + 1);
                break;
            }
            case LeftArrow:
            case 'a':
            case 'A': {
                editOptionIndex = std::max(0, editOptionIndex - 1);
                break;
            }
            case ENTER: {
                handleAction();
                break;
            }
            default:
                break;
        }
        return true;
    }

    void PrintEditMenu() {
        for (ushort i = 0; i < optionNumber; ++i) {
            if (editOptionIndex == i) {
                std::wcout << L"\x1B[34m=>\033[0m" << options[i];
                continue;
            }
            std::wcout << options[i];
        }
        std::wcout << Jump << std::endl;
    }

    void Restore() {
        errors.clear();
        state = Neutral;
        buff.clear();
    }

    void HandleAdding(int action) {
        switch (action) {
            case CTRL_KEY('e'):
                Restore();
                return;
            case Backspace:
                if (!buff.empty()) {
                    buff.pop_back();
                }
                return;
            case ENTER: {
                if (buff.empty()) {
                    errors.clear();
                    errors.append(L"Debe ingresar un valor para el ID");
                    errors.append(Jump);
                    return;
                }
                int id = std::stoi(buff);
                bool wasInserted = graph->Insert(new GraphNode<Tree<Champion>>(id, Tree<Champion>()));
                if (!wasInserted) {
                    errors.clear();
                    errors.append(L"El nodo ya existe");
                    errors.append(Jump);
                    return;
                }
                state = Neutral;
                Restore();
                return;
            }
            default:
                if (buff.length() > 6) return;
                for (char m_digit: m_digits) {
                    if (action == m_digit) {
                        buff.push_back(action);
                        return;
                    }
                }
        }
    }

public:
    const wchar_t Name[11] = L"Grafo LOL";

    explicit MainMenu(Graph<Tree<Champion>> *g) {
        this->graph = g;
        this->submenu = new TreeMenu(Name);
    }

    bool HandleKey(int action) {
        switch (state) {
            case Neutral:
                handleMain(action);
                break;
            case Adding:
                HandleAdding(action);
                break;
            case Editing:
                HandleEditKey(action);
                break;
            case Submenu:
                bool continues = submenu->HandleKey(action);
                state = continues ? state : Neutral;
                break;
        }
        return true;
    }

    void PrintAddingMenu() {
        std::wcout << L"Ingrese el ID del nodo a crear #" << Jump;
        std::wcout << L"ID: " << buff << Jump;
        std::wcout << L"⏎ create node      Cancel Ctrl + E" << Jump;
        if (!errors.empty()) {
            std::wcout << errors << Jump;
        }
        std::wcout << std::endl;
    }

    void Print() {
        if (state == Submenu) {
            submenu->Print();
            return;
        }
        if (state == Adding) {
            PrintAddingMenu();
            return;
        }
        std::wprintf(L"\x1B[31mTexting\033[0m\t\t");
        std::wprintf(L"\x1B[32mTexting\033[0m\t\t");
        std::wprintf(L"\x1B[33mTexting\033[0m\t\t");
        std::wprintf(L"\x1B[34mTexting\033[0m\t\t");
        std::wprintf(L"\x1B[35mTexting\033[0m\n");
        std::wprintf(Jump);
        std::wcout << Name << Jump;
        graph->Reset();
        if (graph->Count() < 1) {
            std::wcout << L"El grafo " << Name << " esta vacio" << Jump;
        } else {
            std::wcout << L"Node ID : Conexiones" << Jump;
        }
        RenderNodes();
        if (state == Editing) {
            PrintEditMenu();
            return;
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
