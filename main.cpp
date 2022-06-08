#include <termios.h>
#include <unistd.h>
#include <iostream>
#include "App.h"

// current terminal settings
struct termios orig_termios;

// current system Locale
std::locale oldLocale;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    setlocale(LC_ALL, oldLocale.name().c_str());
}

void die(const char *s) {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
    perror(s);
    exit(1);
}

int main() {
    // setting up locale to support Unicode
    setlocale(LC_ALL, "en_US.UTF-8");
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
        die("tcgetattr");
    }
    atexit(disableRawMode);

    // entering raw mode
    struct termios raw = orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);

    // time out read bytes
    //raw.c_cc[VMIN] = 0;
    //raw.c_cc[VTIME] = 20;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    App app;
    app.Run(raw);
    return 0;
}
