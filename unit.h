#pragma once

#include <string>
#include <fstream>
#include <iostream>

class unit {
private:
    const std::string name;
    double hp;
    const double  dmg; // health point, damage point
public:
    unit(std::string name, double hp, double dmg) : name(name), hp(hp), dmg(dmg) {}

    //  getter f�ggv�nyek
    double getHp() const;
    double getDmg() const;
    std::string getName() const;

    bool isAlive() const;

    virtual void loseHp(unit* attacker);
    virtual double dealDamage() { return getDmg(); }
    static unit* parseUnit(std::string fname);
};

class player : public unit {
private:
    const std::string name;
    double hp, dmg, exp, lvl; // health point, damage point, experience, level
public:
    player(std::string name, double hp, double dmg, double exp, double lvl) : unit(name, hp, dmg), exp(exp), lvl(lvl) {}

    //getter f�ggv�nyek
    double getExp() const;
    double getLvl() const;

    void gainXP(unit const* attacker);

    static player* parsePlayer(std::string fname);
    double dealDamage();
    //void loseHp(unit const* attacker); // re-def
};
