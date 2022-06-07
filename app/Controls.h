#ifndef REDEMPTION_CONTROLS_H
#define REDEMPTION_CONTROLS_H

#define CTRL_KEY(k) ((k) & 0x1f)
#define CONST_SIZE(A, B) (sizeof(A) / sizeof(B))

const char Seq = '\x1b';
const wchar_t *Jump = L"\r\n";

enum KeyControl {
    ENTER = 13,
    Backspace = 127,
    UpArrow = 500,
    DownArrow,
    LeftArrow,
    RightArrow,
    Delete,
    ESC,
};

const char digits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

/**
 * Contains a beautiful ASCII representation of a unicorn
 * Art by -Tua Xiong from https://www.asciiart.eu/mythology/unicorns
 */
const wchar_t *UNICORN_BANNER = L"              ,,))))))));,\r\n"
                                "            __)))))))))))))),\r\n"
                                "\\|/       -\\(((((''''((((((((.\r\n"
                                "-*-==//////((''  .     `)))))),\r\n"
                                "/|\\      ))| o    ;-.    '(((((                                  ,(,\r\n"
                                "         ( `|    /  )    ;))))'                               ,_))^;(~\r\n"
                                "            |   |   |   ,))((((_     _____------~~~-.        %,;(;(>';'~\r\n"
                                "            o_);   ;    )))(((` ~---~  `::           \\      %%~~)(v;(`('~\r\n"
                                "                  ;    ''''````         `:       `:::|\\,__,%%    );`'; ~\r\n"
                                "                 |   _  Unicorn.exe   )     /      `:|`----'     `-'\r\n"
                                "           ______/\\/~    |                 /        /\r\n"
                                "         /~;;.____/;;'  /          ___--,-(   `;;;/\r\n"
                                "        / //  _;______;'------~~~~~    /;;/\\    /\r\n"
                                "       //  | |                        / ;   \\;;,\\\r\n"
                                "      (<_  | ;                      /',/-----'  _>\r\n"
                                "       \\_| ||_                     //~;~~~~~~~~~\r\n"
                                "           `\\_|                   (,~~\r\n"
                                "                                   \\~\\\r\n"
                                "                                    ~~\r\n"
                                "             PRESS ANY KEY TO CONTINUE\r\n";

#endif //REDEMPTION_CONTROLS_H
