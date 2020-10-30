#include <map>
#include <iterator>
#include <string>
#include <fstream>
#include <vector>
#include "JSON.h"
#include <cmath>
#include "Hero.h"

double Hero::getExp() const { return exp; }
double Hero::getLevel() const { return lvl; }
double Hero::getMaxHealthPoints() const { return maxhp; }

void Hero::gainXP(unit const* u) {
    if (u->getHealthPoints() <= this->getDamage()) exp += u->getHealthPoints();
    else exp += this->getDamage();
    while (exp >= experience_per_level) {
        lvl++;
        exp = exp - experience_per_level;
        this->heal(getMaxHealthPoints()+health_point_bonus_per_level);
        this->boostDmg(getDamage()+damage_bonus_per_level);
        this->changeAcd(getAttackCoolDown()*cooldown_multiplier_per_level);
    }
}

double Hero::dealDamage(unit* const u){
    gainXP(u);
    return getDamage();
}

Hero* Hero::parse(std::string fname) {
    std::string n;
    double d,h,a;
    //double e = 0;
    //double l = 1;

    double epl, hpbpl, dbpl, cmpl;

    std::map<std::string,std::string> m;
    fname = JSONparser::rFVbQ(fname);
    try{
        m = JSONparser::fileInp(fname);
    }catch(const std::string e){
            std::cerr << e << '\n';
            std::exit( -1);
    }        
    std::map<std::string, std::string>::iterator itr;
    for (itr = m.begin(); itr != m.end(); ++itr) {
            if(itr->first == "name") n = JSONparser::rFVbQ(itr->second);
            else if(itr->first == "base_damage") d = stod(itr->second);
            else if(itr->first == "base_health_points") h = stod(itr->second);
            else if(itr->first == "base_attack_cooldown") a = stod(itr->second);
            //else if(itr->first == "exp") e = stod(itr->second);
            //else if(itr->first == "lvl") l = stod(itr->second);

            else if(itr->first == "experience_per_level") epl = stod(itr->second);
            else if(itr->first == "health_point_bonus_per_level") hpbpl = stod(itr->second);
            else if(itr->first == "damage_bonus_per_level") dbpl = stod(itr->second);
            else if(itr->first == "cooldown_multiplier_per_level") cmpl = stod(itr->second);
            else continue;
    }
    return new Hero(n, h, d, a, 0, 1, epl, hpbpl, dbpl, cmpl);
}

void ifUnitDead(unit* const attacker, unit* const defender, std::vector<unit*> &alive){
    auto it = std::find(alive.begin(), alive.end(), defender);
    if (it != alive.end()) { alive.erase(it); }
}

void Hero::fightTilDeath(Monster &m){
    std::vector<unit*> alive;
    alive.push_back(this);
    alive.push_back(&m);
    unit* attacker = alive[0]; ///< Initial attacker character
    unit* defender = alive[1]; ///< Initial defender character
    double atctime = attacker->getAttackCoolDown(); 
    double deftime = defender->getAttackCoolDown();
    
        /**
    * \brief This loop contains the first two hits.
    */
    for(int i = 0; i<2; i++){
        if (alive.size()>1 && (!(defender->battle(attacker)))){
            ifUnitDead(attacker, defender, alive);
            continue;
        }
        else{
            unit* temp = attacker;
            attacker = defender;
            defender = temp;
        }
    } 
        /**
    * \brief This loop contains the timed attacks.
    */
    while (alive.size() > 1) {
        if(!(attacker->attackOrDefend(defender, atctime, deftime))){
            attacker = alive[1];
            defender = alive[0];
        }

        if (!(defender->battle(attacker))){
            ifUnitDead(attacker, defender, alive);
            continue;
        }
        attacker = alive[0];
        defender = alive[1];
    }
}
