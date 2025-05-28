#include "Potiune.h"
#include "Player.h" 
#include <iostream> 
#include <sstream>  

#ifndef RED_TEXT_COLOR 
#define RED_TEXT_COLOR     "\033[1;31m"
#define GREEN_TEXT_COLOR   "\033[1;32m"
#define RESET_TEXT_COLOR   "\033[0m"
#endif


Potiune::Potiune(int impact, int raritate, const std::string& nume, bool tip, int pret)
    : Obiect(impact, raritate, nume, pret), m_tip(tip) {}

Potiune::~Potiune() {}

Potiune::Potiune(const Potiune& other)
    : Obiect(other), m_tip(other.m_tip) {}

bool Potiune::getTip() const {
    return m_tip;
}

// Implementarea corecta a metodei foloseste
void Potiune::foloseste(Player* utilizator) {
    if (!utilizator) {
        std::cout << "Eroare: Nu se poate folosi potiunea fara un utilizator valid." << std::endl;
        return;
    }

    utilizator->adaugaPotiuneFolosita();

    std::cout << "Ai folosit " << getNume() << "." << std::endl;
    if (!m_tip) { // Daca potiunea este de tip rau (false)
        utilizator->scadeViata(getImpactPotiune()); // Folosim getImpactPotiune
        std::cout << RED_TEXT_COLOR << "Din pacate, potiunea a fost neprietenoasa si ti-a scazut viata cu "
                  << getImpactPotiune() << "!" << RESET_TEXT_COLOR << std::endl;
        if (utilizator->getHealth() <= 0) {
            std::cout << RED_TEXT_COLOR << "Potiunea te-a ucis!" << RESET_TEXT_COLOR << std::endl;
        }
    } else { // Potiune de tip bun (true)
        utilizator->cresteViata(getImpactPotiune()); // Folosim getImpactPotiune
        std::cout << GREEN_TEXT_COLOR << "Potiunea ti-a redat "
                  << getImpactPotiune() << " sanatate!" << RESET_TEXT_COLOR << std::endl;
    }
}

Obiect* Potiune::clone() const {
    return new Potiune(*this);
}

// Implementarea pentru getImpactPotiune
int Potiune::getImpactPotiune() const {
    return getValoareEfect(); 
}

std::string Potiune::getDetaliiMagazin() const {
    std::stringstream ss;
    ss << Obiect::getDetaliiMagazin()
       << (getTip() ? ", Efect: +" : ", Efect: -") << getImpactPotiune()
       << (getTip() ? " HP" : " HP");
    return ss.str();
}