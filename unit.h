#pragma once

#include <string>
#include <fstream>
#include <iostream>

class unit {
private:
    const std::string name;
    double hp;  
    const double  dmg; // health point, damage point
    const double attackcooldown;
    void loseHp(unit const *attacker);
public:
    unit(std::string name, double hp, double dmg, double acd): name(name), hp(hp), dmg(dmg), attackcooldown(acd) {}

    //  getter fügvények
    double getHp() const;
    double getDmg() const;
    double getAcd() const;
    std::string getName() const ;

    bool attackOrDefend(unit const *attacker, double &atctime, double &deftime);

    bool battle(unit const *u1);

    static unit* parseUnit(std::string fname);
};