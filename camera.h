#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <vector>
#include <iostream>

class Inamic;
class Obiect;
class Cufar;

class Camera {
private:
    int m_id_camera;
    std::string m_descriere;
    std::vector<Obiect*> m_obiecte;
    std::vector<Camera*> m_vecini;
    Inamic* m_inamic;
    bool m_e_magazin;
    bool m_e_monstru;
    Cufar* m_cufar;

public:
    Camera(int id_camera, std::string descriere, bool e_magazin, bool e_monstru);
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
