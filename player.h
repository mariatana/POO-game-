#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include "actor.h"
#include "materie.h" 

class Camera;
class Obiect;
class Arma;   

class Player : public Actor {
private:
    int m_pocket;
    std::vector<Obiect*> m_inventar;
    Camera* m_curent_camera;
    Arma* m_arma_curenta; 
     static const int MAX_OBIECTE_INVENTAR = 10;
    static int m_monstri_batuti;
    std::map<std::string, MateriePrima> m_inventar_materii;
    int m_potiuni_folosite;

public:
    Player(int health, Camera* camera_start, int p);
    ~Player() override;
     bool PoateAdaugaObiect() const;
    void AdaugaObiect(Obiect* o);
    void AdaugaBani(int p);

    int getPocket() const;
    void ScadeBani(int p);
    void afiseazaLovitura() const override;
    void getStatus() const override;
    static void AdaugaMonstriBatuti();
    static int getMonstriBatuti();
    Camera* getCamera() const;
    void SetCamera(Camera* new_camera);

    void afiseazaInventar() const;
    void schimbaArma(const std::string& nume);
    void seteazaArma(Arma* arma); 

    

    bool verificaDubluInventar(Obiect* obiect_primit) const; 
  
    int getNumarArme() const;
    int getPotiuniFolosite() const;
    void adaugaPotiuneFolosita();
    Arma* getArmaCurenta() const;

    void adaugaMateriePrima(MateriePrima* m);
    void afiseazaInventarMaterie() const; 
    bool AreMaterie(const std::string& nume, int cant_min) const;
    void consumaMateriePunte(const std::string& nume, int cant);

    void cresteViata(int valoare);
    void stergeObiectDinInventar(Obiect* obj); 
};

#endif