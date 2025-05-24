#ifndef POTIUNE_H
#define POTIUNE_H

#include <iostream>
#include <vector>
#include <string>
#include "player.h"

class Player;
class Obiect;

class Potiune : public Obiect {
private:
    bool m_tip;

public:
    Potiune(int damage, int raritate, const std::string& nume, bool tip, int pret);
    ~Potiune() override;
    Potiune(const Potiune& other);
    int getImpactPotiune() const;
    bool getTip();
    void foloseste() override;
    Obiect* clone() const override;
};

#endif
