#include "lupta.h"
#include "actor.h"
#include "player.h"
#include "Obiect.h"
#include "inamic.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

using namespace std;

Lupta::Lupta(Player* p, Inamic* i) : m_player(p), m_inamic(i) {}

bool Lupta::start() {
    cout << "Lupta a inceput cu " << m_inamic->getName() << "!\n";

    while (m_player->getHealth() > 0 && m_inamic->getHealth() > 0) {
        int dmg = m_player->getArmaCurenta()->getDamage();
        cout << "Ai lovit cu " << dmg << " damage\n";
        m_inamic->scadeViata(dmg);
        cout << "Inamicul are acum " << m_inamic->getHealth() << " HP.\n";

        if (m_inamic->getHealth() > 0) {
            int dmg_inamic = m_inamic->randomPunch();
            m_player->scadeViata(dmg_inamic);
            cout << "Inamicul te-a lovit cu " << dmg_inamic
                 << " damage. Tu ai acum " << m_player->getHealth() << " HP.\n";
        }
    }

    if (m_player->getHealth() > 0) {
        cout << GREEN << "Ai castigat lupta!" << RESET << endl;
        Player::AdaugaMosntriBatuti();
        return true;
    } else {
        cout << "Ai fost invins in lupta...\n";
        return false;
    }
}
