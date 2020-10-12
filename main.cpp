#include <iostream>
#include <vector>
#include <algorithm>    
#include "unit.h"

using namespace std;

void ifUnitDead(unit* const attacker, unit* const defender, vector<unit*> &alive, vector<unit*> &dead){
    cout << attacker->getName() << " wins. Remaining HP: " << attacker->getHp() << endl;
            //deleting defender var caused segmentation fault, instead alive's size is being reduced by one and defender is being added to the "dead" vector
			dead.push_back(defender);
			//alive.resize(alive.size()-1);
            auto it = std::find(alive.begin(), alive.end(), defender);
            if (it != alive.end()) { alive.erase(it); }
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
        if (alive.size()>1 && (!(defender->battle(attacker)))){
            ifUnitDead(attacker, defender, alive, dead);
            continue;
        }
        else{
            unit* temp = attacker;
            attacker = defender;
            defender = temp;
        }
    }

    while (alive.size() > 1) {
        if(!(attacker->attackOrDefend(defender, atctime, deftime))){
            attacker = alive[1];
            defender = alive[0];
        }

        if (!(defender->battle(attacker))){
            ifUnitDead(attacker, defender, alive, dead);
            continue;
        }
        attacker = alive[0];
        defender = alive[1];
    }
    for (auto a: alive) delete a;
    for (auto d: dead) delete d;
}
