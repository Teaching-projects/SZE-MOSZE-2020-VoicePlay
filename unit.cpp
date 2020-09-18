#include "unit.h"

//  getter fügvények
const double unit::getHp () { return hp; }
const double unit::getDmg () { return dmg; }
const std::string unit::getName () { return name; }

const bool unit::isAlive () { return (hp>0) ? true : false; }

void unit::loseHp(unit *attacker){
        hp -= attacker->getDmg();
        if (hp<0) hp=0;
    }