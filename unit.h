#pragma once

#include <string>
#include <fstream>
#include <iostream>

class unit {
private:
    const std::string name;
    double hp, maxhp;
    double dmg; //health point, damage point
public:
    unit(std::string name, double hp, double dmg) : name(name), hp(hp), dmg(dmg), maxhp(hp) {}

    //getter fuggvenyek
    double getHp() const;
    double getDmg() const;
    double getMaxhp() const;
    std::string getName() const;

    bool isAlive() const;

    virtual void loseHp(unit* attacker);
    virtual double dealDamage() { return getDmg(); }

    static unit* parseUnit(std::string fname);

    void heal(double d) {
        hp = d;
        maxhp = d;
    }     //heal unit to d hp
    void boostDmg(double d) { dmg = d; } //boost damage to d
};
