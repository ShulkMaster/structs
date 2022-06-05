#ifndef REDEMPTION_CHAMPION_H
#define REDEMPTION_CHAMPION_H

#include "string"
#include <ctime>

class Champion {
public:
    std::wstring name;
    int age;
    std::wstring className;
    std::tm release;

    std::wstring ToDate() {
        return std::to_wstring(release.tm_mday).append(release.tm_mon, 1);
    }

    bool operator<(const Champion &champ) const {
        return name < champ.name;
    }

    bool operator<(const Champion* champ) const {
        return name < champ->name;
    }
};

#endif //REDEMPTION_CHAMPION_H
