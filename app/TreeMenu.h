#ifndef REDEMPTION_TREEMENU_H
#define REDEMPTION_TREEMENU_H

#include <iostream>
#include "Controls.h"
#include "Tree.h"
#include "Champion.h"

class TreeMenu {
private:
    enum State {
        Neutral,
        Adding,
        Editing,
        Updating
    };

    const wchar_t *Name = nullptr;
    State state = Neutral;
    Data::GraphNode<Data::Tree<Champion> *> *node = nullptr;
    Data::Tree<Champion> *tree = nullptr;
    const int width = 100;
    const wchar_t *options[4] = {
            L"1) Create node 😎\t",
            L"2) Update node 😅\t",
            L"3) Delete node 😈\t",
            L"4) End edit",
    };
    ushort editOptionIndex = 0;
    ushort editIndex = 0;
    std::wstring nameBuff;
    std::wstring ageBuff;
    std::wstring classBuff;
    std::wstring errors;

    const ushort optionNumber = sizeof(options) / sizeof(wchar_t *);

    void ChangeToUpdate() {
        editIndex = 0;
        if (tree->GetCurrent() != nullptr) {
            auto value = tree->GetCurrent()->value;
            nameBuff.append(value.name);
            ageBuff.append(std::to_wstring(value.age));
            classBuff.append(value.className);
            state = Updating;
        }
    }

    bool HandleMainKey(int action) {
        switch (action) {
            case 'w':
            case 'W':
            case UpArrow: {
                return tree->NextUp();
            }
            case 'a':
            case 'A':
            case LeftArrow: {
                tree->NextLeft();
                break;
            }
            case 'd':
            case 'D':
            case RightArrow: {
                tree->NextRight();
                break;
            }
            case ENTER:
                ChangeToUpdate();
                break;
            case CTRL_KEY('e'): {
                state = state == Neutral ? Editing : Neutral;
                break;
            }
            case CTRL_KEY('b'):
                return false;
            default:
                break;
        }
        return true;
    }

    void HandleAction() {
        switch (editOptionIndex) {
            case 0: {
                state = Adding;
                break;
            }
            case 1:
                ChangeToUpdate();
                break;
            case 2:
                tree->Delete(tree->GetCurrent());
                state = Neutral;
                break;
            case 3:
            default:
                state = Neutral;
                editOptionIndex = 0;
                break;
        }
    }

    void HandleEditing(int action) {
        switch (action) {
            case '4':
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
            case '1':
                state = Adding;
                break;
            case '2':
                ChangeToUpdate();
                break;
            case '3':
                tree->Delete(tree->GetCurrent());
                state = Neutral;
                break;
            case ENTER: {
                HandleAction();
                break;
            }
            default:
                break;
        }
    }

    void Restore() {
        state = Neutral;
        editIndex = 0;
        nameBuff.clear();
        ageBuff.clear();
        classBuff.clear();
    }

    bool isValid() {
        bool valid = true;
        errors.clear();

        if (ageBuff.empty()) {
            errors.append(L"Debe ingresar una edad");
            errors.append(Jump);
            valid = false;
        }
        if (nameBuff.empty()) {
            errors.append(L"Debe ingresar un nombre");
            errors.append(Jump);
            valid = false;
        }
        if (classBuff.empty()) {
            errors.append(L"Debe ingresar una clase");
            errors.append(Jump);
            valid = false;
        }
        return valid;
    }

    void ProcessInput(int action) {
        // order : name / age / className
        if (action <= CTRL_KEY('z')) return;
        if (action == Backspace || action == Delete) {
            switch (editIndex) {
                case 0:
                    if (!nameBuff.empty()) nameBuff.pop_back();
                    break;
                case 1:
                    if (!ageBuff.empty()) ageBuff.pop_back();
                    break;
                case 2:
                    if (!classBuff.empty()) classBuff.pop_back();
                    break;
            }
            return;
        }
        switch (editIndex) {
            case 0:
                if (nameBuff.length() > 50 && !iscntrl(action)) break;
                nameBuff.push_back(action);
                break;
            case 1:
                if (ageBuff.length() > 6) break;
                for (char m_digit: digits) {
                    if (action == m_digit) {
                        ageBuff.push_back(action);
                        return;
                    }
                }
                break;
            case 2:
                if (classBuff.length() > 60 && !iscntrl(action)) break;
                classBuff.push_back(action);
                break;
            default:
                break;
        }
    }

public:
    explicit TreeMenu(const wchar_t *name) {
        this->Name = name;
    }

    void SetTree(Data::GraphNode<Data::Tree<Champion> *> *pNode) {
        this->node = pNode;
        tree = node->value;
        state = Neutral;
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
                editIndex = std::max(0, editIndex - 1);
                break;
            case DownArrow:
                editIndex = std::min(2, editIndex + 1);
                break;
            case ENTER: {
                if (!isValid()) return;
                int age = std::stoi(ageBuff);
                if (state == Updating) {
                    auto val = &tree->GetCurrent()->value;
                    val->age = age;
                    val->name.clear();
                    val->name.append(nameBuff);
                    val->className.clear();
                    val->className.append(classBuff);
                    Restore();
                    return;
                }
                auto newNode = new Data::TreeNode<Champion>(Champion(age, nameBuff, classBuff));
                bool wasInserted = tree->Insert(newNode);
                if (!wasInserted) {
                    errors.append(L"El nodo ya existe");
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

    bool HandleKey(int action) {
        switch (state) {
            case Neutral:
                return HandleMainKey(action);
            case Updating:
            case Adding:
                HandleAdding(action);
                break;
            case Editing:
                HandleEditing(action);
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

    const wchar_t *GetPointer(ushort index) const {
        return editIndex != index ? L"   " : L"=> ";
    }

    void PrintAddingMenu() {
        std::wcout << L"Creacion de Nodo Arbol" << Jump;
        std::wcout << GetPointer(0) << L"Name: " << nameBuff << Jump;
        std::wcout << GetPointer(1) << L"Edad: " << ageBuff << Jump;
        std::wcout << GetPointer(2) << L"Clase: " << classBuff << Jump;
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
        std::wcout << Name << L"/Node " << node->id << L'-' << node->name << L"/Tree Nivel-" << tree->level << Jump;
        if (state == Adding || state == Updating) {
            PrintAddingMenu();
            return;
        }
        RenderNodes();
        if (state == Editing) {
            PrintEditMenu();
            return;
        }
        std::wcout << L"navigate ← ↑ →       ⏎ enter node      Edit Ctrl + E      Go Back Ctrl + B" << std::endl;
    }

    void RenderNodes() {
        auto current = tree->GetCurrent();
        if (current == nullptr) {
            std::wcout << L"El Arbol esta vacio" << Jump;
            return;
        }
        std::wstring name = current->value.name;
        int minWidth = name.length();
        std::wstring fill;
        std::wstring footer;
        if (minWidth > width - 4) {
            fill = name.substr(0, width - 4);
            footer = std::wstring(width - 2, '=');
            std::wcout << L"\x1B[32m " << footer << L" " << Jump;
            std::wcout << L" |" << fill << L"| " << Jump;
        } else {
            int padding = (width - 4) / 2 - minWidth;
            fill.append(padding, L' ');
            footer = fill + std::wstring(minWidth + 2, '=');
            std::wcout << L"\x1B[32m " << footer << L" " << Jump;
            std::wcout << fill << L"| " << name << L" |" << Jump;
        }
        std::wcout << L" " << footer << L" \033[0m" << Jump;
        RenderChildren(current, fill.length(), std::min(minWidth + 2, width - 2));
        std::wcout << std::endl;
    }

    static void RenderChildren(Data::TreeNode<Champion> *node, int beginning, int width) {
        std::wstring fill = std::wstring(beginning, ' ');
        std::wstring space = std::wstring(width, ' ');
        std::wcout << fill << L'|' << space << L'|' << Jump;
        std::wcout << fill << L'|' << space << L'|' << Jump;
        std::wcout << fill << L'|' << space << L'|' << Jump;
        std::wstring lines[3] = {std::wstring(L"")};
        if (node->left != nullptr) {
            std::wstring name = node->left->value.name;
            if (name.length() > beginning) {
                lines[0].append(beginning, L'_');
                lines[1].append(L'|' + name.substr(0, beginning - 2) + L'|');
                lines[2].append(beginning, L'_');
            } else {
                std::wstring fillSpace = std::wstring(beginning - name.length(), L' ');
                lines[0].append(fillSpace);
                lines[1].append(fillSpace.length() - 1, L' ');
                lines[2].append(fillSpace);
                lines[0].append(name.length(), L'_');
                lines[1].append(L'|' + name + L'|');
                lines[2].append(name.length(), L'_');
            }
        } else {
            lines[0].append(beginning, L' ');
            lines[1].append(beginning + 1, L' ');
            lines[2].append(beginning, L' ');
        }
        if (node->right != nullptr) {
            std::wstring name = node->right->value.name;
            lines[0].append(space.length() + 1, L' ');
            lines[1].append(space);
            lines[2].append(space.length() + 1, L' ');
            lines[0].append(name.length() + 2, L'_');
            lines[1].append(L"|" + name + L"|");
            lines[2].append(name.length() + 2, L'_');
        }
        std::wcout << lines[0] << Jump;
        std::wcout << lines[1] << Jump;
        std::wcout << lines[2] << Jump;
    }

};

#endif //REDEMPTION_TREEMENU_H
