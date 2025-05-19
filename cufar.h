#ifndef CUFAR_H
#define CUFAR_H
#include <string>
#include "Obiect.h"
class Obiect;
class Cufar
{
  private:
  bool used;
  public:
  Cufar(bool used);
  ~Cufar();
  void folosesteCufar();
  bool getStateCufar() const;
  void schimbaStareCufar();



};
#endif