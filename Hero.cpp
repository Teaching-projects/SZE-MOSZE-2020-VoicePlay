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
int Hero::getLightRadius() const { return light_radius; }

void Hero::gainXP(unit const* u) {
    double actualDmg = this->getPDamage()-u->getDefense()+this->getMDamage();  //the damage dealt - the defended damage
    if (actualDmg > 0){ 
        if (u->getHealthPoints() <= actualDmg) exp += u->getHealthPoints();
        else exp += actualDmg;
        while (exp >= experience_per_level) {
            lvl++;
            exp = exp - experience_per_level;
            this->heal(getMaxHealthPoints()+health_point_bonus_per_level);
            this->boostDmg(getPDamage()+damage_bonus_per_level,getMDamage()+magical_damage_bonus_per_level);
            this->changeAcd(getAttackCoolDown()*cooldown_multiplier_per_level);
            this->boostDefense(getDefense()+defense_bonus_per_level);
            this->boostLightRadius(getLightRadius()+light_radius_bonus_per_level);
        }
    }
}

double Hero::dealDamage(unit* const u){
    double ret = u->getHealthPoints()+u->getDefense()-this->getPDamage()-this->getMDamage();
    gainXP(u);
    
    return ret;
}

Hero* Hero::parse(std::string fname) {
    std::string n;
    double d = -1.0;
    double h = -1.0;
    double a = -1.0;
    double dfs,dfsbpl,m,mbpl;
    double lr,lrbl;

    double epl, hpbpl, dbpl, cmpl;

    try
	{
		JSON attributes = JSON::parseFromFile(fname);
		n = attributes.get<std::string>("name");
		h = attributes.get<double>("base_health_points");
		d = attributes.get<double>("base_damage");
		a = attributes.get<double>("base_attack_cooldown");
        epl = attributes.get<double>("experience_per_level");
        hpbpl = attributes.get<double>("health_point_bonus_per_level");
        dbpl = attributes.get<double>("damage_bonus_per_level");
        cmpl = attributes.get<double>("cooldown_multiplier_per_level");
        dfsbpl = attributes.get<double>("defense_bonus_per_level");
        dfs = attributes.get<double>("defense");
        m = attributes.get<double>("magical-damage");
        mbpl = attributes.get<double>("magical_damage_bonus_per_level");
        try{
            lrbl = attributes.get<double>("light_radius_bonus_per_level");
        }catch(const std::out_of_range&){
            lrbl=1;
        }
        lr = attributes.get<double>("light_radius");
        
	}
	catch (const std::out_of_range&)
	{
		//infile.close();
        std::cout << "Parse error hero\n";
		throw(JSON::ParseException());
	}
    Damage dmgs;
        dmgs.physical=d;
        dmgs.magical=m;
    return new Hero(n, h, dmgs, a, 0, 1, epl, hpbpl, dbpl, cmpl,dfs,dfsbpl,mbpl,lr,lrbl);
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


double Hero::getDefenseBonus() const {return defense_bonus_per_level;}