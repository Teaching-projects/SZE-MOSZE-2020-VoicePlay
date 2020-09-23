#include "unit.h"

//  getter fügvények
double unit::getHp () const { return hp; }
double unit::getDmg () const { return dmg; }
std::string unit::getName () const { return name; }

bool unit::isAlive () const { return (hp>0) ? true : false; }

void unit::loseHp(unit const *attacker){
        hp -= attacker->getDmg();
        if (hp<0) hp=0;
    }

void unit::parseUnit(std::string fname){
    std::ifstream f(fname);   
    std::string t;

    std::getline(f,t);
    std::getline(f,t);
    t = t.substr(t.find(": \"")+3);
    name = t.substr(0,t.size()-2);
    std::getline(f,t);
    t = t.substr(t.find(": ")+2);
    hp = std::stod(t);
    std::getline(f,t);
    t = t.substr(t.find(": ")+2);
    dmg = std::stod(t);
    f.close();
}