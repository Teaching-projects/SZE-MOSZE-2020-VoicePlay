#include <cmath>
#include "player.h"

double player::getExp() const { return exp; }
double player::getLvl() const { return lvl; }

void player::gainXP(unit const* u) {
    if (u->getHp() <= this->getDmg()) exp += u->getHp();
    else exp += this->getDmg();
    while (exp >= 100) {
        lvl++;
        exp = exp - 100;
        this->heal(std::round(getMaxhp() * 1.1));
        this->boostDmg(std::round(getDmg() * 1.1));
    }
}

double player::dealDamage(unit* const u){
    gainXP(u);
    return getDmg();
}

player* player::parsePlayer(std::string fname) {
    std::ifstream f(fname);
    std::string t;
    std::string n = "";
    double h = -1;
    double d = -1;
    double e = -1;
    double l = -1;
    if (!f) throw fname + " file does not exist!";
    while (!f.eof()) {
        std::getline(f, t);
        if ((t.find("name") != std::string::npos) && n == "") {
            t = t.substr(t.find(": \"") + 3); //trim string
            n = t.substr(0, t.size() - 2);  //further trim string and make name equal
        }
        else if ((t.find("hp") != std::string::npos) && h == -1) {
            t = t.substr(t.find(": ") + 2);
            h = std::stod(t);
        }
        else if ((t.find("dmg") != std::string::npos) && d == -1) {
            t = t.substr(t.find(": ") + 2);
            d = std::stod(t);
        }
        else if ((t.find("exp") != std::string::npos) && e == -1) {
            t = t.substr(t.find(": ") + 2);
            e = std::stod(t);
        }
        else if ((t.find("lvl") != std::string::npos) && l == -1) {
            t = t.substr(t.find(": ") + 2);
            l = std::stod(t);
        }
    }
    f.close();
    return new player(n, h, d, e, l);
}
