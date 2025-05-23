#ifndef MATERIE_H
#define MATERIE_H
#include <string>
using namespace std;
class MateriePrima
{
    private:
    string nume;
    int cantitate;
    public:
     MateriePrima() : nume(""), cantitate(0) {}
    MateriePrima(const string &nume, int cantitate);
    ~MateriePrima();
    int getCantitate() const;
    string getNume() const;
    void adaugaCantitate(int x);
};
#endif
