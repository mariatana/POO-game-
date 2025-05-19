#include "Arma.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

Arma::Arma(int damage, int raritate, const std::string& nume,int pret)
    : Obiect(damage, raritate, nume,pret) {}

Arma::Arma(const Arma& other)
    : Obiect(other) {}

Arma::~Arma() {
    // Poți pune debug info dacă vrei:
    // cout << "Destructor Arma: " << nume << " s-a distrus.\n";
}

void Arma::foloseste() {
    cout << "Ai folosit arma " << getNume() << " care face " << getDamage() << " damage!" << endl;
}
Obiect* Arma::clone() const {
    return new Arma(*this);  // apelează constructorul de copiere
}
