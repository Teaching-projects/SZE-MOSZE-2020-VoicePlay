#pragma once

#include "Hero.h"
#include "unit.h"

class Monster : public unit {
private:
public:
    Monster(std::string name, double hp, Damage dmg, double acd, double dfs): unit(name,hp,dmg,acd,dfs) {}
    Monster(Monster* l): unit(l->getName(),l->getHealthPoints(),Damage(l->getPDamage(),l->getMDamage()),
                        l->getAttackCoolDown(), l->getDefense()) {
                        delete l;
                    }
    static Monster parse(std::string fname){
        std::string name;

        double dmg,magic,hp,atck,dfss;
        try
        {
            JSON attributes = JSON::parseFromFile(fname);
            name = attributes.get<std::string>("name");
            hp = attributes.get<double>("health_points");
            dmg = attributes.get<double>("damage");
            magic = attributes.get<double>("magical-damage");
            atck = attributes.get<double>("attack_cooldown");
            dfss = attributes.get<double>("defense");
        }
        catch (const std::out_of_range&)
        {
            throw(JSON::ParseException());
        }
        Damage dmgs;
        dmgs.physical=dmg;
        dmgs.magical=magic;
        return Monster(name, hp, dmgs, atck, dfss);
    }
};
