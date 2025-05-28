#include "actor.h"
#include "inamic.h"
#include <iostream>
#include <cstdlib>



// Constructor: inițializează un inamic cu viață, damage minim/maxim și nume
Inamic::Inamic(int health, int min_dmg, int max_dmg, const std::string& nume)
    : Actor(health), m_min_damage(min_dmg), m_max_damage(max_dmg), m_monster_name(nume) {}


Inamic::~Inamic() {}

// Generează un damage aleator între valorile minime și maxime
int Inamic::randomPunch() const {
    return m_min_damage + rand() % (m_max_damage - m_min_damage + 1);
}

// Returnează damage-ul minim 
int Inamic::getMinimDamage() const {
    return m_min_damage;
}

// Afișează un mesaj în care inamicul lovește jucătorul
void Inamic::afiseazaLovitura() const {
    int dmg = randomPunch(); // Se calculează damage-ul generat aleator
    std::cout << m_monster_name << " te-a lovit cu " << dmg << " damage!" << '\n';
}

// Returnează o sumă de bani câștigată după ce învingi inamicul
int Inamic::randomMoney() const {
    return m_min_damage + rand() % (m_max_damage - m_min_damage + 1);
}

// Afișează viața curentă a inamicului
void Inamic::getStatus() const {
    std::cout << m_monster_name << " are " << getHealth() << " HP." << '\n';
}

// Returnează numele inamicului
std::string Inamic::getName() const {
    return m_monster_name;
}
