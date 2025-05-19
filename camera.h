#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <vector>
#include <iostream>

class Inamic;
class Obiect;
class Cufar;
class Camera 
{
private:
    int IdCamera;
    std::string Descriere;
    std::vector<Obiect*> obiecte;
    std::vector<Camera*> vecini;
    Inamic* inamic;
    bool eMagazin;
    bool ismonster;
    Cufar *cufar;

public:
    Camera(int IdCamera, std::string Descriere, bool eMagazin,bool ismonster);
    
    int getId() const;
    std::string getDescriere() const;
    bool esteMagazin() const;

    void adaugaVecini(Camera* c);
    void adaugaObiect(Obiect* o);

    const std::vector<Camera*>& getVecini() const;
    const std::vector<Obiect*>& getObiecte() const;

    void setInamic(Inamic* i);
    Inamic* getInamic() const;
    Cufar* getCufar() const;
    ~Camera();
    bool emonstru() const;
};

#endif
