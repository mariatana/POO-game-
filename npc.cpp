#include "npc.h"
#include "arma.h"
#include <iostream>

using namespace std;

NPC::NPC(const NpcInfo& info) : m_info(info) {}

void NPC::Interacționeaza(Player* player) const {
    cout << "NPC " << m_info.nume << ": " << m_info.mesaj << endl;
    if (m_info.da_bonus) {
        cout << "Ai primit un sfat sau un mic obiect bonus!" << endl;
         player->AdaugaBani(10);
         player->AdaugaObiect(new Arma(15, 2, "Topor Viking", 0));
    }
}
