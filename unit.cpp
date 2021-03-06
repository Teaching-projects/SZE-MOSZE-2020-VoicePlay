#include <map>
#include <iterator>
#include <string>
#include <fstream>
#include "unit.h"
#include "JSON.h"


double unit::getHealthPoints () const { return hp; }
double unit::getPDamage () const { return dmg.physical; }
double unit::getMDamage () const { return dmg.magical; }
double unit::getAttackCoolDown () const { return attackcooldown; }
std::string unit::getName () const { return name; }
bool unit::isAlive() const { return hp>0 ? true : false;}
double unit::dealDamage(unit* const u){ 
    return (u->getHealthPoints()-this->getPDamage()+u->getDefense()-this->getMDamage()); }
void unit::loseHp(unit *attacker) {
    hp = attacker->dealDamage(this);
    if (hp <= 0) hp = 0;
}

bool unit::battle(unit *u1){
    this->loseHp(u1);
    return (getHealthPoints()>0) ? true : false;
}

bool unit::attackOrDefend(unit const *defender, double &atctime, double &deftime){
        if(atctime == deftime){
            atctime = getAttackCoolDown();
            deftime = defender->getAttackCoolDown();
            return true;
        }
        else if(atctime>deftime) {
            atctime -= deftime;
            deftime = defender->getAttackCoolDown();
            return false;
        }
        else {
            deftime -= atctime;
            atctime = getAttackCoolDown();
            return true;
        }
}

unit* unit::parseUnit(std::string fname){
        std::string n;
        double d,m,h,a,dfs;     
        try
        {
            JSON attributes = JSON::parseFromFile(fname);
            n = attributes.get<std::string>("name");
            h = attributes.get<double>("health_points");
            d = attributes.get<double>("damage");
            m = attributes.get<double>("magical-damage");
            dfs = attributes.get<double>("defense");
            a = attributes.get<double>("attack_cooldown");
        }
        catch (const std::out_of_range&)
        {
            throw(JSON::ParseException());
        }
        catch (const std::string e){
            std::cerr << e << '\n';
            std::exit( -1);
        }
        Damage dmgs;
        dmgs.physical=d;
        dmgs.magical=m;
        return new unit(n,h,dmgs,a,dfs);
}


double unit::getDefense() const {return defense;}