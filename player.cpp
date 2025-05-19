// ===== Player.cpp =====
#include "Player.h"
#include <cstring>
#include <vector>
#include "camera.h"
#include "obiect.h"
#include "inamic.h"
#include "arma.h"
#include <string>
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"



using namespace std;
//initializare total monstri batuti
int Player::MonstriBatuti=0;
//functia adaugare monstri batuti
void Player::AdaugaMosntriBatuti()
{
    MonstriBatuti++;
}
int Player::getMonstriBatuti()
{
    return MonstriBatuti;
}
// Constructorul jucătorului - pornește cu o cameră și o sumă de bani
Player::Player(int health,Camera* cameraStart, int p) : Actor(health), curentCamera(cameraStart), pocket(p), armaCurenta(nullptr), potiuniFolosite(0) {}

// Destructorul eliberează memoria pentru obiectele din inventar
Player::~Player() {
    for (Obiect* o : inventar) {
        delete o;
    }
   
}

// Adaugă un obiect în inventar
void Player::AdaugaObiect(Obiect* o) {
    inventar.push_back(o);
    if (!armaCurenta) armaCurenta = o; // Prima armă adăugată devine arma curentă
}

// Returnează numărul de bani
int Player::getPocket() const {
    return pocket;
}

// Afișează cu cât lovește jucătorul
void Player::afiseazaLovitura() const {
    if (armaCurenta) {
        int dmg = armaCurenta->getDamage();
        std::cout << "Ai lovit cu " << dmg << " damage folosind " << armaCurenta->getNume() << std::endl;
        
    } else {
        std::cout << "Nu ai nicio arma!" << std::endl;
    }
}

// Afișează statusul sănătății
void Player::getStatus() const {
    std::cout << "Sanatate curenta: " << health << std::endl;
}

// Returnează camera în care se află jucătorul
Camera* Player::getCamera() const {
    return curentCamera;
}

// Setează o cameră nouă ca fiind camera curentă
void Player::SetCamera(Camera* newCamera) {
    curentCamera = newCamera;
}

// Afișează obiectele din inventar
void Player::afiseazaInventar() const {
    if (inventar.empty()) {
        std::cout << "Inventarul este gol." << std::endl;
    } else {
        std::cout << "Inventarul contine:" << std::endl;
        for (Obiect* o : inventar) {
            std::cout << "- " << o->getNume() << " (damage: " << o->getDamage() << ", raritate: " << o->getRaritate() << ")" << std::endl;
        }
    }
}

// Setează o nouă armă ca fiind arma curentă
void Player::seteazaArma(Obiect* arma) {
    armaCurenta = arma;
}

// Simulează folosirea unei poțiuni (exemplu simplu)
void Player::folosestePotiune(Potiune *p) {
    potiuniFolosite++;
    if(p->getTip()==false)
    {
        health=health - p->getImpactPotiune();
        if (health < 0) 
           health = 0;
        std::cout<<RED<<"Unlucky...potiune neprietenoasa..te-a afectat cu "<<p->getImpactPotiune()<<" damage"<<RESET<<endl;
    }
    else
    {
        health=health+p->getImpactPotiune();
        std::cout<<"Ai folosit potiune de heal si ai primit"<<p->getImpactPotiune()<<"sanatate"<<endl;
    }

}

// Returnează numărul total de poțiuni folosite
int Player::getPotiuniFolosite() const {
    return potiuniFolosite;
}
void Player::AdaugaBani(int p)
{
    pocket+=p;
}
Obiect* Player::getArmaCurenta() const {
    return armaCurenta;
}
void Player::ScadeBani(int p)
{
   
    pocket-=p;

}

void Player::schimbaArma(std::string nume)
{
    
   int ok=0;
    for (Obiect* o : inventar) {
        Arma* arma = dynamic_cast<Arma*>(o);
        if (arma &&arma->getNume()==nume) {
            armaCurenta = arma;
            this->seteazaArma(armaCurenta);
            std::cout << "Arma a fost schimbata cu succes!\n";
            ok=1;
            break;
        }
    }
    if(ok==0)
    cout << "Nu exista nicio arma cu acest nume in inventar\n";
    
}
bool Player:: verificaDubluInventar(Obiect *obiectPrimit)
{
    for (Obiect *o : inventar)
      if(o->getNume()==obiectPrimit->getNume())
        {
            return false;
            break;
        }
    return true;
}
int Player:: getNumarArme() const{
    return inventar.size();
}
void Player:: furaRandomArma()
{
   
    std::vector<int> indexuriArme;//retinem pozitiile

    
    for (size_t i = 0; i < inventar.size(); ++i) {
        if (dynamic_cast<Arma*>(inventar[i])) {
            indexuriArme.push_back(i); 
        }
    }

    
    if (indexuriArme.empty()) {
        std::cout << "Nu ai nicio arma in inventar.\n";
        return;
    }

    int indexStergere = indexuriArme[rand() % indexuriArme.size()];

    std::cout << "Blestemul a furat arma: " << inventar[indexStergere]->getNume() << "\n";

   
    delete inventar[indexStergere];
    inventar.erase(inventar.begin() + indexStergere);
}



