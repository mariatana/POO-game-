#include "Actor.h"

#include <iostream>
#include <vector>



Actor::Actor(int health) : m_health(health) {}

Actor::~Actor() {}



int Actor::getHealth() const {
    //returneaza sanatatea
    return m_health;
}

void Actor::setHealth(int health) {
    //seteaza sanatatea
    m_health = health;
}

void Actor::scadeViata(int damage) {
    //scade viata
    m_health -= damage;
    if (m_health < 0) m_health = 0;
}