#ifndef INAMIC_H
#define INAMIC_H
#include <iostream>
#include <string>
#include "Actor.h"
class Inamic:public Actor
{
    private:
    int mindamage;
    int maxDamage;
    std::string monsterName;
    public:
    Inamic(int health,int miD,int maD,const std::string &nume );
    ~Inamic();
    int getMinimDamage() const;
    int randomPunch() const;
    void afiseazaLovitura() const override;
    int randomMoney()const;
    void getStatus() const override;
    std::string getName() const;


};
#endif