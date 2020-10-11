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

    double atctime = attacker->getAcd();
    double deftime = defender->getAcd();
    
    for(int i = 0; i<2; i++){
        if (!(battle(attacker, defender))){
            cout << attacker->getName() << " wins. Remaining HP: " << attacker->getHp() << endl;
			dead.push_back(defender);
            auto it = std::find(alive.begin(), alive.end(), defender);
            if (it != alive.end()) { alive.erase(it); }
            continue;
        }
        
        unit* temp = attacker;
        attacker = defender;
        defender = temp;
    }

    while (alive.size() > 1) {
        if(atctime == deftime){ //if both timers have the same number, attacker remains attacker
            atctime = attacker->getAcd();
            deftime = defender->getAcd();
        }
        else if(atctime>deftime) { //if defender is the faster in the round, they become attacker
            atctime -= deftime;
            deftime = defender->getAcd();
            attacker = alive[1];
            defender = alive[0];
        }
        else { //if attacker is the faster, they remain attacker
            deftime -= atctime;
            atctime = attacker->getAcd();
        }

        if (!(battle(attacker,defender))){
            cout << attacker->getName() << " wins. Remaining HP: " << attacker->getHp() << endl;
            //deleting defender var caused segmentation fault, instead alive's size is being reduced by one and defender is being added to the "dead" vector
			dead.push_back(defender);
			//alive.resize(alive.size()-1);
            auto it = std::find(alive.begin(), alive.end(), defender);
            if (it != alive.end()) { alive.erase(it); }
            continue;
        }
        attacker = alive[0];
        defender = alive[1];
    }
    for (auto a: alive) delete a;
    for (auto d: dead) delete d;
}
