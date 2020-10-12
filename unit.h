#pragma once

#include <string>
#include <fstream>
#include <iostream>

class unit {
private:
    const std::string name;
    double hp;  
    const double  dmg; // health point, damage point
    const double acd;
    void loseHp(unit const *attacker);
public:
    unit(std::string name, double hp, double dmg, double acd): name(name), hp(hp), dmg(dmg), acd(acd) {}

    //  getter fügvények
    double getHp() const;
    double getDmg() const;
    double getAcd() const;
    std::string getName() const ;


    bool battle(unit* u1);

    static unit* parseUnit(std::string fname);
};