#ifndef REDEMPTION_TREEMENU_H
#define REDEMPTION_TREEMENU_H

#include <iostream>
#include "Controls.h"
#include "Tree.h"
#include "Champion.h"

class TreeMenu {
private:
    int level = 0;
    const wchar_t *Name = nullptr;
    bool isEditing = false;
    Data::GraphNode<Data::Tree<Champion>> *node = nullptr;
    Data::Tree<Champion> *tree;
    const int width = 100;
public:
    TreeMenu(const wchar_t *name) {
        this->Name = name;
    }

    void SetTree(Data::GraphNode<Data::Tree<Champion>> *pNode) {
        this->node = pNode;
        tree = &(node->value);
    }

    void Clear() {
        node = nullptr;
        tree = nullptr;
    }

    bool HandleKey(int action) {
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
            case CTRL_KEY('e'): {
                isEditing = !isEditing;
                break;
            }
            case CTRL_KEY('b'): {
                isEditing = false;
                return false;
            }
            default:
                break;
        }
        return true;

    }

    void Print() {
        std::wcout << Name << L"/Node " << node->id << Jump;
        std::wcout << L"Nivel" << tree->level << Jump;
        RenderNodes();
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
