#ifndef REDEMPTION_CHAMPION_H
#define REDEMPTION_CHAMPION_H

#include "string"
#include <ctime>

class Champion {
    std::wstring name;
    short age;
    std::wstring className;
    std::tm release;

    std::wstring ToDate() {
        return std::to_wstring(release.tm_mday).append(release.tm_mon, 1);
    }
};

#endif //REDEMPTION_CHAMPION_H
