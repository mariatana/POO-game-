#include "Arma.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Arma::Arma(int damage, int raritate, const std::string& nume, int pret)
    : Obiect(damage, raritate, nume, pret) {}

Arma::Arma(const Arma& other)
    : Obiect(other) {}

Arma::~Arma() {}

void Arma::foloseste() {
    cout << "Ai folosit arma " << getNume() << " care face " << getDamage() << " damage!" << endl;
}

Obiect* Arma::clone() const {
    return new Arma(*this);
}
