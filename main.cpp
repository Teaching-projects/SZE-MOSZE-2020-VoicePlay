#include <iostream>
#include <vector>
#include <algorithm>    
#include <map>
#include "unit.h"
#include "jsonparser.h"
#include "player.h"

using namespace std;

/**
* \brief This function puts dead characters in dead vector.
* \param attacker the currently attacking unit
* \param defender the currently defending unit
* \param alive the vector containging living units
* \param dead the vector containing dead units
*/
void ifUnitDead(unit* const attacker, unit* const defender, vector<unit*> &alive, vector<unit*> &dead){
    cout << attacker->getName() << " wins. Remaining HP: " << attacker->getHp() << endl;
			dead.push_back(defender);
            auto it = std::find(alive.begin(), alive.end(), defender);
            if (it != alive.end()) { alive.erase(it); }
}

int main(int argc, char *argv[]){ ///< Command line arguments

    vector<unit*> alive; ///< The vector containing units with HP above 0.
    vector<unit*> dead; ///< The vector containing units with 0 HP.
    
    /**
    * \brief This block checks if the file exsists and can be read by parseUnit method. If not, it deletes the vectors.
    * \exception If file doesn't exsist or doesn't contain the necessary data
    */
    try
    {
        alive.push_back(player::parseUnit(argv[1]));
        alive.push_back(unit::parseUnit(argv[2]));
    }
    catch(const string e)
    {
        std::cerr << e << '\n';
        for (auto a: alive) delete a;
        for (auto d: dead) delete d;
        return -1;
    }

    unit* attacker = alive[0]; ///< Initial attacker character
    unit* defender = alive[1]; ///< Initial defender character

    double atctime = attacker->getAcd(); ///< Attacker's time that will be counted down to progress battle
    double deftime = defender->getAcd(); ///< Defender's time that will be counted down to progress battle
    
    /**
    * \brief This loop contains the first two hits.
    */
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

    /**
    * \brief This loop contains the timed attacks.
    */
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
    for (auto a : alive) delete a;
    for (auto d : dead) delete d;
}
