#include <iostream>
#include <string>
#include "materie.h"
using namespace std;
MateriePrima::MateriePrima(const string &nume, int cantitate): nume(nume), cantitate(cantitate){}
MateriePrima::~MateriePrima(){}
int MateriePrima::getCantitate() const
{
    return cantitate;

}
string MateriePrima::getNume() const
{
    return nume;

}
void MateriePrima::adaugaCantitate(int x)
{
   cantitate+=x;
}
MateriePrima& MateriePrima::operator+=(const MateriePrima& other) {
    if (nume == other.nume) {
        cantitate += other.cantitate;
    } else {
        throw std::invalid_argument("Nu poți aduna materii diferite!");
    }
    return *this;
}
void MateriePrima::consuma(int x)
{
    cantitate-=x;
}
