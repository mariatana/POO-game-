#include <iostream>
#include <string>
#include "Obiect.h"
#include "Potiune.h"
#include "player.h"
using namespace std;


Potiune::Potiune(int d, int r, const std::string& n,bool tip,int pret):Obiect(d, r, n,pret),tip(tip){}
Potiune::~Potiune(){};
Potiune::Potiune(const Potiune& other):
   Obiect(other),tip(other.tip){}
bool Potiune ::getTip()
{
    return tip;
}

void Potiune::foloseste() 
{
   cout<<"f"<<endl;
   //! de compl
};
Obiect* Potiune::clone() const {
    return new Potiune(*this);
}
int Potiune::getImpactPotiune() const
{
    return this->getDamage();
}
