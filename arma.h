#ifndef ARMA_H
#define ARMA_H

#include "Obiect.h" 

class Player; 

class Arma : public Obiect {
public:
    Arma(int damageArma, int raritate, const std::string& nume, int pret);
    Arma(const Arma& other);
    ~Arma() override;

   
    void foloseste(Player* utilizator) override;
    Obiect* clone() const override;

    int getDamageArma() const;

    std::string getDetaliiMagazin() const override;
};

#endif