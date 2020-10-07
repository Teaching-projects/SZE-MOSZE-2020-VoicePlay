#include <map>
#include <iterator>
#include <string>
#include <fstream>
#include "unit.h"
#include "jsonparser.h"

//  getter fügvények
double unit::getHp () const { return hp; }
double unit::getDmg () const { return dmg; }
std::string unit::getName () const { return name; }

bool unit::isAlive () const { return (hp>0) ? true : false; }

void unit::loseHp(unit const *attacker){
        hp -= attacker->getDmg();
        if (hp<0) hp=0;
    }

unit* unit::parseUnit(std::string fname){
        std::string n;
        double d,h;
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
                else continue;
        }
        return new unit(n,h,d);
}