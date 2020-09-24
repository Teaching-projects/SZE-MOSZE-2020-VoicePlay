#include "unit.h"

//  getter fügvények
double unit::getHp () const { return hp; }
double unit::getDmg () const { return dmg; }
std::string unit::getName () const { return name; }

bool unit::isAlive () const { return (hp>0) ? true : false; }

void unit::loseHp(unit const *attacker){
        hp -= attacker->getDmg();
        if (hp<0) hp=0;
    }

void unit::parseUnit(std::string fname){
        std::ifstream f(fname);   
        std::string t;
        if (!f) throw fname+" file does not exist!" ;
        std::getline(f,t);  //skip first line
        
        std::getline(f,t);  //read name line
        t = t.substr(t.find(": \"")+3); //trim string
        name = t.substr(0,t.size()-2);  //further trim string and make name equal

        std::getline(f,t);  //read hp line
        t = t.substr(t.find(": ")+2);
        hp = std::stod(t);

        std::getline(f,t);  //read dmg line
        t = t.substr(t.find(": ")+2);
        dmg = std::stod(t);

        f.close();  
}