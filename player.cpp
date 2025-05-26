#include "Player.h"
#include <vector>
#include <string>
#include "camera.h"
#include "obiect.h"
#include "inamic.h"
#include "materie.h"
#include "arma.h"

// Coduri pentru colorarea textului în consolă
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

// Inițializare variabilă statică pentru contorul de monștri învinși
int Player::m_monstri_batuti = 0;

// Funcție care incrementează numărul total de monștri învinși
void Player::AdaugaMosntriBatuti() {
    m_monstri_batuti++;
}

// Returnează câți monștri au fost învinși
int Player::getMonstriBatuti() {
    return m_monstri_batuti;
}

// Constructorul clasei Player - inițializează sănătatea, camera, bani și setările de început
Player::Player(int health, Camera* camera_start, int p)
    : Actor(health), m_curent_camera(camera_start), m_pocket(p),
      m_arma_curenta(nullptr), m_potiuni_folosite(0) {}

// Destructor - eliberează memoria ocupată de obiectele din inventar
Player::~Player() {
    for (Obiect* o : m_inventar) {
        delete o;
    }
}

// Adaugă un obiect în inventar, iar dacă nu ai armă, îl setează ca armă curentă
void Player::AdaugaObiect(Obiect* o) {
    m_inventar.push_back(o);
    if (!m_arma_curenta) m_arma_curenta = o;
}

// Returnează cantitatea de bani a jucătorului
int Player::getPocket() const {
    return m_pocket;
}

// Afișează damage-ul dat în atac și numele armei folosite
void Player::afiseazaLovitura() const {
    if (m_arma_curenta) {
        int dmg = m_arma_curenta->getDamage();
        std::cout << "Ai lovit cu " << dmg
                  << " damage folosind " << m_arma_curenta->getNume() << std::endl;
    } else {
        std::cout << "Nu ai nicio arma!" << std::endl;
    }
}

// Afișează sănătatea curentă a jucătorului
void Player::getStatus() const {
    std::cout << "Sanatate curenta: " << m_health << std::endl;
}

// Returnează camera curentă în care se află jucătorul
Camera* Player::getCamera() const {
    return m_curent_camera;
}

// Setează camera curentă la o nouă cameră
void Player::SetCamera(Camera* new_camera) {
    m_curent_camera = new_camera;
}

// Afișează obiectele din inventar, dacă există
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

// Setează arma curentă la un obiect dat
void Player::seteazaArma(Obiect* arma) {
    m_arma_curenta = arma;
}

// Folosește o poțiune și aplică efectele (vindecare sau damage)
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

// Returnează câte poțiuni au fost folosite
int Player::getPotiuniFolosite() const {
    return m_potiuni_folosite;
}

// Adaugă bani în buzunarul jucătorului
void Player::AdaugaBani(int p) {
    m_pocket += p;
}

// Scade o sumă de bani din buzunarul jucătorului
void Player::ScadeBani(int p) {
    m_pocket -= p;
}

// Returnează arma curentă
Obiect* Player::getArmaCurenta() const {
    return m_arma_curenta;
}

// Schimbă arma curentă cu una nouă, căutând-o după nume în inventar
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

// Verifică dacă un obiect există deja în inventar (după nume)
bool Player::verificaDubluInventar(Obiect* obiect_primit) {
    for (Obiect* o : m_inventar)
        if (o->getNume() == obiect_primit->getNume())
            return false;
    return true;
}

// Returnează numărul total de obiecte (arme) din inventar
int Player::getNumarArme() const {
    return m_inventar.size();
}

// Alege o armă la întâmplare din inventar și o elimină (blestem)
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

// Adaugă materie primă în inventar; dacă există deja, crește cantitatea
void Player::adaugaMateriePrima(MateriePrima* m) {
    std::string nume = m->getNume();
    int cantitate = m->getCantitate();

    if (m_inventar_materii.find(nume) != m_inventar_materii.end()) {
        m_inventar_materii[nume].adaugaCantitate(cantitate);
    } else {
        m_inventar_materii[nume] = *m;
    }
}

// Afișează materiile prime deținute de jucător
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

// Verifică dacă jucătorul are o anumită materie primă într-o cantitate minimă
bool Player::AreMaterie(const std::string& nume, int cant_min) {
    auto it = m_inventar_materii.find(nume);
    return it != m_inventar_materii.end() && it->second.getCantitate() >= cant_min;
}

// Scade o anumită cantitate dintr-o materie primă
void Player::consumaMateriePunte(const std::string& nume, int cant) {
    auto it = m_inventar_materii.find(nume);
    if (it != m_inventar_materii.end()) {
        it->second.consuma(cant);
    }
}
