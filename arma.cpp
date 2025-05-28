#include "Arma.h"
#include "Player.h" 
#include <iostream> 
#include <sstream>  

Arma::Arma(int damageArma, int raritate, const std::string& nume, int pret)
    : Obiect(damageArma, raritate, nume, pret) {} 

Arma::Arma(const Arma& other)
    : Obiect(other) {}

Arma::~Arma() {}


void Arma::foloseste(Player* utilizator) {
    std::cout << "Arma " << getNume() << " este pregatita. ";
    std::cout << "Face " << getDamageArma() << " damage." << std::endl;
}

Obiect* Arma::clone() const {
    return new Arma(*this);
}

int Arma::getDamageArma() const {
    return getValoareEfect();
}

std::string Arma::getDetaliiMagazin() const {
    std::stringstream ss;
    // Folosim implementarea din Obiect si adaugam specificul Armei
    ss << Obiect::getDetaliiMagazin() << ", Damage: " << getDamageArma();
    return ss.str();
}