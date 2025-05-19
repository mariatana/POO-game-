#ifndef LUPTA_H
#define LUPTA_H

#include "player.h"
#include "inamic.h"
class Player;
class Lupta {
private:
    Player* player;
    Inamic* inamic;

public:
    Lupta(Player* p, Inamic* i);   // Constructor
    bool start();                  // Corect: FĂRĂ parametri!
};

#endif
