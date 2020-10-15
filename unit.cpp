#include "unit.h"

//  getter fegvenyek
double unit::getHp() const { return hp; }
double unit::getDmg() const { return dmg; }
std::string unit::getName() const { return name; }
double player::getExp() const { return exp; }
double player::getLvl() const { return lvl; }

bool unit::isAlive() const { return (hp > 0) ? true : false; }

void unit::loseHp(unit* attacker) {
    hp -= attacker->dealDamage();
    if (hp <= 0) hp = 0;   // hp cant be < 0 
}

void player::gainXP(unit const* attacker) {
    exp += attacker->getDmg();
    while (exp >= 100) {
        lvl++;
        exp = exp - 100;
        hp = attacker->getHp() * 1.1;
        dmg = dmg * 1.1;
    }
}

unit* unit::parseUnit(std::string fname) {
    std::ifstream f(fname);
    std::string t;
    std::string n = "";
    double h = -1;
    double d = -1;
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
    }
    f.close();
    return new unit(n, h, d);
}

/*void player::loseHp(unit const* attacker){        //gain xp when hit
    this->unit::loseHp(attacker);   //the plíer::loseHp cant acces the player hp so this call is necessary
    if (this->isAlive()) {    //if player not dead gain xp (shouldnt be needed just sanity check)
        gainXP(attacker);
    }

}
*/

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

double player::dealDamage() {
    gainXP(this);   //gain xp when dealing damage
    return getDmg();
}