/**
* \class player
*
* \brief player class
*
* This class contains the first fighting unit, the Player.
*
* \author Varga Mate, team VoicePlay
*
* \version 1.0
*
* \date 2020/10/27 21:20
*
* Created on: 2020/10/27 21:20

*/

#pragma once
#include "unit.h"

class player : public unit {
private:
    double exp, lvl, maxhp; ///< experience, level, maximum health point of the player
    void gainXP(unit const* u); ///< private method that gives the player experience points, increases hp and dmg and reduces attack cooldown if necessary
    /**
    * \brief This function restores the player's hp.
    */
    void heal(double d) {
        hp = d;
        maxhp = d;
    }     
    void boostDmg(double d) { dmg = d; } ///< private method that increases player's damage when called
    void changeAcd(double d) { attackcooldown=d;} ///< private method that decreases player's cooldown time when called
public:
    player(std::string name, double hp, double dmg, double a, double exp, double lvl) : unit(name, hp, dmg, a), exp(exp), lvl(lvl), maxhp(hp) {}

    /**
    * \brief This is a simple getter function for current experience points.
    * \return The player's XP
    */
    double getExp() const;
    /**
    * \brief This is a simple getter function for current level.
    * \return The player's level
    */
    double getLvl() const;
    /**
    * \brief This is a simple getter function for maximum health points.
    * \return The player's maximum health
    */
    double getMaxhp() const;

    /**
    * \brief This method reads the player's parameters from the json files.
    * \param fname The name of the file
    */
    static player* parsePlayer(std::string fname);

    /**
    * \brief This method calls gainXP() method when player hits the other unit, then returns the damage
    * \param u The attacked unit
    * \return The value of the getDmg() getter function
    */
    double dealDamage(unit* const u);
};
