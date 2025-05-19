// ===== Obiect.h =====
#ifndef OBIECT_H
#define OBIECT_H

#include <string>
#include <iostream>

class Obiect {
private:
    int damage;              // Valoarea de damage pe care o provoacă obiectul (dacă e o armă)
    int raritate;            // Raritatea obiectului, poate influența șansele de drop
    std::string nume;        // Numele obiectului
    static int obiecteInInventar; // Contor static pentru obiectele aflate în joc
    int pret;

public:
    Obiect(int d, int r, const std::string& n,int pret);          // Constructor
    Obiect(const Obiect& other);                         // Constructor de copiere
    virtual ~Obiect();                                   // Destructor virtual
    friend std::ostream & operator<<(std::ostream& os, const Obiect &obj);//overl operator << 
    virtual void foloseste() = 0;                        // Funcție virtuală pură
    int getDamage() const;                               // Returnează damage-ul
    int getRaritate() const;                            
    std::string getNume() const;                         
    static int getNrObiecte();    
    virtual Obiect* clone() const = 0; // funcție pur virtuală  
    int getPret()const;                     
};
#endif