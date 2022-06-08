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
        Updating,
    };
    int cursorX = 0;
    int cursorY = 0;
    Graph<Tree<Champion> *> *graph = nullptr;
    TreeMenu *submenu;
    const int MaxRows = 10;
    const int MaxConnectionToShow = 10;
    State state = Neutral;
    ushort editOptionIndex = 0;
    std::wstring buffId;
    std::wstring buffName;
    bool isId = true;
    std::wstring errors;

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
            case 'a':
            case 'A':
            case LeftArrow: {
                cursorX = std::max(0, cursorX - 1);
                break;
            }
            case 'd':
            case 'D':
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

    void GoToUpdate() {
        graph->Reset();
        graph->Next(cursorY);
        isId = false;
        auto edit = graph->GetCurrent();
        if (edit != nullptr) {
            state = Updating;
            buffId.append(std::to_wstring(edit->id));
            buffName.append(edit->name);
        }
    }

    void DeleteItem() {
        graph->Reset();
        graph->Next(cursorY);
        graph->Delete(graph->GetCurrent());
        cursorY = std::max(0, cursorY - 1);
        state = Neutral;
    }

    void handleAction() {
        switch (editOptionIndex) {
            case 0: {
                state = Adding;
                break;
            }
            case 1: {
                GoToUpdate();
                break;
            }
            case 2:
                DeleteItem();
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
            case '4':
            case CTRL_KEY('e'): {
                // toggle state logic
                state = state == Neutral ? Editing : Neutral;
                break;
            }
            case '1':
                state = Adding;
                editOptionIndex = 0;
                break;
            case '2':
                GoToUpdate();
                break;
            case '3':
                DeleteItem();
                break;
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
        buffId.clear();
        buffName.clear();
        isId = true;
    }

    bool isValid() {
        bool valid = true;
        errors.clear();

        if (buffId.empty()) {
            errors.append(L"Debe ingresar un valor para el ID");
            errors.append(Jump);
            valid = false;
        }
        if (buffName.empty()) {
            errors.append(L"Debe ingresar un nombre de nodo");
            errors.append(Jump);
            valid = false;
        }
        return valid;
    }

    void ProcessInput(int action) {
        if (action <= CTRL_KEY('z')) return;
        if (isId) {
            if (buffId.length() > 6) return;

            for (char m_digit: digits) {
                if (action == m_digit) {
                    buffId.push_back(action);
                    return;
                }
            }
            return;
        }
        if (buffName.length() > 20 && !iscntrl(action)) return;
        buffName.push_back(action);
    }

    void HandleAdding(int action) {
        switch (action) {
            case CTRL_KEY('e'):
                Restore();
                return;
            case LeftArrow:
            case RightArrow:
                break;
            case UpArrow:
            case DownArrow:
                isId = !isId;
                return;
            case Backspace:
                if (isId) {
                    if (!buffId.empty()) buffId.pop_back();
                } else if (!buffName.empty()) buffName.pop_back();
                return;
            case ENTER: {
                if (!isValid()) return;
                int id = std::stoi(buffId);
                bool wasInserted = graph->Insert(new GraphNode<Tree<Champion> *>(id, buffName, new Tree<Champion>()));
                if (!wasInserted) {
                    errors.append(L"El nodo ya existe o alcanzo el limite ").append(
                            std::to_wstring(Graph<Tree<Champion>>::maxNodes));
                    errors.append(Jump);
                    return;
                }
                Restore();
                return;
            }
            default:
                ProcessInput(action);
        }
    }

    void HandleUpdate(int action) {
        switch (action) {
            case CTRL_KEY('e'):
                Restore();
                return;
            case LeftArrow:
            case RightArrow:
            case UpArrow:
            case DownArrow:
                break;
            case Backspace:
                if (isId) {
                    if (!buffId.empty()) buffId.pop_back();
                } else if (!buffName.empty()) buffName.pop_back();
                return;
            case ENTER: {
                if (!isValid()) return;
                auto current = graph->GetCurrent();
                current->name.clear();
                current->name.append(buffName);
                state = Neutral;
                Restore();
                return;
            }
            default:
                ProcessInput(action);
        }
    }

public:
    const wchar_t Name[11] = L"Grafo LOL";

    explicit MainMenu(Graph<Tree<Champion> *> *g) {
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
            case Submenu: {
                bool continues = submenu->HandleKey(action);
                state = continues ? state : Neutral;
                break;
            }
            case Updating:
                HandleUpdate(action);
                break;
        }
        return true;
    }

    void PrintAddingMenu() {
        std::wcout << L"Creacion de Nodo" << Jump;
        if (isId) {
            std::wcout << L"=> ID: " << buffId << Jump;
            std::wcout << L"   Nombre: " << buffName << Jump;
        } else {
            std::wcout << L"   ID: " << buffId << Jump;
            std::wcout << L"=> Nombre: " << buffName << Jump;
        }
        if (state == Adding) {
            std::wcout << L"⏎ create node      Cancel Ctrl + E" << Jump;
        } else {
            std::wcout << L"⏎ Actualizar nodo      Cancel Ctrl + E" << Jump;
        }
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

        if (state == Adding || state == Updating) {
            PrintAddingMenu();
            return;
        }

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

    void RenderConnections(GraphNode<Tree<Champion> *> *node, bool isSelected) {
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
