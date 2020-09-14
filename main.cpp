#include <iostream>
#include <string>
#include <vector>

using namespace std;

class unit {
private:
    string name;
    double hp, dmg; // health point, damage point: a unit adatainak tárolására
public:
    unit(string name, double hp, double dmg): name(name), hp(hp), dmg(dmg) {}

    //  getter fügvények
    double getHp () { return hp; }
    double getDmg () { return dmg; }
    string getName () { return name; }

    bool isAlive () {
        if ( hp > 0 )
            return true;
        else
            return false;
    }

    void loseHp(unit *attacker){
        hp -= attacker->getDmg();
        if (hp<0) hp=0;
    }
};

void printStatus(vector<unit*> alive){
    for( auto v:  alive)
        cout << v->getName() << ": HP: " << v->getHp() << ", DMG: " << v->getDmg() << endl;
}

void printAttack(string n1, string n2){
    cout << n1 << " -> " << n2 << endl;
}

int main(int argc, char *argv[]){
    vector<unit*> alive;
    vector<unit*> dead;

    alive.push_back(new unit(argv[1],stod(argv[2]),stod(argv[3])));
    alive.push_back(new unit(argv[4],stod(argv[5]),stod(argv[6])));

    printStatus(alive);
    while(alive.size() > 1){
        printAttack(alive[0]->getName(), alive[1]->getName());
        alive[1]->loseHp(alive[0]);
        printStatus(alive);
        if (!(alive[1]->isAlive())) {
            cout << alive[1]->getName() << " died. " << alive[0]->getName() << " wins.\n";
            dead.push_back(alive[1]);
            alive.erase(alive.begin()+1);
            continue;
        }

        printAttack(alive[1]->getName(), alive[0]->getName());
        alive[0]->loseHp(alive[1]);
        printStatus(alive);
        if (!(alive[0]->isAlive())) {
            cout << alive[0]->getName() << " died. " << alive[1]->getName() << " wins.\n";
            dead.push_back(alive[0]);
            alive.erase(alive.begin());
            continue;
        
        }
    }

    for (int i = 0; i < alive.size(); i++) delete alive[i];
	for (int i = 0; i < alive.size(); i++) delete dead[i];

}
