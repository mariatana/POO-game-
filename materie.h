#ifndef MATERIE_H
#define MATERIE_H

#include <string>
using namespace std;

class MateriePrima {
private:
    string m_nume;
    int m_cantitate;

public:
    MateriePrima() : m_nume(""), m_cantitate(0) {}
    MateriePrima(const string& nume, int cantitate);
    ~MateriePrima();
    int getCantitate() const;
    string getNume() const;
    void adaugaCantitate(int x);
    void consuma(int x);
    MateriePrima& operator+(const MateriePrima& other);
};

#endif
