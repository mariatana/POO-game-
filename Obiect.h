#ifndef OBIECT_H
#define OBIECT_H

#include <string>
#include <iostream>

class Obiect {
private:
    int m_damage;
    int m_raritate;
    std::string m_nume;
    static int m_obiecte_in_inventar;
    int m_pret;

public:
    Obiect(int damage, int raritate, const std::string& nume, int pret);
    Obiect(const Obiect& other);
    virtual ~Obiect();
    friend std::ostream& operator<<(std::ostream& os, const Obiect& obj);
    virtual void foloseste() = 0;
    int getDamage() const;
    int getRaritate() const;
    std::string getNume() const;
    static int getNrObiecte();
    virtual Obiect* clone() const = 0;
    int getPret() const;
};

#endif
