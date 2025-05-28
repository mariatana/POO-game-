#include "lupta.h"
#include "actor.h"
#include "player.h"
#include "Obiect.h"
#include "inamic.h"
#include "arma.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Coduri pentru colorarea textului în consolă
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

using namespace std;

// Constructor: primește un pointer către player și unul către inamic
Lupta::Lupta(Player* p, Inamic* i) : m_player(p), m_inamic(i) {}

// Metoda care pornește efectiv lupta între player și inamic
bool Lupta::start() {
    cout << "Lupta a inceput cu " << m_inamic->getName() << "!\n";

    // Loop-ul principal al luptei continuă cât timp ambii sunt în viață
    while (m_player->getHealth() > 0 && m_inamic->getHealth() > 0) {
        // Jucătorul atacă
        int dmg = m_player->getArmaCurenta()->getValoareEfect();
        cout << "Ai lovit cu " << dmg << " damage\n";
        m_inamic->scadeViata(dmg);  // Se scade viața inamicului
        cout << "Inamicul are acum " << m_inamic->getHealth() << " HP.\n";

        // Dacă inamicul mai este în viață, atacă și el
        if (m_inamic->getHealth() > 0) {
            int dmg_inamic = m_inamic->randomPunch();  // Damage aleatoriu al inamicului
            m_player->scadeViata(dmg_inamic);          // Se scade viața jucătorului
            cout << "Inamicul te-a lovit cu " << dmg_inamic
                 << " damage. Tu ai acum " << m_player->getHealth() << " HP.\n";
        }
    }

    // Se verifică rezultatul luptei și se afișează mesajul corespunzător
    if (m_player->getHealth() > 0) {
        cout << GREEN << "Ai castigat lupta!" << RESET << endl;
        Player::AdaugaMonstriBatuti();  // Se incrementează contorul de monștri învinși
        return true;
    } else {
        cout << "Ai fost invins in lupta...\n";
        return false;
    }
}
