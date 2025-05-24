#ifndef PLAYER_H
#define PLAYER_H
#include <map>
#include "actor.h"
#include "camera.h"
#include "Obiect.h"
#include "potiune.h"
#include "materie.h"
#include <vector>
#include <string>
#include <iostream>
class Inamic;
class Camera;
class Obiect;
class Potiune;
class Arma;
class MateriePrima;
class Player : public Actor {
private:
    int pocket;                             // Banii jucătorului
    std::vector<Obiect*> inventar;          // Inventarul (arme, poțiuni etc.)
    Camera* curentCamera;                   // Camera curentă în care se află jucătorul
    Obiect* armaCurenta;                    // Arma pe care o folosește momentan
    static int MonstriBatuti;
    map<string, MateriePrima> inventarmaterii;       
    int potiuniFolosite;                    // Poate fi util pentru afișare finală/statistici
   

public:
    Player(int health,Camera* cameraStart, int p);     // Constructor cu cameră inițială și bani
    ~Player() override;                     // Destructor override

    void AdaugaObiect(Obiect* o);  
    void AdaugaBani(int p);
      
    int getPocket() const;                  // Returnează banii
    void ScadeBani(int p);
    void afiseazaLovitura() const override; // Afișează lovitura curentă
    void getStatus() const override;        // Afișează statusul sănătății
    static void AdaugaMosntriBatuti();
    int getMonstriBatuti();
    Camera* getCamera() const;              // Returnează camera curentă
    void SetCamera(Camera* newCamera);      // Setează o cameră nouă curentă

    void afiseazaInventar() const;          // Afișează conținutul inventarului
    void schimbaArma(std::string nume);
    void seteazaArma(Obiect* arma);         // Seta arma curentă (în caz că jucătorul o schimbă)
    void folosestePotiune(Potiune *p);  
    bool verificaDubluInventar(Obiect *ObiectPrimit) ;     //verifica dublicitatea armelor in inventar
    void furaRandomArma() ;//scoet arma din inventar
    int getNumarArme() const;
    int getPotiuniFolosite() const; 
    Obiect* getArmaCurenta() const;    
    void adaugaMateriePrima(MateriePrima *m);    
    void afiseazaInventarMaterie();
    bool AreMaterie(const string &nume, int cantMin);
    void consumaMateriePunte(const string &nume,int cant);//am scris si aici o functie consuma deoarece trebuei sa am o punte intre player->materie pt ca in main in functia craft am ca parametru doar pointer player si functia cosuma este in materiePrima

                                                        
};
#endif