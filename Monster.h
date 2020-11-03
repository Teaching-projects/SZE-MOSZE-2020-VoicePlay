#pragma once

#include "unit.h"

class Monster : public unit {
private:
public:
    Monster(std::string name, double hp, double dmg, double acd): unit(name,hp,dmg,acd) {}
    static Monster parse(std::string fname){
        std::string n;
        double d,h,a;
        /*       
        std::map<std::string, std::string>::iterator itr;
        for (itr = m.begin(); itr != m.end(); ++itr) {
                if(itr->first == "name") n = JSONparser::rFVbQ(itr->second);
                else if(itr->first == "damage") d = stod(itr->second);
                else if(itr->first == "health_points") h = stod(itr->second);
                else if(itr->first == "attack_cooldown") a = stod(itr->second);
                else continue;
        }*/
        try
        {
            JSON attributes = JSON::parseFromFile(fname);
            n = attributes.get<std::string>("name");
            h = attributes.get<double>("health_points");
            d = attributes.get<double>("damage");
            a = attributes.get<double>("attack_cooldown");
        }
        catch (const std::out_of_range&)
        {
            //infile.close();
            throw(JSON::ParseException());
        }
        return Monster(n, h, d, a);
    }
};
