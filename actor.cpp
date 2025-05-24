#include "Actor.h"
#include "Camera.h"
#include <iostream>
#include <vector>

using namespace std;

Actor::Actor(int health) : m_health(health) {}

Actor::~Actor() {}

void Actor::getStatus() const {
    cout << "Current health: " << m_health << endl;
}

int Actor::getHealth() const {
    return m_health;
}

void Actor::setHealth(int health) {
    m_health = health;
}

void Actor::scadeViata(int damage) {
    m_health -= damage;
    if (m_health < 0) m_health = 0;
}
