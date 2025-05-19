#include "camera.h"
#include "cufar.h"

using namespace std;
Camera::Camera(int IdCamera,std::string Descriere, bool eMagazin,bool ismonster)
    :IdCamera(IdCamera),Descriere(Descriere),eMagazin(eMagazin),ismonster(ismonster){
        cufar=new Cufar(false);
    }
int Camera::getId() const
{
    return IdCamera;
}
std::string Camera:: getDescriere() const
{
    return Descriere;

}
bool Camera:: esteMagazin() const
{
    return eMagazin;
}
const vector<Camera*>& Camera:: getVecini() const
{
    return vecini;
}
const vector<Obiect*>& Camera:: getObiecte() const
{
    return obiecte;
}
void Camera:: adaugaObiect(Obiect* o)
{
    obiecte.push_back(o);
}
void Camera:: adaugaVecini(Camera *c)
{
    vecini.push_back(c);
}
void Camera::setInamic(Inamic *i)
{
    inamic=i;
}
Inamic* Camera::getInamic() const
{
    return inamic;
}
bool Camera ::emonstru() const
{
    return ismonster;
}
Cufar * Camera::getCufar() const
{
    return cufar;
}
Camera:: ~Camera()
{
    delete cufar;
}
