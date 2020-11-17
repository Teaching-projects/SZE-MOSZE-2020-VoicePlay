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
    double ret = u->getHealthPoints()-this->getDamage();
    gainXP(u);
    
    return ret;
}

Hero* Hero::parse(std::string fname) {
    std::string n;
    double d = -1.0;
    double h = -1.0;
    double a = -1.0;

    double epl, hpbpl, dbpl, cmpl;

    try
	{
		JSON attributes = JSON::parseFromFile(fname);
        std::cout << "parse f"<< "\neddig ok\n";
		n = attributes.get<std::string>("name");
		h = attributes.get<double>("base_health_points");
        std::cout << "get hp"<< "\neddig ok\n";
		d = attributes.get<double>("base_damage");
        std::cout << "get dmg"<< "\neddig ok\n";
		a = attributes.get<double>("base_attack_cooldown");
        epl = attributes.get<double>("experience_per_level");
        hpbpl = attributes.get<double>("health_point_bonus_per_level");
        dbpl = attributes.get<double>("damage_bonus_per_level");
        cmpl = attributes.get<double>("cooldown_multiplier_per_level");
        
	}
	catch (const std::out_of_range&)
	{
		//infile.close();
		throw(JSON::ParseException());
	}
    return new Hero(n, h, d, a, 0, 1, epl, hpbpl, dbpl, cmpl);
}

void ifUnitDead(unit* const attacker, unit* const defender, std::vector<unit*> &alive){
    auto it = std::find(alive.begin(), alive.end(), defender);
    if (it != alive.end()) { alive.erase(it); }
}

void Hero::fightTilDeath(Monster &m){

    unit* faster; ///< Initial attacker character
    unit* slower; ///< Initial defender character
    double fasterCD;
        /**
    * \brief This loop contains the first two hits.
    */
    if(getAttackCoolDown() < m.getAttackCoolDown()){
        fasterCD = getAttackCoolDown();
        faster = this;
        slower = &m;
    }else{
        fasterCD = m.getAttackCoolDown();
        faster = &m;
        slower = this;
    }
    double timer = 0.0;   
        /**
    * \brief This loop contains the timed attacks.
    */
    while (isAlive() && m.isAlive()) {
        timer +=fasterCD;
        if(slower->getAttackCoolDown()<timer){
            faster->loseHp(slower);
            if(faster->isAlive()){
                slower->loseHp(faster);
                timer -= slower->getAttackCoolDown();
            }
        }else if (slower->getAttackCoolDown() > timer){
            slower->loseHp(faster);
        }else{
            m.loseHp(this);
            if(m.isAlive()){
                this->loseHp(&m);
            }
            timer = 0.0;
        }
    }
}