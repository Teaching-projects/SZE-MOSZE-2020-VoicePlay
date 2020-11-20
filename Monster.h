#pragma once

#include "unit.h"

class Monster : public unit {
private:
public:
    Monster(std::string name, double hp, double dmg, double acd, double dfs): unit(name,hp,dmg,acd,dfs) {}
    static Monster parse(std::string fname){
        std::string n;
        double d,h,a,dfs;
        try
        {
            JSON attributes = JSON::parseFromFile(fname);
            n = attributes.get<std::string>("name");
            h = attributes.get<double>("health_points");
            d = attributes.get<double>("damage");
            a = attributes.get<double>("attack_cooldown");
            dfs = attributes.get<double>("defense");
        }
        catch (const std::out_of_range&)
        {
            //infile.close();
            throw(JSON::ParseException());
        }
        return Monster(n, h, d, a, dfs);
    }
};
