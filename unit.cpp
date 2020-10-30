#include <map>
#include <iterator>
#include <string>
#include <fstream>
#include "unit.h"
#include "JSON.h"

//  getter fügvények
double unit::getHealthPoints () const { return hp; }
double unit::getDamage () const { return dmg; }
double unit::getAttackCoolDown () const { return attackcooldown; }
std::string unit::getName () const { return name; }
bool unit::isAlive() const { return hp>0 ? true : false;}

void unit::loseHp(unit *attacker) {
    hp -= attacker->dealDamage(this);
    if (hp <= 0) hp = 0;   // hp cant be < 0 
}

bool unit::battle(unit *u1){
    this->loseHp(u1);
    //loseHp(u1);
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
        double d,h,a;
        std::map<std::string,std::string> m;
        try{
            m = JSONparser::fileInp(fname);
        }catch(const std::string e){
                std::cerr << e << '\n';
                std::exit( -1);
        }        
        std::map<std::string, std::string>::iterator itr;
        for (itr = m.begin(); itr != m.end(); ++itr) {
                if(itr->first == "name") n = JSONparser::rFVbQ(itr->second);
                else if(itr->first == "dmg") d = stod(itr->second);
                else if(itr->first == "hp") h = stod(itr->second);
                else if(itr->first == "acd") a = stod(itr->second);
                else continue;
        }
        return new unit(n,h,d,a);
}
