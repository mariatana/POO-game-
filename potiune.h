#ifndef POTIUNE_H
#define POTIUNE_H

#include "Obiect.h" // Obiect.h include deja <string>, <iostream> si forward declare Player
// #include <iostream> // Inclus prin Obiect.h
// #include <string>   // Inclus prin Obiect.h

class Player; // Asiguram forward declaration

class Potiune : public Obiect {
private:
    bool m_tip; // true = vindecare, false = daunatoare

public:
    Potiune(int impact, int raritate, const std::string& nume, bool tip, int pret);
    ~Potiune() override;
    Potiune(const Potiune& other);

    int getImpactPotiune() const; // Declaratia este corecta
    bool getTip() const;

    // Corectam semnatura pentru a suprascrie metoda din Obiect
    void foloseste(Player* utilizator) override;
    Obiect* clone() const override;

    std::string getDetaliiMagazin() const override;
};

#endif