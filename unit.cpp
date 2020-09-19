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