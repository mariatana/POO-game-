#include "actor.h"
#include "inamic.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Inamic::Inamic(int health, int min_dmg, int max_dmg, const std::string& nume)
    : Actor(health), m_min_damage(min_dmg), m_max_damage(max_dmg), m_monster_name(nume) {}

Inamic::~Inamic() {}

int Inamic::randomPunch() const {
    return m_min_damage + rand() % (m_max_damage - m_min_damage + 1);
}

int Inamic::getMinimDamage() const {
    return m_min_damage;
}

void Inamic::afiseazaLovitura() const {
    int dmg = randomPunch();
    cout << m_monster_name << " te-a lovit cu " << dmg << " damage!" << endl;
}

int Inamic::randomMoney() const {
    return m_min_damage + rand() % (m_max_damage - m_min_damage + 1);
}

void Inamic::getStatus() const {
    cout << m_monster_name << " are " << getHealth() << " HP." << endl;
}

std::string Inamic::getName() const {
    return m_monster_name;
}
