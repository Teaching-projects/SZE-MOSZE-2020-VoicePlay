#pragma once

#include "unit.h"
#include "Monster.h"

class Hero : public unit {
private:
    double exp, lvl, maxhp; //experience, level, maximum health point
    double defense_bonus_per_level,magical_damage_bonus_per_level;
    double light_radius;
    void gainXP(unit const* u);
    void heal(double d) {   //heal unit to d hp
        hp = d;
        maxhp = d;
    }     
    void boostDmg(double d, double m) { dmg.physical = d; dmg.magical = m; } //boost damage to d
    void changeAcd(double d) { attackcooldown=d;}
    void boostDefense(double d) { defense = d;}
public:
    double experience_per_level, health_point_bonus_per_level, damage_bonus_per_level, cooldown_multiplier_per_level;

    Hero(std::string name, double hp, Damage dmg, double a, double exp, double lvl, double experience_per_level, double health_point_bonus_per_level, 
        double damage_bonus_per_level, double cooldown_multiplier_per_level, double dfs, double dfsbl, double mbpl, double lr) 
                : unit(name, hp, dmg, a, dfs), exp(exp), lvl(lvl), maxhp(hp), experience_per_level(experience_per_level), 
                    health_point_bonus_per_level(health_point_bonus_per_level), 
                    damage_bonus_per_level(damage_bonus_per_level), cooldown_multiplier_per_level(cooldown_multiplier_per_level),
                    defense_bonus_per_level(dfsbl), magical_damage_bonus_per_level(mbpl),  light_radius(lr) {}
    Hero(Hero* l): unit(l->getName(),l->getHealthPoints(),Damage(l->getPDamage(),l->getMDamage()),
                        l->getAttackCoolDown(), l->getDefense()), exp(l->getExp()), lvl(l->getLevel()), maxhp(l->getMaxHealthPoints()), experience_per_level(l->experience_per_level), 
                    health_point_bonus_per_level(l->health_point_bonus_per_level), 
                    damage_bonus_per_level(l->damage_bonus_per_level), cooldown_multiplier_per_level(l->cooldown_multiplier_per_level), 
                    defense_bonus_per_level(l->defense_bonus_per_level), magical_damage_bonus_per_level(l->magical_damage_bonus_per_level),
                    light_radius(l->getLightRadius()) {
                        delete l;
                    }

    //getter functions
    double getExp() const;
    double getLevel() const;
    double getMaxHealthPoints() const;
    double getDefenseBonus() const;
    int getLightRadius() const;

    static Hero* parse(std::string fname);

    double dealDamage(unit* const u);
    void fightTilDeath(Monster &m);
};
