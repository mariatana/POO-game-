#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include "actor.h"
#include "camera.h"
#include "Obiect.h"
#include "potiune.h"
#include "materie.h"

class Inamic;
class Camera;
class Obiect;
class Potiune;
class Arma;
class MateriePrima;

class Player : public Actor {
private:
    int m_pocket;
    std::vector<Obiect*> m_inventar;
    Camera* m_curent_camera;
    Obiect* m_arma_curenta;
    static int m_monstri_batuti;
    std::map<std::string, MateriePrima> m_inventar_materii;
    int m_potiuni_folosite;

public:
    Player(int health, Camera* camera_start, int p);
    ~Player() override;

    void AdaugaObiect(Obiect* o);
    void AdaugaBani(int p);

    int getPocket() const;
    void ScadeBani(int p);
    void afiseazaLovitura() const override;
    void getStatus() const override;
    static void AdaugaMosntriBatuti();
    int getMonstriBatuti();
    Camera* getCamera() const;
    void SetCamera(Camera* new_camera);

    void afiseazaInventar() const;
    void schimbaArma(std::string nume);
    void seteazaArma(Obiect* arma);
    void folosestePotiune(Potiune* p);
    bool verificaDubluInventar(Obiect* obiect_primit);
    void furaRandomArma();
    int getNumarArme() const;
    int getPotiuniFolosite() const;
    Obiect* getArmaCurenta() const;
    void adaugaMateriePrima(MateriePrima* m);
    void afiseazaInventarMaterie();
    bool AreMaterie(const std::string& nume, int cant_min);
    void consumaMateriePunte(const std::string& nume, int cant);
};

#endif
