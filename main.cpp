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




const std::map<int,std::string> error_messages = {
    { 1 , "Bad number of arguments. Only a single scenario file should be provided." },
    { 2 , "The provided scenario file is not accessible." },
    { 3 , "The provided scenario file is invalid." },
    { 4 , "JSON parsing error." }
};


void bad_exit(int exitcode){
    std::cerr 
        << (error_messages.count(exitcode) ? error_messages[exitcode] : "Unknown error")
        << std::endl;
    exit(exitcode);
}

int main(int argc, char** argv){
    if (argc != 2) bad_exit(1);
    if (!std::filesystem::exists(argv[1])) bad_exit(2);

    std::string hero_file;
    std::list<std::string> monster_files;
    try {
        auto scenario = JSON::parseFromFile(argv[1]);
        if (!(scenario.count("hero")&&scenario.count("monsters"))) bad_exit(3)
        else {
            hero_file=scenario["hero"];
            std::istringstream monsters(scenario["monsters"]);
            std::copy(istream_iterator<string>(monsters),
                istream_iterator<string>(),
                back_inserter(monster_files));
        }
    } catch (const JSON::ParseException& e) bad_exit(4);

    try {
        Hero hero{Hero::parse(hero_file)};
        std::list<Monster> monsters;
        for (const auto& monster_file : monster_files)
            monsters.push_back(Monster::parse(monster_file));        

        while (hero.isAlive() && !monsters.empty()) {
            std::cout 
                << hero.getName() << "(" << hero.getLevel()<<") "<<hero.getHealthPoints()
                << " vs "
                << monsters.front().getName()
                <<std::endl;
            hero.fightTilDeath(monsters.front());
            if (!monsters.front().isAlive()) monsters.pop_front();
        }
        std::cout << hero.isAlive() ? "The hero won." : "The hero died." << std::endl;
    } catch (const JSON::ParseException& e) bad_exit(4);
    return 0;
}
