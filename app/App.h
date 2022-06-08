#ifndef REDEMPTION_APP_H
#define REDEMPTION_APP_H

#include "Controls.h"
#include "MainMenu.h"
#include <fstream>


class App {
public:

    static void PrintBanner() {
        std::wcout << UNICORN_BANNER << std::endl;
    }

    static std::wstring Trim(const std::wstring &str) {
        size_t first = str.find_first_not_of(' ');
        if (std::string::npos == first) {
            return str;
        }
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    static bool FillChamp(Graph<Tree<Champion> *> *g, std::wstring &str) {
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
            return true;
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
            std::wcout << L"No se encontró ninguna datafile llamada data.txt" << Jump;
            return;
        }
        std::wstring dataLine;
        int lines = 0;
        int successNodes = 0;
        int errorNodes = 0;
        int successChamps = 0;
        int errorChamps = 0;
        while (dataFile) {
            std::getline(dataFile, dataLine);
            if (dataLine.empty()) continue;
            if (dataLine[0] == L'\t') {
                lines++;
                if (FillChamp(g, dataLine)) {
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
        std::wcout << L"Nodos exitosos: \x1B[32m" << successNodes << L"\033[0m | Fallidos \x1B[31m" << errorNodes << L"\033[0m" << Jump;
        std::wcout << L"Campeones exitosos: " << successChamps << L" |  Fallidos \x1B[31m" << errorChamps << L"\033[0m" << Jump;
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
        auto graph = new Graph<Tree<Champion> *>();
        PrintBanner();
        FillData(graph);
        std::wcout << L"PRESS ANY KEY TO CONTINUE\r\n";
        ReadPress();
        auto *m = new MainMenu(graph);
        bool continues = true;
        while (continues) {
            Refresh();
            m->Print();
            int action = ReadPress();
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
