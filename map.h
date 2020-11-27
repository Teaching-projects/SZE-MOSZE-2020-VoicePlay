#pragma once

#include "unit.h"
#include "Monster.h"
#include "Hero.h"

#include <map>
#include <vector>
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
    Hero* her;
    posit hero_pos;
    std::map<Monster*, posit> monster_list;
    bool runing = false;
    bool can_be_run = false;
    bool level_given = false;
    void write_out(){
        std::cout << "╔ ";
        for(int i=1; i<level.getWidth(); i++) //first row 
            std::cout << "═";
        std::cout << "╗\n";
        for(int j=0; j<=level.getHeight(); j++){
            std::cout << "║";
            for(int i=0; i<=level.getWidth(); i++){
                switch (level.get(j,i)){
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
        std::cout << "╚";
        for(int i=1; i<level.getWidth(); i++) //first row
            std::cout << "═";
        std::cout << "╝\n";
    }

    void moveHero(int xc, int yc){
        int xx = hero_pos.x+xc;
        int yy = hero_pos.y+yc;
        if(level.get(xx,yy) != Map::Wall && 0<=xx<=level.getWidth() && 0<=yy<=level.getHeight()){
            level.put(hero_pos.x,hero_pos.y,' ');
            hero_pos.x == xx;
            hero_pos.y == yy;
            level.put(hero_pos.x,hero_pos.y,'H');
        }
    }
public:
    Game(){};
    Game(std::string mapfilename) { // Game with the Map initialized
        level = Map(mapfilename);
        level_given = true;
    }
    void setMap(Map map){ // Set the map
        if (her!=nullptr && monster_list.empty()) Game::AlreadyHasUnitsException();
        level = map;
        level_given = true;
    }
    void putHero(Hero hero, int x, int y){
        if (!level_given) Map::WrongIndexException();
        if (her!=nullptr) Game::AlreadyHasHeroException();
        if (runing) Game::GameAlreadyStartedException();
        her = &hero;
        hero_pos = posit(x,y);
        level.put(x,y,'H');
        can_be_run = true;
    }
    void putMonster(Monster monster, int x, int y) {
        if (!level_given) Map::WrongIndexException();
        if (runing) Game::GameAlreadyStartedException();
        level.put(x,y,'M');
        monster_list.insert(std::pair<Monster*,posit>(&monster,posit(x,y)));
    }

    void run(){
        if(runing==true) ;
        if(!level_given || her == nullptr) Game::NotInitializedException();

        std::map<Monster*, posit> m_list = monster_list;
        while(!(m_list.empty())){
            write_out();
            if(!(her->isAlive())){
                std::cout << "The hero died.\n";
                can_be_run = false;
                break;
            }
            std::string s;
            std::cin >> s;
            if (s == "north")
                moveHero(0,1);
            else if (s == "east")
                moveHero(1,0);
            else if (s == "south")
                moveHero(0,-1);
            else if (s == "west")
                moveHero(-1,0);
        }
        if (her->isAlive()) std::cout << her->getName() <<" cleared the map.\n";
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
    /*class NotInitializedException : std::exception{
		public:
		NotInitializedException() {}
	};*/
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
        default:
            break;
        }
        //if not any of the above
        Map::WrongIndexException();
        return Wall; // needed not to get warning
    }


void Map::put(int x, int y, char c){
        if (level.at(y)[x] == '#') 
            Game::OccupiedException()   ;
        else if(level.at(y)[x] == 'M' && c =='M'){
            //level.at(y)[x] = 'M';
            if(std::find(multMonster.begin(), multMonster.end(), posit(x,y)) == multMonster.end())
                multMonster.push_back(posit(x,y));
        }
        else
            level.at(y)[x] = c;
    }