#include <iostream>
#include <vector>
#include "unit.h"

using namespace std;

bool battle(unit* const u1, unit* u2){ 
    u2->loseHp(u1);
    return (u2->isAlive()) ? true : false; // if defender is dead, return false
}

bool fileExists(string fname) {
    ifstream f(fname);
    if (f.fail()) {
        cout << fname << " does not exist!" << endl;
        return false;
	}
    return true;
}

int main(){

    string unit1, unit2;
    cin >> unit1 >> unit2;
    if (!(fileExists(unit1) && fileExists(unit2))) {
        return 0;
    }

    vector<unit*> alive;

    alive.push_back(new unit(unit1));
    alive.push_back(new unit(unit2));

    unit* attacker = alive[0];
    unit* defender = alive[1];
    while ((attacker->getHp()>0) && (defender->getHp()>0)) {	
        if (!(battle(attacker,defender))){
            cout << attacker->getName() << " wins. Remaining HP: " << attacker->getHp() << endl;
			
            continue;
        }
        unit* temp = attacker;
        attacker = defender;
        defender = temp;
    }
    for (auto a: alive) delete a;

    return 0;
}
