#ifndef ACTOR_H
#define ACTOR_H
#include <string>
#include <iostream>
class Actor
{
    protected:
    int health;
    public:
    Actor(int h);
    virtual void getStatus() const =0;
    virtual void afiseazaLovitura() const =0;
    virtual ~Actor();
    int getHealth() const;
    void setHealth(int h);
    void scadeViata(int dmg);



};

#endif
