#ifndef REDEMPTION_APP_H
#define REDEMPTION_APP_H

#include "Controls.h"
#include "MainMenu.h"
#include <fstream>
#include <cstring>


class App {
private:
    const wchar_t *End = L"\x1B[33m";
    const wchar_t *Red = L"\x1B[31m";
    const wchar_t *Green = L"\x1B[32m";
    const wchar_t *Purple = L"\x1B[33m";
    const wchar_t *Saber = L"\x1B[34m";
    const wchar_t *Saber2 = L"\x1B[35m";
    const wchar_t *Colors[5] = {Red, Green, Purple, Saber, Saber2};

public:

    static const int NullId = -753211;

    void PrintBanner() {
        const std::wstring banner = std::wstring(UNICORN_BANNER);
        const int remaining = banner.length() % 100;
        const int times = banner.length() / 100;
        ushort index = 0;
        auto color = Colors[index];
        while (ReadPress() != ENTER) {
            Refresh();
            for (int i = 0; i < times; i++) {
                index++;
                if (index >= 5) {
                    index = 0;
                }
                color = Colors[index];
                std::wcout << color << banner.substr(i * 100, 100) << End;
            }
            std::wcout << banner.substr(100 * times, remaining) << End << Jump;
            if (index % 10) {
                std::wcout << L"\tPRESS ENTER TO CONTINUE\r\n";
            }
        }
        Refresh();
        std::wcout << Jump;
    }

    static std::wstring Trim(const std::wstring &str) {
        size_t first = str.find_first_not_of(' ');
        if (std::string::npos == first) {
            return str;
        }
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    static bool FillChamp(Tree<Champion> *tree, std::wstring &str) {
        unsigned long start = 1;
        auto split = str.find_first_of(',', start);
        try {
            std::wstring name = Trim(str.substr(start, split - 1));
            start = split + 1;
            split = str.find_first_of(',', start);
            int age = std::stoi(str.substr(start, split));
            start = split + 1;
            std::wstring className = Trim(str.substr(start));
            Champion champ = Champion(age, name, className);
            bool inserted = tree->Insert(new TreeNode<Champion>(champ));
            if (!inserted)
                std::wcout << champ << Jump;
            return inserted;
        } catch (std::out_of_range &ex) {
            std::wcout << str << L"range" << Jump;
        }
        catch (std::invalid_argument &ex) {
            std::wcout << str << L"args" << Jump;
        }
        return false;
    }

    static void FillData(Graph<Tree<Champion> *> *g) {
        std::wifstream dataFile;
        dataFile.open("data.txt");
        if (!dataFile.is_open()) {
            if (dataFile.bad()) {
                std::wcout << L"Error al leer data.txt" << Jump;
                return;
            }
            std::wcout << L"No se encontr?? ninguna datafile llamada data.txt" << Jump;
            return;
        }
        std::wstring dataLine;
        int lines = 0;
        int successNodes = 0;
        int errorNodes = 0;
        int successChamps = 0;
        int errorChamps = 0;
        int lastId = NullId;
        while (dataFile) {
            std::getline(dataFile, dataLine);
            if (dataLine.empty()) continue;
            if (dataLine[0] == L'\t') {
                lines++;
                if (lastId == NullId) continue;
                auto node = g->FindById(lastId);
                if (FillChamp(node->value, dataLine)) {
                    successChamps++;
                } else {
                    errorChamps++;
                }
                continue;
            }
            int start = 0;
            auto split = dataLine.find(',', start);
            try {
                int id = std::stoi(dataLine.substr(start, split));
                auto name = Trim(dataLine.substr(split + 1));
                auto gNode = new GraphNode<Tree<Champion> *>(id, name, new Tree<Champion>());
                bool wasInserted = g->Insert(gNode);
                if (wasInserted) {
                    successNodes++;
                    lastId = id;
                } else {
                    errorNodes++;
                }
            } catch (std::invalid_argument &ex) {
                std::wcout << lines << ' ' << dataLine << Jump;
                errorNodes++;
            } catch (std::out_of_range &ex) {
                std::wcout << lines << ' ' << dataLine << Jump;
            }
            lines++;
        }
        std::wcout << L"Lineas procesadas " << lines << Jump;
        std::wcout << L"Nodos exitosos: \x1B[32m" << successNodes << L"\033[0m | Fallidos \x1B[31m" << errorNodes
                   << L"\033[0m" << Jump;
        std::wcout << L"Campeones exitosos: " << successChamps << L" |  Fallidos \x1B[31m" << errorChamps << L"\033[0m"
                   << Jump;
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

    void Run(termios &raw) {
        auto graph = new Graph<Tree<Champion> *>();
        // time out read bytes
        int vMin = raw.c_cc[VMIN];
        int vTime = raw.c_cc[VTIME];
        raw.c_cc[VMIN] = 0;
        raw.c_cc[VTIME] = 1;
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
        PrintBanner();
        raw.c_cc[VMIN] = vMin;
        raw.c_cc[VTIME] = vTime;
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
        FillData(graph);

        auto *m = new MainMenu(graph);
        bool continues = true;
        while (continues) {
            m->Print();
            int action = ReadPress();
            Refresh();
            if (action == CTRL_KEY('q')) {
                break;
            }
            continues = m->HandleKey(action);
        }
        delete m;
        delete graph;
        std::wcout << Jump << L"Bye bye!" << Jump << std::endl;
    }
};

#endif //REDEMPTION_APP_H
