/**
* \class Monster
*
* \brief Monster class
*
* This class defines the monsters, meaning the enemies of the player
*
* \author Voros Bence, Varga Mate team VoicePlay
*
* \version 1.0
*
* \date 2020/12/06 21:30
*
* Created on: 2020/12/06 21:30

*/

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
    /**
    * \brief This function parses the monster attributes from file.
    * \param fname The name of the file
    */
    static Monster parse(std::string fname){
        std::string name;

        double dmg,magic,hp,atck,dfss; ///< Attributes of the monsters
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
