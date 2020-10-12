#include "unit.h"

//  getter fügvények
double unit::getHp () const { return hp; }
double unit::getDmg () const { return dmg; }
double unit::getAcd () const { return attackcooldown; }
std::string unit::getName () const { return name; }


void unit::loseHp(unit const *attacker){
        hp -= attacker->getDmg();
        if (hp<0) hp=0;
    }

bool unit::battle(unit const *u1){
    loseHp(u1);
    return (getHp()>0) ? true : false; // if defender is dead, return false
}

bool unit::attackOrDefend(unit const *defender, double &atctime, double &deftime){
        if(atctime == deftime){ //if both timers have the same number, attacker remains attacker
            atctime = getAcd();
            deftime = defender->getAcd();
            return true;
        }
        else if(atctime>deftime) { //if defender is the faster in the round, they become attacker
            atctime -= deftime;
            deftime = defender->getAcd();
            return false;
        }
        else { //if attacker is the faster, they remain attacker
            deftime -= atctime;
            atctime = getAcd();
            return true;
        }
}

unit* unit::parseUnit(std::string fname){
        std::ifstream f(fname);   
        std::string t;
        std::string n = "";
        double h = -1;
        double d = -1;
        double a = -1;
        if (!f) throw fname+" file does not exist!" ;
        while (!f.eof()) {
                std::getline(f,t);
                if((t.find("name") != std::string::npos) && n == ""){
                        t = t.substr(t.find(": \"")+3); //trim string
                        n = t.substr(0,t.size()-2);  //further trim string and make name equal
                }else if((t.find("hp") != std::string::npos) && h == -1){
                        t = t.substr(t.find(": ")+2);
                        h = std::stod(t);
                }else if((t.find("dmg") != std::string::npos) && d == -1){
                        t = t.substr(t.find(": ")+2);
                        d = std::stod(t);
                }else if((t.find("acd") != std::string::npos) && a == -1){
                        t = t.substr(t.find(": ")+2);
                        a = std::stod(t);
                }
        }
        f.close();
        return new unit(n,h,d,a);
}