#include "cufar.h"

Cufar::Cufar(bool used) : used(false) {}   

Cufar::~Cufar() {}

void Cufar::folosesteCufar() {
    std::cout << "Cufarul este folosit!\n";
}

bool Cufar::getStateCufar() const {
    return used;
}

void Cufar::schimbaStareCufar() {
    used = true;
}
