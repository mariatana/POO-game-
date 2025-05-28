#include "cufar.h"

Cufar::Cufar(bool m_used) : m_used(m_used) {}

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
