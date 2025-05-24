#ifndef INAMIC_H
#define INAMIC_H

#include <iostream>
#include <string>
#include "Actor.h"

class Inamic : public Actor {
private:
    int m_min_damage;
    int m_max_damage;
    std::string m_monster_name;

public:
    Inamic(int health, int min_dmg, int max_dmg, const std::string& nume);
    ~Inamic();
    int getMinimDamage() const;
    int randomPunch() const;
    void afiseazaLovitura() const override;
    int randomMoney() const;
    void getStatus() const override;
    std::string getName() const;
};

#endif
