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
    unit(std::string name, double hp, double dmg): name(name), hp(hp), dmg(dmg) {}

    //  getter fügvények
    double getHp() const;
    double getDmg() const;
    std::string getName() const ;

    bool isAlive() const;

    void loseHp(unit const *attacker);

    static unit* parseUnit(std::string fname);
};