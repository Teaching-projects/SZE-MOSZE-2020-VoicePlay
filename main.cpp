#include <iostream>
#include <map>
#include <string>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <list>

#include "JSON.h"
#include "Hero.h"
#include "Monster.h"
#include "map.h"




const std::map<int,std::string> error_messages = {
    { 1 , "Bad number of arguments. Only a single scenario file should be provided." },
    { 2 , "The provided scenario file is not accessible." },
    { 3 , "The provided scenario file is invalid." },
    { 4 , "JSON parsing error." }
};

void bad_exit(int exitcode){
    std::cerr 
        << (error_messages.count(exitcode) ? error_messages.at(exitcode) : "Unknown error")
        << std::endl;
    exit(exitcode);
}

int main(int argc, char** argv){
    if (argc != 2) bad_exit(1);
    if (!std::filesystem::exists(argv[1])) bad_exit(2);

    std::string hero_file;
    std::list<std::string> monster_files;
    try {
        JSON scenario = JSON::parseFromFile(argv[1]); 
        if (!(scenario.count("hero")&&scenario.count("monsters"))) bad_exit(3);
        else {
            hero_file=scenario.get<std::string>("hero");
            JSON::list monster_file_list=scenario.get<JSON::list>("monsters");
            for(auto monster_file : monster_file_list){
                monster_files.push_back(std::get<std::string>(monster_file));}
        }
    } catch (const JSON::ParseException& e) {bad_exit(4);}
    try { 
        Hero hero{Hero::parse(hero_file)};
        std::list<Monster> monsters;
        for (const auto& monster_file : monster_files)
            monsters.push_back(Monster::parse(monster_file));        
        
        /*
        while (hero.isAlive() && !monsters.empty()){
            std::cout
                << hero.getName() << "(" << hero.getLevel()<<")"
                << " vs "
                << monsters.front().getName()
                <<std::endl;
            hero.fightTilDeath(monsters.front());
            if (!monsters.front().isAlive()) monsters.pop_front();
        }
        std::cout << (hero.isAlive() ? "The hero won." : "The hero died.") << std::endl;
        std::cout << hero.getName() << ": LVL" << hero.getLevel() << std::endl
                << "   HP: "<<hero.hetHealthPoints()<<"/"<<hero.getMaxHealthPoints()<<std::endl
                << "  DMG: "<<hero.getPDamage()<<std::endl
                << "  ACD: "<<hero.getAttackCoolDown()<<std::endl
                ;
        
        */

        Game game = Game("map.txt");
        game.putHero(hero, 1, 2);
        for(const auto& monster : monsters){
            game.putMonster(monster, 3, 7);

        }
        game.run();
    }
    catch (const JSON::ParseException& e) {bad_exit(4);}
    return 0;
}