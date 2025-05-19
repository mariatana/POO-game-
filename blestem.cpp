#include "blestem.h"
#include "player.h"
#include <iostream>
Blestem:: Blestem(TipBlestemn tip, int intensitate): tip(tip), intensitate(intensitate){}
void Blestem:: scadeViata()
{
    player->scadeViata(intensitate);
}
void Blestem:: furaArma()
{
   player->scoateRandomInventar();

}
void Blestem:: declanseaza()
{
     if (tip == TipBlestem::VIATA) scadeViata();
    else if (tip == TipBlestem::FURAT_ARME) furaArma();
}