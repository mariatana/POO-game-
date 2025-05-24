#include "cufar.h"

Cufar::Cufar(bool used) : m_used(false) {}

Cufar::~Cufar() {}

void Cufar::folosesteCufar() {
    std::cout << "Cufarul este folosit!\n";
}

bool Cufar::getStateCufar() const {
    return m_used;
}

void Cufar::schimbaStareCufar() {
    m_used = true;
}
