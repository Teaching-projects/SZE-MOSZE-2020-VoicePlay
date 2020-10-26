#pragma once
#include "unit.h"

class player : public unit {
private:
    double exp, lvl, maxhp; //experience, level, maximum health point
    void gainXP(unit const* u);
public:
    player(std::string name, double hp, double dmg, double exp, double lvl) : unit(name, hp, dmg), exp(exp), lvl(lvl), maxhp(hp) {}

    //getter fuggvenyek
    double getExp() const;
    double getLvl() const;

    static player* parsePlayer(std::string fname);

    double dealDamage(unit* const u);
    //void loseHp(unit const* attacker); // re-def
};
