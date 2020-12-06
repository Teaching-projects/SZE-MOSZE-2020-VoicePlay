#pragma once

#include "unit.h"
#include "Monster.h"
#include "Hero.h"

#include <map>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>
#include <exception>


struct posit{
    int x;
    int y;
    bool operator==(const posit& o){
        return (x=o.x)&&(y=o.y);
    }
    posit(int& x2, int& y2){
        this->x=x2;
        this->y=y2;
    }
    posit(){}
};

class Game;

//enum type{Free, Wall, Her, Monst};

class Map{
private:
    int width, height;
    
    std::map<int, std::string> level;
    std::vector<posit> multMonster;
public:
    enum type{Free, Wall, Her, Monst};
    class WrongIndexException : std::exception{
		public:
		WrongIndexException() {}
	};
    Map(std::string filename){ // Betolt fajlbol egy terkepet
        std::ifstream f(filename);   
        std::string t;
        width = 0;
        int i=0;
        if (!f) throw filename+" file does not exist!" ;
        while (std::getline(f,t)) {
                level[i]=t;
                i++;
                if (width < t.length()) width = t.length();
        }
        height = i;
        //std::cout << width << " " << height << "\n";
        for (int i = 0; i<height; i++){
            if(level[i].length()<width){
                level[i].resize(width,' ');
            }
            //std::cout << level[i] << "\n";
        }
    }
    Map(){}
    Map::type get(int x, int y) const;
    void put(int x, int y, char c);
    int getHeight(){return height;}
    int getWidth(){return width;}
    bool multMonsterPresent(int x, int y){ return (std::find(multMonster.begin(), multMonster.end(), posit(x,y)) != multMonster.end()); }
};


class Game{
private:
    Map level;
    Hero* her = nullptr;
    posit hero_pos;
    std::map<Monster*, posit> monster_list;
    bool runing = false;
    bool can_be_run = false;
    bool level_given = false;
    void write_out(){


        double left, right, top, bottom;
        if(her->getLightRadius() <= hero_pos.x) left = hero_pos.x - her->getLightRadius();
        else left = 0;
        if(her->getLightRadius() < (level.getWidth() - hero_pos.x)) right = hero_pos.x + her->getLightRadius() + 1;
        else right = level.getWidth();
        if(her->getLightRadius() <= hero_pos.y) top = hero_pos.y - her->getLightRadius();
        else top = 0;
        if(her->getLightRadius() < (level.getHeight() - hero_pos.y)) bottom = hero_pos.y + her->getLightRadius()+1;
        else bottom = level.getHeight();
        

        std::cout << "\n╔═";
        for(int i=left+1; i<right; i++) //border 
            std::cout << "══";
        std::cout << "═╗\n";
        for(int j=top; j<bottom; j++){
            std::cout << "║";
            for(int i=left; i<right; i++){
                //std::cout << "\n[" <<i<<","<<j<<"]\n";
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
                    if(level.multMonsterPresent(i,j))
                        std::cout << "MM";
                    else
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
        for(int i=left+1; i<right; i++) //border
            std::cout << "══";
        std::cout << "═╝\n";
    }

    void moveHero(int xc, int yc){
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
                    delete i->first;
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
    Game(){};
    Game(std::string mapfilename) { // Game with the Map initialized
        level = Map(mapfilename);
        level_given = true;
    }
    ~Game() {
        if(her!=nullptr)
            delete her;
        if(!monster_list.empty()){
            for (auto it = monster_list.begin(); it != monster_list.end(); ++it){
                delete it->first;
            }
        }
    }
    void setMap(Map map){ // Set the map
        if (her!=nullptr && monster_list.empty()) throw Game::AlreadyHasUnitsException();
        level = map;
        level_given = true;
    }
    void putHero(Hero hero, int x, int y){
        if (!level_given) throw Map::WrongIndexException();
        if (her!=nullptr) throw Game::AlreadyHasHeroException();
        if (runing) throw Game::GameAlreadyStartedException();
        her = new Hero(hero);
        hero_pos = posit(x,y);
        level.put(x,y,'H');
        can_be_run = true;
    }
    void putMonster(Monster monster, int x, int y) {
        if (!level_given) throw Map::WrongIndexException();
        if (runing) throw Game::GameAlreadyStartedException();
        level.put(x,y,'M');
        monster_list.insert(std::pair<Monster*,posit>(new Monster(monster),posit(x,y)));
    }

    void run(){
        if(runing==true) ;
        if(!level_given || her == nullptr) throw Game::NotInitializedException();
        write_out();
        while(!(monster_list.empty())){
            if(!(her->isAlive())){
                level.put(hero_pos.x,hero_pos.y,'M');
                write_out();
                std::cout << "The hero died.\n";
                can_be_run = false;
                break;
            }
            std::cout << "Command: ";
            std::string s;
            std::cin >> s;
            if ((s == "north") && (hero_pos.y > 0)) 
                moveHero(0,-1);
            else if ((s == "east") && (hero_pos.x < level.getWidth()-1))
                moveHero(1,0);
            else if ((s == "south") && (hero_pos.y < level.getHeight()-1))
                moveHero(0,1);
            else if ((s == "west") && (hero_pos.x > 0))
                moveHero(-1,0);
            if(her->isAlive()) write_out();
        }
        if (her->isAlive()) std::cout << her->getName() <<" cleared the map.\n";
        else {
            delete her;
            her = nullptr;
            }
    }

    class OccupiedException : std::exception{
		public:
		OccupiedException() {}
	};
    class AlreadyHasHeroException : std::exception{
		public:
		AlreadyHasHeroException() {}
	};
    class AlreadyHasUnitsException : std::exception{
		public:
		AlreadyHasUnitsException() {}
	};
    class NotInitializedException : std::exception{
		public:
		NotInitializedException() {}
	};
    class GameAlreadyStartedException : std::exception{
		public:
		GameAlreadyStartedException() {}
	};
};


Map::type Map::get(int x, int y) const{
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


void Map::put(int x, int y, char c){
        if (level.at(y)[x] == '#') 
            throw Game::OccupiedException()   ;
        else if(level.at(y)[x] == 'M' && c =='M'){
            if(std::find(multMonster.begin(), multMonster.end(), posit(x,y)) == multMonster.end())
                multMonster.push_back(posit(x,y));
        }
        else
            level.at(y)[x] = c;
    }