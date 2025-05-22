#ifndef NPC_H
#define NPC_H

#include <string>
#include <iostream>
#include "player.h"

// Struct definit global, poate fi folosit în alte clase/functii
struct NpcInfo {
    std::string nume;
    std::string mesaj;
    bool da_bonus;
};

class NPC {
private:
    NpcInfo m_info;

public:
    NPC(const NpcInfo& info);
    void Interacționeaza(Player* player) const;
};

#endif
