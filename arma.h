#ifndef ARMA_H
#define ARMA_H

#include "Obiect.h"
#include "player.h"
#include <iostream>
#include <string>

class Obiect;
class Arma : public Obiect {
public:
    Arma(int damage, int raritate, const std::string& nume, int pret);
    Arma(const Arma& other);
    ~Arma() override;
    void foloseste() override;
    Obiect* clone() const override;
};

#endif
