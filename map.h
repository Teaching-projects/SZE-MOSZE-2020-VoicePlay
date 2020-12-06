/**
* \class Map
*
* \brief Map class
*
* This class reads the map of the game from a txt
*
* \author Voros Bonce, team VoicePlay
*
* \version 1.0
*
* \date 2020/12/06 19:46
*
* Created on: 2020/12/06 19:46

*/
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


class Map{
protected:
    int width, height; ///< the width and height of the map
    
    std::map<int, std::string> level; ///< the actual map
    std::vector<posit> multMonster; ///< vector that contains the monsters on the same spot of the map
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
        for (int i = 0; i<height; i++){
            if(level[i].length()<width){
                level[i].resize(width,' ');
            }
        }
    }
    Map(){}
    /**
    * \brief This function reads the characters from the map and decides its type.
    * \param x The x coordinate of a point on the map
    * \param y The y coordinate of a point on the map
    */
    Map::type get(int x, int y) const;
    /**
    * \brief This function puts the characters from the txt file to the map.
    * \param x The x coordinate of a point on the map
    * \param y The y coordinate of a point on the map
    */
    void put(int x, int y, char c);
    /**
    * \brief This is a simple getter function for the height of the map.
    * \return The height of the map
    */
    int getHeight(){return height;}
    /**
    * \brief This is a simple getter function for the width of the map.
    * \return The width of the map
    */
    int getWidth(){return width;}
    /**
    * \brief This function indicates if there are multiple monsters on the map.
    * \param x The x coordinate of a point on the map
    * \param y The y coordinate of a point on the map
    * \return The quantity of the monsters (true - >1, false - 1)
    */
    bool multMonsterPresent(int x, int y){ return (std::find(multMonster.begin(), multMonster.end(), posit(x,y)) != multMonster.end()); }
};

/**
* \class Game
*
* \brief Game class
*
* This class starts the game, coordinates the hero's movement and checks if the units are alive
*
* \author Vorös Bonce, Kovacs Kira, team VoicePlay
*
* \version 1.0
*
* \date 2020/12/06 19:57
*
* Created on: 2020/12/06 19:57

*/

class Game{
private:
    Map level; ///< The current map
protected:
    Hero* her = nullptr; ///< The current hero character
    posit hero_pos;
    std::map<Monster*, posit> monster_list;
    bool runing = false; ///< This variable tells if the game is running
    bool can_be_run = false; ///< This variable tells if the game can be run
    bool level_given = false; ///< This variable tells if the level can be started

    /**
    * \brief This function writes the map to the screen.
    */
    virtual void write_out(){
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
        for(int i=left+1; i<right; i++)
            std::cout << "══";
        std::cout << "═╗\n";
        for(int j=top; j<bottom; j++){
            std::cout << "║";
            for(int i=left; i<right; i++){
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
        for(int i=left+1; i<right; i++)
            std::cout << "══";
        std::cout << "═╝\n";
    }

    /**
    * \brief This function moves the hero from one position to another, fighting monsters if there is one.
    * \param xc The direction of vertical movement
    * \param yc The direction of horizontal movement
    */
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
    Game(std::string mapfilename) {
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
    /**
    * \brief This function sets the map.
    * \param map The current map of the game
    */
    void setMap(Map map){
        if (her!=nullptr && monster_list.empty()) throw Game::AlreadyHasUnitsException();
        level = map;
        level_given = true;
    }
     /**
    * \brief This function puts a new hero to the map.
    * \param hero The current hero
    * \param x The x coordinate of the hero
    * \param y The y coordinate of the hero
    */
    void putHero(Hero hero, int x, int y){
        if (!level_given) throw Map::WrongIndexException();
        if (her!=nullptr) throw Game::AlreadyHasHeroException();
        if (runing) throw Game::GameAlreadyStartedException();
        her = new Hero(hero);
        hero_pos = posit(x,y);
        level.put(x,y,'H');
        can_be_run = true;
    }
     /**
    * \brief This function puts a new monster to the map.
    * \param hero The current monster
    * \param x The x coordinate of the monster
    * \param y The y coordinate of the monster
    */
    void putMonster(Monster monster, int x, int y) {
        if (!level_given) throw Map::WrongIndexException();
        if (runing) throw Game::GameAlreadyStartedException();
        level.put(x,y,'M');
        monster_list.insert(std::pair<Monster*,posit>(new Monster(monster),posit(x,y)));
    }

    /**
    * \brief This function runs the game and waits for the player's moves.
    */
    virtual void run(){
        if(runing==true) ;
        if(!level_given || her == nullptr) throw Game::NotInitializedException();
        while(!(monster_list.empty())){
            if(!(her->isAlive())){
                level.put(hero_pos.x,hero_pos.y,'M');
                write_out();
                std::cout << "The hero died.\n";
                level.put(hero_pos.x,hero_pos.y,'M');
                can_be_run = false;
                break;
            }
            write_out();
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
        default:
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