#include "Player.h"
#include <vector>
#include <string>
#include "camera.h"
#include "obiect.h"
#include "inamic.h"
#include "materie.h"
#include "arma.h"

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

int Player::m_monstri_batuti = 0;

void Player::AdaugaMosntriBatuti() {
    m_monstri_batuti++;
}

int Player::getMonstriBatuti() {
    return m_monstri_batuti;
}

Player::Player(int health, Camera* camera_start, int p)
    : Actor(health), m_curent_camera(camera_start), m_pocket(p),
      m_arma_curenta(nullptr), m_potiuni_folosite(0) {}

Player::~Player() {
    for (Obiect* o : m_inventar) {
        delete o;
    }
}

void Player::AdaugaObiect(Obiect* o) {
    m_inventar.push_back(o);
    if (!m_arma_curenta) m_arma_curenta = o;
}

int Player::getPocket() const {
    return m_pocket;
}

void Player::afiseazaLovitura() const {
    if (m_arma_curenta) {
        int dmg = m_arma_curenta->getDamage();
        std::cout << "Ai lovit cu " << dmg
                  << " damage folosind " << m_arma_curenta->getNume() << std::endl;
    } else {
        std::cout << "Nu ai nicio arma!" << std::endl;
    }
}

void Player::getStatus() const {
    std::cout << "Sanatate curenta: " << m_health << std::endl;
}

Camera* Player::getCamera() const {
    return m_curent_camera;
}

void Player::SetCamera(Camera* new_camera) {
    m_curent_camera = new_camera;
}

void Player::afiseazaInventar() const {
    if (m_inventar.empty()) {
        std::cout << "Inventarul este gol." << std::endl;
    } else {
        std::cout << "Inventarul contine:" << std::endl;
        for (Obiect* o : m_inventar) {
            std::cout << "- " << o->getNume()
                      << " (damage: " << o->getDamage()
                      << ", raritate: " << o->getRaritate() << ")" << std::endl;
        }
    }
}

void Player::seteazaArma(Obiect* arma) {
    m_arma_curenta = arma;
}

void Player::folosestePotiune(Potiune* p) {
    m_potiuni_folosite++;
    if (!p->getTip()) {
        m_health -= p->getImpactPotiune();
        if (m_health < 0) m_health = 0;
        std::cout << RED << "Unlucky...potiune neprietenoasa..te-a afectat cu "
                  << p->getImpactPotiune() << " damage" << RESET << std::endl;
    } else {
        m_health += p->getImpactPotiune();
        std::cout << "Ai folosit potiune de heal si ai primit "
                  << p->getImpactPotiune() << " sanatate" << std::endl;
    }
}

int Player::getPotiuniFolosite() const {
    return m_potiuni_folosite;
}

void Player::AdaugaBani(int p) {
    m_pocket += p;
}

void Player::ScadeBani(int p) {
    m_pocket -= p;
}

Obiect* Player::getArmaCurenta() const {
    return m_arma_curenta;
}

void Player::schimbaArma(std::string nume) {
    bool ok = false;
    for (Obiect* o : m_inventar) {
        Arma* arma = dynamic_cast<Arma*>(o);
        if (arma && arma->getNume() == nume) {
            m_arma_curenta = arma;
            this->seteazaArma(arma);
            std::cout << "Arma a fost schimbata cu succes!\n";
            ok = true;
            break;
        }
    }
    if (!ok)
        std::cout << "Nu exista nicio arma cu acest nume in inventar\n";
}

bool Player::verificaDubluInventar(Obiect* obiect_primit) {
    for (Obiect* o : m_inventar)
        if (o->getNume() == obiect_primit->getNume())
            return false;
    return true;
}

int Player::getNumarArme() const {
    return m_inventar.size();
}

void Player::furaRandomArma() {
    std::vector<int> indexuri_arme;
    for (size_t i = 0; i < m_inventar.size(); ++i) {
        if (dynamic_cast<Arma*>(m_inventar[i])) {
            indexuri_arme.push_back(i);
        }
    }

    if (indexuri_arme.empty()) {
        std::cout << "Nu ai nicio arma in inventar.\n";
        return;
    }

    int index_stergere = indexuri_arme[rand() % indexuri_arme.size()];
    std::cout << "Blestemul a furat arma: "
              << m_inventar[index_stergere]->getNume() << "\n";

    delete m_inventar[index_stergere];
    m_inventar.erase(m_inventar.begin() + index_stergere);
}

void Player::adaugaMateriePrima(MateriePrima* m) {
    std::string nume = m->getNume();
    int cantitate = m->getCantitate();

    if (m_inventar_materii.find(nume) != m_inventar_materii.end()) {
        m_inventar_materii[nume].adaugaCantitate(cantitate);
    } else {
        m_inventar_materii[nume] = *m;
    }
}

void Player::afiseazaInventarMaterie() {
    int i = 0;
    if (m_inventar_materii.empty()) {
        std::cout << "Inventarul de materii prime este gol." << std::endl;
    } else {
        for (const auto& entry : m_inventar_materii) {
            ++i;
            std::cout << i << ". " << entry.first
                      << " - cantitate: " << entry.second.getCantitate() << std::endl;
        }
    }
}

bool Player::AreMaterie(const std::string& nume, int cant_min) {
    auto it = m_inventar_materii.find(nume);
    return it != m_inventar_materii.end() && it->second.getCantitate() >= cant_min;
}

void Player::consumaMateriePunte(const std::string& nume, int cant) {
    auto it = m_inventar_materii.find(nume);
    if (it != m_inventar_materii.end()) {
        it->second.consuma(cant);
    }
}
