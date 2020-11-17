#pragma once

#include "unit.h"
#include "Monster.h"

class Hero : public unit {
private:
    double exp, lvl, maxhp; //experience, level, maximum health point

    void gainXP(unit const* u);
    void heal(double d) {   //heal unit to d hp
        hp = d;
        maxhp = d;
    }     
    void boostDmg(double d) { dmg = d; } //boost damage to d
    void changeAcd(double d) { attackcooldown=d;}
public:
    double experience_per_level, health_point_bonus_per_level, damage_bonus_per_level, cooldown_multiplier_per_level;

    Hero(std::string name, double hp, double dmg, double a, double exp, double lvl, double experience_per_level, double health_point_bonus_per_level, double damage_bonus_per_level, double cooldown_multiplier_per_level) 
                : unit(name, hp, dmg, a), exp(exp), lvl(lvl), maxhp(hp), experience_per_level(experience_per_level), 
                    health_point_bonus_per_level(health_point_bonus_per_level), 
                    damage_bonus_per_level(damage_bonus_per_level), cooldown_multiplier_per_level(cooldown_multiplier_per_level) {}
    Hero(Hero* l): unit(l->getName(),l->getHealthPoints(),l->getDamage(),
                        l->getAttackCoolDown()), exp(l->getExp()), lvl(l->getLevel()), maxhp(l->getMaxHealthPoints()), experience_per_level(l->experience_per_level), 
                    health_point_bonus_per_level(l->health_point_bonus_per_level), 
                    damage_bonus_per_level(l->damage_bonus_per_level), cooldown_multiplier_per_level(l->cooldown_multiplier_per_level){
                        //delete l;
                    }
    //getter fuggvenyek
    double getExp() const;
    double getLevel() const;
    double getMaxHealthPoints() const;

    static Hero* parse(std::string fname);

    double dealDamage(unit* const u);
    void fightTilDeath(Monster &m);
};
