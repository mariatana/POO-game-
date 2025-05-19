// Magazin.cpp
#include "magazin.h"
void Magazin::adaugaObiect(Obiect* obj) {
    stoc.push_back(obj);
}

void Magazin::afiseazaStoc() const {
    for (int i = 0; i < stoc.size(); ++i) {
        std::cout << i << ". " << stoc[i]->getNume()
                  << " (Pret: " << stoc[i]->getPret() << ", Damage: " << stoc[i]->getDamage() << ")\n";
    }
}

Obiect* Magazin::cumparaObiect(int index, Player* player) {
    if (index < 0 || index >= static_cast<int>(stoc.size())) {
        std::cout << "Obiect inexistent!\n";
        return nullptr;
    }

    Obiect* deCumparat = stoc[index];
    int pret = deCumparat->getPret();

    if (player->getPocket() >= pret) {
        player->ScadeBani(pret); // scadem banii
        Obiect* obiectCumparat = deCumparat;
        stoc.erase(stoc.begin() + index); // scoatem din magazin
        std::cout << "Ai cumparat: " << obiectCumparat->getNume() << "\n";
        return obiectCumparat; // transferam obiectul către player
    } else {
        std::cout << "Nu ai destui bani pentru acest obiect!\n";
        return nullptr;
    }
}
