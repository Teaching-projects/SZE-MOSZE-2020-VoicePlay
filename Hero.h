/**
* \class Hero
*
* \brief Hero class
*
* This class defines the hero, meaning the player character
*
* \author Voros Bonce, Kovacs Kira, Varga Mate team VoicePlay
*
* \version 1.0
*
* \date 2020/12/06 20:48
*
* Created on: 2020/12/06 20:48

*/

#pragma once

#include "unit.h"
#include "Monster.h"

class Hero : public unit {
private:
    double exp, lvl, maxhp; ///< Experience, level and maximum health points of the hero
    double defense_bonus_per_level,magical_damage_bonus_per_level; ///< Defense and magical damage increase when leveling up
    double light_radius, light_radius_bonus_per_level; ///< Light radius that the hero sees, bonus of light radius per leveling up
    /**
    * \brief This function increases the experience of the hero.
    * \param u The enemy unit
    */
    void gainXP(unit const* u);
    /**
    * \brief This function heals the player and sets the maximum hp.
    * \param d The increased maximum hp
    */
    void heal(double d) { 
        hp = d;
        maxhp = d;
    }     
    /**
    * \brief This function increases the damage of the hero.
    * \param d the increased physical damage
    * \param m the increased magical damage
    */
    void boostDmg(double d, double m) { dmg.physical = d; dmg.magical = m; }
    /**
    * \brief This function changes the attack cooldown time of the hero.
    * \param d The changed time
    */
    void changeAcd(double d) { attackcooldown=d;}
    /**
    * \brief This function increase the defense of the hero.
    * \param d The increased defense
    */
    void boostDefense(double d) { defense = d;}
    /**
    * \brief This function increases the area the hero sees.
    * \param d The increased radius
    */
    void boostLightRadius(double d) {light_radius = d;}
public:
    double experience_per_level, health_point_bonus_per_level, damage_bonus_per_level, cooldown_multiplier_per_level; ///< The increase rate of the attributes

    Hero(std::string name, double hp, Damage dmg, double a, double exp, double lvl, double experience_per_level, double health_point_bonus_per_level, 
        double damage_bonus_per_level, double cooldown_multiplier_per_level, double dfs, double dfsbl, double mbpl, double lr, double lrbl) 
                : unit(name, hp, dmg, a, dfs), exp(exp), lvl(lvl), maxhp(hp), experience_per_level(experience_per_level), 
                    health_point_bonus_per_level(health_point_bonus_per_level), 
                    damage_bonus_per_level(damage_bonus_per_level), cooldown_multiplier_per_level(cooldown_multiplier_per_level),
                    defense_bonus_per_level(dfsbl), magical_damage_bonus_per_level(mbpl),  light_radius(lr), light_radius_bonus_per_level(lrbl) {}
    Hero(Hero* l): unit(l->getName(),l->getHealthPoints(),Damage(l->getPDamage(),l->getMDamage()),
                        l->getAttackCoolDown(), l->getDefense()), exp(l->getExp()), lvl(l->getLevel()), maxhp(l->getMaxHealthPoints()), experience_per_level(l->experience_per_level), 
                    health_point_bonus_per_level(l->health_point_bonus_per_level), 
                    damage_bonus_per_level(l->damage_bonus_per_level), cooldown_multiplier_per_level(l->cooldown_multiplier_per_level), 
                    defense_bonus_per_level(l->defense_bonus_per_level), magical_damage_bonus_per_level(l->magical_damage_bonus_per_level),
                    light_radius(l->getLightRadius()), light_radius_bonus_per_level(l->light_radius_bonus_per_level){
                        delete l;
                    }

    /**
    * \brief This is a simple getter function for the experience of the hero.
    * \return The xp points of the hero
    */
    double getExp() const;
    /**
    * \brief This is a simple getter function for the level of the hero.
    * \return The level of the hero
    */
    double getLevel() const;
    /**
    * \brief This is a simple getter function for the maximum health of the hero.
    * \return The maximum health of the hero
    */
    double getMaxHealthPoints() const;
    /**
    * \brief This is a simple getter function for defense bonus of the hero.
    * \return The defense bonus of the hero
    */
    double getDefenseBonus() const;
    /**
    * \brief This is a simple getter function for the area size the hero sees.
    * \return The light radius
    */
    int getLightRadius() const;

    /**
    * \brief This function reads the hero's attributes from the file.
    * \param fname The name of the file
    */
    static Hero* parse(std::string fname);

    /**
    * \brief This function deals damage to the enemy unit.
    * \param u The enemy unit
    */
    double dealDamage(unit* const u);
    /**
    * \brief This function makes the hero fighting until the hero or the monster is dead.
    * \param m The monster
    */
    void fightTilDeath(Monster &m);
};
