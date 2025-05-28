#include "Obiect.h"
// #include "inamic.h" // Nu pare necesar aici
// #include "camera.h" // Nu pare necesar aici
// #include <vector> // Nu pare necesar aici
#include <string>
#include <sstream> // Pentru getDetaliiMagazin

int Obiect::m_obiecte_in_inventar = 0;

Obiect::Obiect(int valoare_efect, int raritate, const std::string& nume, int pret)
    : m_valoare_efect(valoare_efect), m_raritate(raritate), m_nume(nume), m_pret(pret) {
    m_obiecte_in_inventar++;
}

Obiect::Obiect(const Obiect& other)
    : m_valoare_efect(other.m_valoare_efect), m_raritate(other.m_raritate),
      m_nume(other.m_nume), m_pret(other.m_pret) {
    m_obiecte_in_inventar++;
}

std::ostream& operator<<(std::ostream& os, const Obiect& obj) {
    // Afisarea in stream ramane generala, sau poate fi imbogatita cu getDetaliiMagazin
    os << obj.getNume() << " (Raritate: " << obj.getRaritate() << ")";
    return os;
}

Obiect::~Obiect() {
    m_obiecte_in_inventar--;
}

int Obiect::getValoareEfect() const { // Redenumit din getDamage
    return m_valoare_efect;
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

// Implementare default pentru getDetaliiMagazin
std::string Obiect::getDetaliiMagazin() const {
    std::stringstream ss;
    ss << getNume() << " (Pret: " << getPret()
       << ", Raritate: " << getRaritate() << ")";
    return ss.str();
}