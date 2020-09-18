#include <iostream>
#include <vector>
#include "unit.h"

using namespace std;

void printStatus(vector<unit*> alive){
    for( auto v:  alive)
        cout << v->getName() << ": HP: " << v->getHp() << ", DMG: " << v->getDmg() << endl;
}

void printAttack(string n1, string n2){
    cout << n1 << " -> " << n2 << endl;
}

bool battle(unit* u1, unit* u2, vector<unit*> alive){ 
/// az u1 unit tamadja az u2-ot ((az alive atadasa csak az elvart kimenttel valo megegyezes miatt szukseges a kovetkezo feladattol mar nem kell))
	printAttack(u1->getName(), u2->getName());
	u2->loseHp(u1);
	printStatus(alive);
	return (u2->isAlive()) ? true : false; // ha a defender meghalt return false
}

int main(int argc, char *argv[]){
    vector<unit*> alive;
    vector<unit*> dead;

    alive.push_back(new unit(argv[1],stod(argv[2]),stod(argv[3])));
    alive.push_back(new unit(argv[4],stod(argv[5]),stod(argv[6])));

	printStatus(alive);
    unit* attacker = alive[0];
    unit* defender = alive[1];
	while (alive.size() > 1) {	/// place-holder loop, csak amig valamelyik feladat mast nem ker
        if (!(battle(attacker,defender,alive))){
			cout << defender->getName() << " died. " << attacker->getName() << " wins.\n";
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
}
