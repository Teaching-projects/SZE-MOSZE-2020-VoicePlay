#pragma once

#include <string>
#include <fstream>
#include <iostream>

class unit {
protected:
    const std::string name;
    double hp;
    double dmg; //health point, damage point
public:
    unit(std::string name, double hp, double dmg) : name(name), hp(hp), dmg(dmg) {}

    //getter fuggvenyek
    double getHp() const;
    double getDmg() const;
    std::string getName() const;

    bool isAlive() const;

    virtual void loseHp(unit* attacker);
    virtual double dealDamage(unit* const u) { return getDmg(); }

    static unit* parseUnit(std::string fname);


};
