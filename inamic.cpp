#include "actor.h"
#include "inamic.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Inamic::Inamic(int health,int miD, int maD, const std::string &nume)
    : Actor(health),mindamage(miD), maxDamage(maD), monsterName(nume) {}

Inamic::~Inamic() {}

int Inamic::randomPunch() const {
    return mindamage + rand() % (maxDamage - mindamage + 1);
}
int Inamic:: getMinimDamage() const{
    return this->mindamage;
}
void Inamic::afiseazaLovitura() const {
    int dmg = randomPunch();
    cout << monsterName << " te-a lovit cu " << dmg << " damage!" << endl;
}

int Inamic::randomMoney() const {
    return mindamage + rand() % (maxDamage - mindamage + 1);
}

void Inamic::getStatus() const {
    cout << monsterName << " are " << getHealth() << " HP." << endl;
}
std::string Inamic:: getName() const{
    return monsterName;
}
