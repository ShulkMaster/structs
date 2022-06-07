#ifndef REDEMPTION_CHAMPION_H
#define REDEMPTION_CHAMPION_H

#include "string"
#include <ctime>

class Champion {
public:
    std::wstring name;
    int age;
    std::wstring className;

    Champion(int age, std::wstring name, std::wstring className) {
        this->className = className;
        this->name = name;
        this->age = age;
    }

    bool operator<(const Champion &champ) const {
        return name < champ.name;
    }

    bool operator<(const Champion *champ) const {
        return name < champ->name;
    }

    bool operator==(const Champion &champ) const {
        return name == champ.name;
    }

    friend std::wostream& operator<<(std::wostream& os, const Champion &champion);
};

std::wostream &operator<<(std::wostream &os, const Champion &champion) {
    os << champion.name;
    return os;
}

#endif //REDEMPTION_CHAMPION_H
