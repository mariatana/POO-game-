#ifndef LUPTA_H
#define LUPTA_H

#include "player.h"
#include "inamic.h"

class Player;
class Lupta {
private:
    Player* m_player;
    Inamic* m_inamic;

public:
    Lupta(Player* p, Inamic* i);
    bool start();
};

#endif
