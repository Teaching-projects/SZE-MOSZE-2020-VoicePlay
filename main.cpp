#include <iostream>
#include <vector>
#include <algorithm>    
#include "unit.h"

using namespace std;

bool battle(unit* const u1, unit* u2){ 
    u2->loseHp(u1);
    return (u2->isAlive()) ? true : false; // if defender is dead, return false
}

int main(int argc, char *argv[]){

    vector<unit*> alive;
    vector<unit*> dead;
try
{
    alive.push_back(unit::parseUnit(argv[1]));
    alive.push_back(unit::parseUnit(argv[2]));
}
catch(const string e)
{
    std::cerr << e << '\n';
    for (auto a: alive) delete a;
    for (auto d: dead) delete d;
    return -1;
}

    unit* attacker = alive[0];
    unit* defender = alive[1];
    while (alive.size() > 1) {
        if (!(battle(attacker,defender))){
            cout << attacker->getName() << " wins. Remaining HP: " << attacker->getHp() << endl;
            //deleting defender var caused segmentation fault, instead alive's size is being reduced by one and defender is being added to the "dead" vector
			dead.push_back(defender);
			//alive.resize(alive.size()-1);
            auto it = std::find(alive.begin(), alive.end(), defender);
            if (it != alive.end()) { alive.erase(it); }
            continue;
        }
        unit* temp = attacker;
        attacker = defender;
        defender = temp;
    }
    for (auto a: alive) delete a;
    for (auto d: dead) delete d;
}
