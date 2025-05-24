#include "magazin.h"

void Magazin::adaugaObiect(Obiect* obj) {
    m_stoc.push_back(obj);
}

void Magazin::afiseazaStoc() const {
    for (int i = 0; i < m_stoc.size(); ++i) {
        std::cout << i << ". " << m_stoc[i]->getNume()
                  << " (Pret: " << m_stoc[i]->getPret()
                  << ", Damage: " << m_stoc[i]->getDamage() << ")\n";
    }
}

Obiect* Magazin::cumparaObiect(int index, Player* player) {
    if (index < 0 || index >= static_cast<int>(m_stoc.size())) {
        std::cout << "Obiect inexistent!\n";
        return nullptr;
    }

    Obiect* de_cumparat = m_stoc[index];
    int pret = de_cumparat->getPret();

    if (player->getPocket() >= pret) {
        player->ScadeBani(pret);
        m_stoc.erase(m_stoc.begin() + index);
        std::cout << "Ai cumparat: " << de_cumparat->getNume() << "\n";
        return de_cumparat;
    } else {
        std::cout << "Nu ai destui bani pentru acest obiect!\n";
        return nullptr;
    }
}
