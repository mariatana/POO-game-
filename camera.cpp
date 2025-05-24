#include "camera.h"
#include "cufar.h"

using namespace std;

Camera::Camera(int id_camera, std::string descriere, bool e_magazin, bool e_monstru)
    : m_id_camera(id_camera), m_descriere(descriere),
      m_e_magazin(e_magazin), m_e_monstru(e_monstru) {
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

const vector<Camera*>& Camera::getVecini() const {
    return m_vecini;
}

const vector<Obiect*>& Camera::getObiecte() const {
    return m_obiecte;
}

void Camera::adaugaObiect(Obiect* o) {
    m_obiecte.push_back(o);
}

void Camera::adaugaVecini(Camera* c) {
    m_vecini.push_back(c);
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
}
