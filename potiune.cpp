#include <iostream>
#include <string>
#include "Obiect.h"
#include "Potiune.h"
#include "player.h"

using namespace std;

Potiune::Potiune(int damage, int raritate, const std::string& nume, bool tip, int pret)
    : Obiect(damage, raritate, nume, pret), m_tip(tip) {}

Potiune::~Potiune() {}

Potiune::Potiune(const Potiune& other)
    : Obiect(other), m_tip(other.m_tip) {}

bool Potiune::getTip() {
    return m_tip;
}

void Potiune::foloseste() {
    cout << "f" << endl;
}

Obiect* Potiune::clone() const {
    return new Potiune(*this);
}

int Potiune::getImpactPotiune() const {
    return this->getDamage();
}
