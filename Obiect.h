#ifndef OBIECT_H
#define OBIECT_H

#include <string>
#include <iostream>


class Player;

class Obiect {
private:
    int m_valoare_efect; 
    int m_raritate;
    std::string m_nume;
    static int m_obiecte_in_inventar;
    int m_pret;

public:
    Obiect(int valoare_efect, int raritate, const std::string& nume, int pret);
    Obiect(const Obiect& other);
    virtual ~Obiect();
    friend std::ostream& operator<<(std::ostream& os, const Obiect& obj);

    // Metoda foloseste va lua un Player ca argument pentru a permite interactiunea
    virtual void foloseste(Player* utilizator) = 0;

    int getValoareEfect() const;
    int getRaritate() const;
    std::string getNume() const;
    static int getNrObiecte();
    virtual Obiect* clone() const = 0;
    int getPret() const;

    virtual std::string getDetaliiMagazin() const;
};

#endif