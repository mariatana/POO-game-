#include "magazin.h"

// Adaugă un obiect în stocul magazinului
void Magazin::adaugaObiect(Obiect* obj) {
    m_stoc.push_back(obj);
}

// Afișează toate obiectele disponibile în magazin
void Magazin::afiseazaStoc() const {
    for (int i = 0; i < m_stoc.size(); ++i) {
        std::cout << i << ". " << m_stoc[i]->getNume()            // Numele obiectului
                  << " (Pret: " << m_stoc[i]->getPret()           // Prețul obiectului
                  << ", Damage: " << m_stoc[i]->getDamage() << ")\n";  // Damage-ul (dacă e armă)
    }
}

// Permite jucătorului să cumpere un obiect din magazin, dacă are bani suficienți
Obiect* Magazin::cumparaObiect(int index, Player* player) {
    // Verifică dacă indexul este valid
    if (index < 0 || index >= static_cast<int>(m_stoc.size())) {
        std::cout << "Obiect inexistent!\n";
        return nullptr;
    }

    Obiect* de_cumparat = m_stoc[index];      // Obiectul selectat pentru cumpărare
    int pret = de_cumparat->getPret();        // Prețul obiectului

    // Verifică dacă jucătorul are bani suficienți
    if (player->getPocket() >= pret) {
        player->ScadeBani(pret);              // Scade banii din portofelul jucătorului
        m_stoc.erase(m_stoc.begin() + index); // Elimină obiectul din stocul magazinului
        std::cout << "Ai cumparat: " << de_cumparat->getNume() << "\n";
        return de_cumparat;                   // Returnează pointerul către obiectul cumpărat
    } else {
        std::cout << "Nu ai destui bani pentru acest obiect!\n";
        return nullptr;                       // Nu s-a putut face achiziția
    }
}
