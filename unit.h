/**
* \class unit
*
* \brief unit class
*
* This class contains the second fighting unit, which fights with the player, contained by player class
*
* \author Kovacs Kira, team VoicePlay
*
* \version 1.0
*
* \date 2020/10/15 6:58
*
* Created on: 2020/10/15 6:58

*/

#pragma once

#include <string>
#include <fstream>
#include <iostream>

class unit {
protected:
    const std::string name; ///< the name of the unit
    double hp;  ///< the starting health points of the unit
    double  dmg; ///< the damage the unit deals to another character in a round
    double attackcooldown; ///< the cooldown time between the attacks of the same unit
    void loseHp(unit *attacker); ///< private method that decreases the health points of the unit by the attacker's damage
public:
    unit(std::string name, double hp, double dmg, double acd): name(name), hp(hp), dmg(dmg), attackcooldown(acd) {}

    /**
    * \brief This is a simple getter function for current health points.
    * \return The character's health points
    */
    double getHp() const;
    /**
    * \brief This is a simple getter function for damage points.
    * \return The character's damage points
    */
    double getDmg() const;
    /**
    * \brief This is a simple getter function for cooldown time.
    * \return The character's cooldown time
    */
    double getAcd() const;
    /**
    * \brief This is a simple getter function for unit's name.
    * \return The character's name
    */
    std::string getName() const ;
    /**
    * \brief This is the method that counts the leftover time of the unit after a round and decides who attacks next.
    * \param attacker the unit who first attacked
    * \param atctime the initial attacker's leftover time after last round
    * \param deftime the initial defender's leftover time after last round
    */
    bool attackOrDefend(unit const *attacker, double &atctime, double &deftime);

    //virtual void loseHp(unit* attacker);
    virtual double dealDamage(unit* const u) { return getDmg(); }
    /**
    * \brief This method decides whether the attacked character is still alive or not.
    * \param u1 the attacker unit
    * \return a bool variable, true if defender unit is alive, false if not
    */
    bool battle(unit *u1);
    /**
    * \brief This method reads the parameters from the json files
    * \param fname The name of the file
    */
    static unit* parseUnit(std::string fname);


};
