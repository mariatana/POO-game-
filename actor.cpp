#include "Actor.h"
#include "Camera.h"
#include <iostream>
#include <vector>
using namespace std;

Actor:: Actor(int h):health(h){};
Actor:: ~Actor(){}
void Actor:: getStatus() const
{
    cout<<"Current health: "<<health<<endl;
}
int Actor::getHealth() const {
    return health;
}

void Actor::setHealth(int h) {
    health = h;
}
void Actor::scadeViata(int dmg) {
    health -= dmg;
    if (health < 0) health = 0;
}


