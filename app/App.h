#ifndef REDEMPTION_APP_H
#define REDEMPTION_APP_H

#include "iostream"
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

    int ReadPress() {
        int keyCode;
        char byteRead;
        int res = read(STDIN_FILENO, &byteRead, 1);
        if (res == -1 && errno != EAGAIN) {
            write(STDOUT_FILENO, "\x1b[2J", 4);
            write(STDOUT_FILENO, "\x1b[H", 3);
            perror("read");
            exit(1);
        }
        if (iscntrl(byteRead)) {
            std::wprintf(L"%d\r\n", byteRead);
        } else {
            wprintf(L"%d ('%c')\r\n", byteRead, byteRead);
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

    void Run() {
        auto graph = new Graph<Tree<Champion>>();
        for (int i = 0; i < 20; ++i) {
            auto trick = new GraphNode<Tree<Champion>>(i, Tree<Champion>());
            graph->Insert(trick);
        }
        auto *m = new MainMenu(graph);
        bool continues = true;
        PrintBanner();
        while (continues) {
            int action = ReadPress();
            Refresh();
            continues = m->HandleKey(action);
            m->Print();
        }
        std::wcout << Jump << L"Bye bye!" << Jump << std::endl;
        delete m;
        delete graph;
    }
};

#endif //REDEMPTION_APP_H
