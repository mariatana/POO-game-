#include <iostream>
#include <string>
#include "materie.h"

using namespace std;

MateriePrima::MateriePrima(const string& nume, int cantitate)
    : m_nume(nume), m_cantitate(cantitate) {}

MateriePrima::~MateriePrima() {}

int MateriePrima::getCantitate() const {
    return m_cantitate;
}

string MateriePrima::getNume() const {
    return m_nume;
}

void MateriePrima::adaugaCantitate(int x) {
    m_cantitate += x;
}

MateriePrima& MateriePrima::operator+(const MateriePrima& other) {
    if (m_nume == other.m_nume) {
        m_cantitate += other.m_cantitate;
        if (m_nume.find("Super") != 0) {
            m_nume = "Super" + m_nume;
        }
    } else {
        throw std::invalid_argument("Nu poți aduna materii diferite!");
    }
    return *this;
}

void MateriePrima::consuma(int x) {
    m_cantitate -= x;
}
