#pragma once

#include "unit.h"
#include "Monster.h"
#include "Hero.h"

#include <map>
#include <fstream>
#include <exception>


struct posit{
    int x;
    int y;

    bool operator=(const posit& o){
        return (x=o.x)&&(y=o.y);
    }
};

class Map{
private:
    enum type{Free, Wall, Her, Monst};

    std::map<int, std::string> level;
public:
    class WrongIndexException : std::exception{
		public:
		WrongIndexException() {}
	};
    Map(std::string filename){ // Betolt fajlbol egy terkepet
        std::ifstream f(filename);   
        std::string t;
        int i=0;
        if (!f) throw filename+" file does not exist!" ;
        while (std::getline(f,t)) {
                level[i]=t;
                i++;
        }
    }
    Map::type get(int x, int y) const{
        char t = level.at(y)[x];
        switch (t) {
        case ' ':
            type r = Free;
            break;
        case '#':
            type r = Wall;
            break;
        default:
            Map::WrongIndexException;
            break;
        }
    }
};