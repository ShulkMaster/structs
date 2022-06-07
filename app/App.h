#ifndef REDEMPTION_APP_H
#define REDEMPTION_APP_H

#include "Controls.h"
#include "MainMenu.h"


class App {
public:

    static void PrintBanner() {
        std::wcout << UNICORN_BANNER << std::endl;
    }

    static int ReadControl(char byte) {
        switch (byte) {
            case 'A':
                return UpArrow;
            case 'B':
                return DownArrow;
            case 'C':
                return RightArrow;
            case 'D':
                return LeftArrow;
            default:
                return byte + 0;
        }
    }

    static int ReadExtend(char byte1, char byte2) {
        if (byte2 == '~' && byte1 == '3') {
            return Delete;
        }
        return ReadControl(byte1);
    }

    static void Refresh() {
        write(STDOUT_FILENO, "\x1b[2J", 4);
        write(STDOUT_FILENO, "\x1b[H", 3);
    }

    int static ReadPress() {
        int keyCode;
        char byteRead;
        int res = read(STDIN_FILENO, &byteRead, 1);
        if (res == -1 && errno != EAGAIN) {
            write(STDOUT_FILENO, "\x1b[2J", 4);
            write(STDOUT_FILENO, "\x1b[H", 3);
            perror("read");
            exit(1);
        }
        if (byteRead != Seq) {
            keyCode = 0 + byteRead;
            return keyCode;
        }
        char seq[3];
        if (read(STDIN_FILENO, &seq[0], 1) != 1) return ESC;
        if (read(STDIN_FILENO, &seq[1], 1) != 1) return ESC;
        if (seq[0] == '[') {
            if (seq[1] >= '0' && seq[1] <= '9') {
                if (read(STDIN_FILENO, &seq[2], 1) != 1) return ESC;
                return ReadExtend(seq[1], seq[2]);
            }
            return ReadControl(seq[1]);
        }
        return ESC;
    }

    static void Run() {
        auto graph = new Graph<Tree<Champion>*>();
        for (int i = 0; i < 20; ++i) {
            auto trick = new GraphNode<Tree<Champion> *>(i, L"Node", new Tree<Champion>());
            auto tree = new Data::Tree<Champion>();
            for (int j = 3; j < 6; ++j) {
                int age = (8 - j) * 5;
                auto name = std::wstring(L"Champion").append(std::to_wstring(j));
                auto className = std::wstring(L"Chatarrero");
                auto champ = Champion(age, name, className);
                name.clear();
                age = (2 + j) * 5;
                name.clear();
                name.append(L"Champ").append(std::to_wstring(6 - j));
                auto champ2 = Champion(age,name, className);
                tree->Insert(new TreeNode<Champion>(champ));
                tree->Insert(new TreeNode<Champion>(champ2));
            }
            trick->value = tree;
            graph->Insert(trick);
        }
        auto *m = new MainMenu(graph);
        bool continues = true;
        PrintBanner();
        while (continues) {
            int action = ReadPress();
            Refresh();
            if(action == CTRL_KEY('q')){
                break;
            }
            continues = m->HandleKey(action);
            m->Print();
        }
        delete m;
        delete graph;
        std::wcout << Jump << L"Bye bye!" << Jump << std::endl;
    }
};

#endif //REDEMPTION_APP_H
