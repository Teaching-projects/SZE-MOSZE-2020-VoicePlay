#pragma once

#include <string>
#include <fstream>
#include <iostream>

class unit {
private:
    std::string name;
    double hp;  
    double  dmg; // health point, damage point
public:
    unit(std::string fname) { parseUnit(fname);}

    //  getter fügvények
    double getHp() const;
    double getDmg() const;
    std::string getName() const ;

    bool isAlive() const;

    void loseHp(unit const *attacker);

    void parseUnit(std::string fname);
};