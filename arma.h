#ifndef ARMA_H
#define ARMA_H

#include "Obiect.h"
#include "player.h"
#include <iostream>
#include <string>

class Obiect;
class Arma : public Obiect {
public:
    // Constructor cu parametri
    Arma(int damage, int raritate, const std::string& nume,int pret);

    // Constructor de copiere
    Arma(const Arma& other);
   
    // Destructor
    ~Arma() override;
    
    // Implementarea metodei virtuale pure din Obiect
    void foloseste() override;
    Obiect* clone() const override;
};

#endif
