#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include <iostream>

class Actor {
protected:
    int m_health;
    //modif
protected:
 Actor(int health);

public:

    virtual void getStatus() const = 0;
    virtual void afiseazaLovitura() const = 0;
    virtual ~Actor();
    int getHealth() const;
    void setHealth(int health);
    void scadeViata(int damage);
};

#endif