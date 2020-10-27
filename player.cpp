#include <map>
#include <iterator>
#include <string>
#include <fstream>
#include "jsonparser.h"
#include <cmath>
#include "player.h"

double player::getExp() const { return exp; }
double player::getLvl() const { return lvl; }
double player::getMaxhp() const { return maxhp; }

void player::gainXP(unit const* u) {
    if (u->getHp() <= this->getDmg()) exp += u->getHp();
    else exp += this->getDmg();
    while (exp >= 100) {
        lvl++;
        exp = exp - 100;
        this->heal(std::round(getMaxhp() * 1.1));
        this->boostDmg(std::round(getDmg() * 1.1));
        this->changeAcd(std::round(getAcd()*0.9));
    }
}

double player::dealDamage(unit* const u){
    gainXP(u);
    return getDmg();
}

player* player::parsePlayer(std::string fname) {
    std::string n;
    double d,h,a,e,l;
    std::map<std::string,std::string> m;
    try{
        m = jsonparser::fileInp(fname);
    }catch(const std::string e){
            std::cerr << e << '\n';
            std::exit( -1);
    }        
    std::map<std::string, std::string>::iterator itr;
    for (itr = m.begin(); itr != m.end(); ++itr) {
            if(itr->first == "name") n = jsonparser::rFVbQ(itr->second);
            else if(itr->first == "dmg") d = stod(itr->second);
            else if(itr->first == "hp") h = stod(itr->second);
            else if(itr->first == "acd") a = stod(itr->second);
            else if(itr->first == "exp") e = stod(itr->second);
            else if(itr->first == "lvl") l = stod(itr->second);
            else continue;
    }
    return new player(n, h, d, a, e, l);
}
