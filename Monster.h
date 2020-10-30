#pragma once

#include "unit.h"

class Monster : public unit {
private:
public:
    Monster(std::string name, double hp, double dmg, double acd): unit(name,hp,dmg,acd) {}
    static Monster parse(std::string fname){
        std::string n;
        double d,h,a;
        std::map<std::string,std::string> m;
        try{
        fname = JSONparser::rFVbQ(fname);
        }catch(const int e){
            //continue;
        }
        try{
            m = JSONparser::fileInp(fname);
        }catch(const std::string e){
                std::cerr << e << '\n';
                std::exit( -1);
        }        
        std::map<std::string, std::string>::iterator itr;
        for (itr = m.begin(); itr != m.end(); ++itr) {
                if(itr->first == "name") n = JSONparser::rFVbQ(itr->second);
                else if(itr->first == "damage") d = stod(itr->second);
                else if(itr->first == "health_points") h = stod(itr->second);
                else if(itr->first == "attack_cooldown") a = stod(itr->second);
                else continue;
        }
        return Monster(n, h, d, a);
    }
};
