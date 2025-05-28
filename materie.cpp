#include <iostream>
#include <string>
#include "materie.h"

using namespace std;

// Constructor: inițializează materia cu un nume și o cantitate
MateriePrima::MateriePrima(const string& nume, int cantitate)
    : m_nume(nume), m_cantitate(cantitate) {}

MateriePrima::~MateriePrima() {}

// Returnează cantitatea curentă de materie
int MateriePrima::getCantitate() const {
    return m_cantitate;
}

// Returnează numele materiei
string MateriePrima::getNume() const {
    return m_nume;
}

// Adaugă o cantitate la materia existentă
void MateriePrima::adaugaCantitate(int x) {
    m_cantitate += x;
}

// Supraincarcă operatorul + pentru a combina două materii identice
MateriePrima& MateriePrima::operator+(const MateriePrima& other) {
    // Verifică dacă materiile au același nume
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

// Scade o cantitate din materia curentă (folosită la crafting)
void MateriePrima::consuma(int x) {
    m_cantitate -= x;
}
