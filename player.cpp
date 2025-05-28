#include "Player.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream> 

#include "camera.h"
#include "Obiect.h" 
#include "Arma.h"   
#include "Potiune.h" 
#include "materie.h"


#ifndef RED_TEXT_COLOR_PLAYER 
#define RED_TEXT_COLOR_PLAYER     "\033[1;31m"
#define GREEN_TEXT_COLOR_PLAYER   "\033[1;32m"
#define YELLOW_TEXT_COLOR_PLAYER  "\033[1;33m"
#define RESET_TEXT_COLOR_PLAYER   "\033[0m"
#endif


int Player::m_monstri_batuti = 0;

void Player::AdaugaMonstriBatuti() {
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
    m_inventar.clear();
}

void Player::AdaugaObiect(Obiect* o) {
    if (!o) return;
    m_inventar.push_back(o);
    if (!m_arma_curenta) {
        Arma* arma = dynamic_cast<Arma*>(o);
        if (arma) {
            m_arma_curenta = arma;
        }
    }
}

void Player::stergeObiectDinInventar(Obiect* obj) {
    if (!obj) return;
    auto it = std::find(m_inventar.begin(), m_inventar.end(), obj);
    if (it != m_inventar.end()) {
    
        if (m_arma_curenta == dynamic_cast<Arma*>(*it)) {
            m_arma_curenta = nullptr;
        }
        delete *it; 
        m_inventar.erase(it);
    }
}


int Player::getPocket() const {
    return m_pocket;
}

void Player::afiseazaLovitura() const {
    if (m_arma_curenta) {
        int dmg = m_arma_curenta->getDamageArma();
        std::cout << "Ai lovit cu " << dmg
                  << " damage folosind " << m_arma_curenta->getNume() << std::endl;
    } else {
        std::cout << "Nu ai nicio arma echipata!" << std::endl;
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
        for (size_t i = 0; i < m_inventar.size(); ++i) {
            std::cout << i << ". ";
            if (!m_inventar[i]) {
                std::cout << "[Slot Gol/Eroare]" << std::endl;
                continue;
            }

            Arma* arma = dynamic_cast<Arma*>(m_inventar[i]);
            Potiune* potiune = dynamic_cast<Potiune*>(m_inventar[i]);

            if (arma) {
                std::cout << arma->getNume()
                          << " (Tip: Arma, Damage: " << arma->getDamageArma() // Corectat
                          << ", Raritate: " << arma->getRaritate() << ")" << std::endl;
            } else if (potiune) {
                 std::cout << potiune->getNume()
                          << " (Tip: Potiune, Efect: " << (potiune->getTip() ? "+" : "-")
                          << potiune->getImpactPotiune() // Corectat
                          << ", Raritate: " << potiune->getRaritate() << ")" << std::endl;
            } else { // Obiect generic (daca ar exista altele)
                std::cout << m_inventar[i]->getNume()
                          << " (Raritate: " << m_inventar[i]->getRaritate()
                          << ", Valoare Efect: " << m_inventar[i]->getValoareEfect() // Afisam valoarea generica
                          << ")" << std::endl;
            }
        }
    }
}

void Player::seteazaArma(Arma* arma) {
    m_arma_curenta = arma;
}


void Player::adaugaPotiuneFolosita() {
    m_potiuni_folosite++;
}

int Player::getPotiuniFolosite() const {
    return m_potiuni_folosite;
}

void Player::AdaugaBani(int p) {
    m_pocket += p;
}

void Player::ScadeBani(int p) {
    m_pocket -= p;
    if (m_pocket < 0) m_pocket = 0;
}

Arma* Player::getArmaCurenta() const {
    return m_arma_curenta;
}

void Player::schimbaArma(const std::string& nume) {
    bool gasit = false;
    for (Obiect* o : m_inventar) {
        Arma* arma_din_inventar = dynamic_cast<Arma*>(o);
        if (arma_din_inventar && arma_din_inventar->getNume() == nume) {
            m_arma_curenta = arma_din_inventar;
            std::cout << "Arma a fost schimbata cu succes in: " << m_arma_curenta->getNume() << std::endl;
            gasit = true;
            break;
        }
    }
    if (!gasit)
        std::cout << "Nu exista nicio arma cu acest nume in inventar sau obiectul nu este o arma.\n";
}

bool Player::verificaDubluInventar(Obiect* obiect_primit) const { // Adaugat const
    if (!obiect_primit) return true;
    for (Obiect* o : m_inventar)
        if (o && o->getNume() == obiect_primit->getNume())
            return false;
    return true;
}

int Player::getNumarArme() const {
    int count = 0;
    for (Obiect* o : m_inventar) {
        if (dynamic_cast<Arma*>(o)) {
            count++;
        }
    }
    return count;
}



void Player::adaugaMateriePrima(MateriePrima* m_prototip) {
    if (!m_prototip) return;
    std::string nume = m_prototip->getNume();
    int cantitate_prototip = m_prototip->getCantitate(); // Cantitatea din prototip (de obicei 1 sau valoarea default)

    auto it = m_inventar_materii.find(nume);
    if (it != m_inventar_materii.end()) {
        // Adaugam o unitate din materia prima gasita (sau cantitatea prototipului)
        it->second.adaugaCantitate(cantitate_prototip > 0 ? cantitate_prototip : 1);
    } else {
        // Cream o noua instanta de materie prima pentru inventarul jucatorului
        m_inventar_materii[nume] = MateriePrima(nume, cantitate_prototip > 0 ? cantitate_prototip : 1);
    }
}

void Player::afiseazaInventarMaterie() const { 
    int i = 0;
    if (m_inventar_materii.empty()) {
        std::cout << "Inventarul de materii prime este gol." << std::endl;
    } else {
        std::cout << "=== MATERII PRIME ===" << std::endl;
        for (const auto& entry : m_inventar_materii) {
            ++i;
            std::cout << i << ". " << entry.first
                      << " - cantitate: " << entry.second.getCantitate() << std::endl;
        }
    }
}

bool Player::AreMaterie(const std::string& nume, int cant_min) const {
    auto it = m_inventar_materii.find(nume);
    return it != m_inventar_materii.end() && it->second.getCantitate() >= cant_min;
}

void Player::consumaMateriePunte(const std::string& nume, int cant) {
    auto it = m_inventar_materii.find(nume);
    if (it != m_inventar_materii.end()) {
        it->second.consuma(cant);
        
    }
}

void Player::cresteViata(int valoare) {
    if (valoare < 0) return;
    m_health += valoare;
    
}

bool Player::PoateAdaugaObiect() const {
    return m_inventar.size() < MAX_OBIECTE_INVENTAR;
   
}