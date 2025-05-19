#include "Obiect.h"
#include "inamic.h"
#include "camera.h"
#include <vector>
#include <string>
int Obiect::obiecteInInventar = 0; // Inițializare variabilă statică


// Constructor clasic
Obiect::Obiect(int d, int r, const std::string& n,int pret) : damage(d), raritate(r), nume(n),pret(pret) {
    obiecteInInventar++;
}

// Constructor de copiere
Obiect::Obiect(const Obiect& other) : damage(other.damage), raritate(other.raritate), nume(other.nume) {
    obiecteInInventar++;
}
std::ostream& operator<<(std::ostream& os, const Obiect& obj) {
    os << obj.getNume() << " (Damage: " << obj.getDamage() << ", Raritate: " << obj.getRaritate() << ")";
    return os;
}

// Destructor
Obiect::~Obiect() {
    obiecteInInventar--;
}

int Obiect::getDamage() const {
    return damage;
}

int Obiect::getRaritate() const {
    return raritate;
}

std::string Obiect::getNume() const {
    return nume;
}

int Obiect::getNrObiecte() {
    return obiecteInInventar;
}
int Obiect::getPret() const
{
    return this->pret;
}