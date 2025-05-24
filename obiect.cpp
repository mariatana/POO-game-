#include "Obiect.h"
#include "inamic.h"
#include "camera.h"
#include <vector>
#include <string>

int Obiect::m_obiecte_in_inventar = 0;

Obiect::Obiect(int damage, int raritate, const std::string& nume, int pret)
    : m_damage(damage), m_raritate(raritate), m_nume(nume), m_pret(pret) {
    m_obiecte_in_inventar++;
}

Obiect::Obiect(const Obiect& other)
    : m_damage(other.m_damage), m_raritate(other.m_raritate),
      m_nume(other.m_nume), m_pret(other.m_pret) {
    m_obiecte_in_inventar++;
}

std::ostream& operator<<(std::ostream& os, const Obiect& obj) {
    os << obj.getNume() << " (Damage: " << obj.getDamage()
       << ", Raritate: " << obj.getRaritate() << ")";
    return os;
}

Obiect::~Obiect() {
    m_obiecte_in_inventar--;
}

int Obiect::getDamage() const {
    return m_damage;
}

int Obiect::getRaritate() const {
    return m_raritate;
}

std::string Obiect::getNume() const {
    return m_nume;
}

int Obiect::getNrObiecte() {
    return m_obiecte_in_inventar;
}

int Obiect::getPret() const {
    return m_pret;
}
