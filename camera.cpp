#include "camera.h"
#include "cufar.h"
#include "inamic.h"


Camera::Camera(int id_camera, std::string descriere, bool e_magazin, bool e_monstru)
    : m_id_camera(id_camera),
      m_descriere(std::move(descriere)), // Folosim std::move pentru eficienta (presupunand ca 'descriere' e un rvalue sau nu mai e necesar)
      m_e_magazin(e_magazin),
      m_e_monstru(e_monstru),
      m_inamic(nullptr) { 
    m_cufar = new Cufar(false);
}

int Camera::getId() const {
    return m_id_camera;
}

std::string Camera::getDescriere() const {
    return m_descriere;
}

bool Camera::esteMagazin() const {
    return m_e_magazin;
}

const std::vector<Camera*>& Camera::getVecini() const {
    return m_vecini;
}

const std::vector<Obiect*>& Camera::getObiecte() const {
    return m_obiecte;
}

void Camera::adaugaObiect(Obiect* o) {
    if (o) { // Buna practica sa verifici pointerul
        m_obiecte.push_back(o);
    }
}

void Camera::adaugaVecini(Camera* c) {
    if (c) { 
        m_vecini.push_back(c);
    }
}

void Camera::setInamic(Inamic* i) {

    m_inamic = i;
}

Inamic* Camera::getInamic() const {
    return m_inamic;
}

bool Camera::emonstru() const {
    return m_e_monstru;
}

Cufar* Camera::getCufar() const {
    return m_cufar;
}

Camera::~Camera() {
    delete m_cufar;
    m_cufar = nullptr; 
    delete m_inamic;  
    m_inamic = nullptr; 

}
