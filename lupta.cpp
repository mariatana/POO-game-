// Lupta.cpp
#include "lupta.h"
#include "actor.h"
#include "player.h"
#include "Obiect.h"
#include "inamic.h"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
Lupta::Lupta(Player* p, Inamic* i) : player(p), inamic(i) {}

bool Lupta::start() {
    cout << "Lupta a inceput cu " << inamic->getName() << "!\n";
    
    while (player->getHealth() > 0 && inamic->getHealth() > 0) {
        int dmg = player->getArmaCurenta()->getDamage();
        cout << "Ai lovit cu " << dmg << " damage"<<endl;
        inamic->scadeViata(dmg);
        cout<<" Inamicul are acum " << inamic->getHealth() << " HP.\n";

        if (inamic->getHealth() > 0) {
            int dmgInamic = inamic->randomPunch();
            player->scadeViata(dmgInamic);
            cout << "Inamicul te-a lovit cu " << dmgInamic << " damage. Tu ai acum " << player->getHealth() << " HP.\n";
        }
    }

    if (player->getHealth() > 0) {
        cout <<GREEN<< "Ai castigat lupta!"<<RESET<<endl;
        Player::AdaugaMosntriBatuti();
        return true;
    } else {
        cout << "Ai fost invins in lupta...\n";
        return false;
    }
}
