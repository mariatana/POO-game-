#ifndef POTIUNE_H
#define POTIUNE_H
#include <iostream>
#include <vector>
#include <string>
#include "player.h"
class Player;
class Obiect;
class Potiune :public Obiect
{
    private:
    bool tip;//daca e 1 da heal, altfel da direct damage...na..esti mai ghinionist cateodata:)
    public:
    Potiune(int d, int r, const std::string& n,bool tip,int pret);
    ~Potiune()override;
    Potiune(const Potiune& other);//cpy constr
    int getImpactPotiune()const;
    bool getTip();// da tipul de potiune
    void foloseste() override;
    Obiect* clone() const override;


};
#endif