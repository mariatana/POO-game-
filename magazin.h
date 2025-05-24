#ifndef MAGAZIN_H
#define MAGAZIN_H

#include "Obiect.h"
#include "player.h"
#include <vector>

class Player;
class Magazin {
private:
    std::vector<Obiect*> m_stoc;

public:
    void adaugaObiect(Obiect* o);
    void afiseazaStoc() const;
    Obiect* cumparaObiect(int index, Player* player);
    bool esteGol() const;
};

#endif
