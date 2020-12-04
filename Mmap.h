#pragma once

#include "unit.h"
#include "Monster.h"
#include "Hero.h"
#include "map.h"
#include "JSON.h"

#include <map>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>
#include <exception>

class MarkedMap: public Map{
private:
    posit hero_pos;
    std::map<char,posit> mon_pos;
public:
    MarkedMap(){}
    MarkedMap(std::string fname) {
        std::ifstream f(fname);   
        std::string t;
        width = 0;
        int i=0;
        if (!f) throw fname+" file does not exist!" ;
        while (std::getline(f,t)) {
                for(int j=0; j<t.length(); j++){
                    if(isdigit(t[j])){
                        mon_pos.insert(std::pair<char,posit>(t[j],posit(j,i)));
                        t[j] = ' ';
                    }else if (t[j] == 'H'){   
                        hero_pos = posit(j,i);
                        t[j] = ' ';
                    }
                }
                level[i]=t;
                i++;
                if (width < t.length()) width = t.length();
        }
        height = i;
        for (int i = 0; i<height; i++){
            if(level[i].length()<width){
                level[i].resize(width,' ');
            }
        }
    }
    posit getHeroPosition() const{
        return hero_pos;
    }
    std::list<posit> getMonsterPositions(char c) const{
        std::list<posit> ret;
        for(auto v: mon_pos){
            if(v.first == c){
                ret.push_back(v.second);
            }
        }
        return ret;
    }
    void put(int x, int y, char c){
        if (level.at(y)[x] == '#') 
            throw Game::OccupiedException()   ;
        else
            level.at(y)[x] = c;
    }
    Map::type get(int x, int y) const{
        char t = level.at(y)[x];
        switch (t) {
        case ' ':
            return Free;
            break;
        case '#':
            return Wall;
            break;
        case 'M':
            return Monst;
            break;
        case 'H':
            return Her;
            break;
        default:         //if not any of the above
            throw Map::WrongIndexException();
            break;
        }
    }
};


class PreparedGame: public Game{
private:
    MarkedMap level;

    void initHero(std::string fname){
        posit pos = level.getHeroPosition();

        if (!level_given) throw Map::WrongIndexException();
        if (her!=nullptr) throw Game::AlreadyHasHeroException();
        if (runing) throw Game::GameAlreadyStartedException();

        her = new Hero(Hero::parse(fname));
        hero_pos = posit(pos.x,pos.y);
        level.put(hero_pos.x,hero_pos.y,'H');
        can_be_run = true;
    }
    void initMonsters(std::string fname, char c){
        if (!level_given) throw Map::WrongIndexException();
        if (runing) throw Game::GameAlreadyStartedException();
        std::list<posit> pos = level.getMonsterPositions(c);
        for(auto v: pos){
            level.put(v.x,v.y,'M');
            monster_list.insert(std::pair<Monster*,posit>(new Monster(Monster::parse(fname)),posit(v.x,v.y)));
        }
    }

    virtual void write_out(){
        std::cout << "\n╔═";
        for(int i=1; i<level.getWidth(); i++) //first row 
            std::cout << "══";
        std::cout << "═╗\n";
        for(int j=0; j<level.getHeight(); j++){
            std::cout << "║";
            for(int i=0; i<level.getWidth(); i++){
                switch (level.get(i,j)){
                case Map::Free:
                    std::cout << "░░";
                    break;
                case Map::Wall:
                    std::cout << "██";
                    break;
                case Map::Her:
                    std::cout << "┣┫";
                    break;
                case Map::Monst:
                    std::cout << "M░";
                    break;
                default:
                    break;
                }
            }
            std::cout << "║";
            std::cout << "\n";
        }
        std::cout << "╚═";
        for(int i=1; i<level.getWidth(); i++) //first row
            std::cout << "══";
        std::cout << "═╝\n";
    }

    virtual void moveHero(int xc, int yc){
        int xx = hero_pos.x+xc;
        int yy = hero_pos.y+yc;
        if(level.get(xx,yy) != Map::Wall && 0<=xx && xx<=level.getWidth() && 0<=yy && yy<=level.getHeight()){
            level.put(hero_pos.x,hero_pos.y,' ');
            hero_pos.x = xx;
            hero_pos.y = yy;
            level.put(hero_pos.x,hero_pos.y,'H');
        }
        for (auto i = monster_list.cbegin(); i != monster_list.cend(); ) {
            if (i->second.x == hero_pos.x && i->second.y == hero_pos.y){
                her->fightTilDeath(*i->first);
                if (!i->first->isAlive()){
                    std::cout << i->first->getName() <<" monster died\n";
                    monster_list.erase(i++);
                }else{
                    ++i;
                }
            }else{
                    ++i;
                }   
        }
    }



public:
    PreparedGame(std::string fname){
        try{
            JSON attributes = JSON::parseFromFile(fname);
            level = MarkedMap(attributes.get<std::string>("map"));
            level_given = true;
            std::string her_file = attributes.get<std::string>("hero");
            std::string mon1 = attributes.get<std::string>("monster-1");
            std::string mon2 = attributes.get<std::string>("monster-2");
            std::string mon3 = attributes.get<std::string>("monster-3");
            
            initHero(her_file);
            initMonsters(mon1, '1');
            initMonsters(mon2, '2');
            initMonsters(mon3, '3');
        }catch (const std::out_of_range&){
            throw(JSON::ParseException());
        } 
    }
};
