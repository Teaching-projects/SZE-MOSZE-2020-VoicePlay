#include <iostream>
#include <vector>
#include "unit.h"

using namespace std;

bool battle(unit* const u1, unit* u2){ 
    u2->loseHp(u1);
    return (u2->isAlive()) ? true : false; // if defender is dead, return false
}

void output(unit* const atk) {
	ofstream output;
	output.open("output.txt");
	output << atk->getName() << " " << atk->getHp() << endl;
	output.close();
}

bool fileExists(string fname) {
    ifstream f(fname);
    if (f.fail()) {
        cout << fname << " does not exist!" << endl;
        return false;
	}
    return true;
}

int main(int argc, char *argv[]){

    if (!(fileExists(argv[1]) && fileExists(argv[1]))) {
        return 0;
    }

    vector<unit*> alive;
    vector<unit*> dead;

    alive.push_back(new unit(argv[1]));
    alive.push_back(new unit(argv[2]));

    unit* attacker = alive[0];
    unit* defender = alive[1];
    while (alive.size() > 1) {	
        if (!(battle(attacker,defender))){
			cout << attacker->getName() << " wins. Remaining HP: " << attacker->getHp() << endl;
			output(attacker);
			dead.push_back(defender);
            alive.resize(alive.size()-1); 
            //deleting defender var caused segmentation fault, instead alive's size is being reduced by one and defender is being added to the "dead" vector
            continue;
        }
        unit* temp = attacker;
        attacker = defender;
        defender = temp;
    }
    for (auto a: alive) delete a;
    for (auto d: dead) delete d;

    return 0;
}
