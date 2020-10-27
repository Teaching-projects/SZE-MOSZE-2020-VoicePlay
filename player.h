#pragma once
#include "unit.h"

class player : public unit {
private:
    double exp, lvl, maxhp; //experience, level, maximum health point
    void gainXP(unit const* u);
    void heal(double d) {   //heal unit to d hp
        hp = d;
        maxhp = d;
    }     
    void boostDmg(double d) { dmg = d; } //boost damage to d
    void changeAcd(double d) { attackcooldown=d;}
public:
    player(std::string name, double hp, double dmg, double a, double exp, double lvl) : unit(name, hp, dmg, a), exp(exp), lvl(lvl), maxhp(hp) {}

    //getter fuggvenyek
    double getExp() const;
    double getLvl() const;
    double getMaxhp() const;

    static player* parsePlayer(std::string fname);

    double dealDamage(unit* const u);
};
