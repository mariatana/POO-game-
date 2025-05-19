#ifndef BLESTEM_H
#define BLESTEM_H
class Player;
class enum TipBlestem {VIATA, ARMA};
class Blestem{
    private:
    int intensitate;
    void furaArma();
    void scadeViata();
    void gameOverNoArme();
    public:
    Blestem(TipBlestem tip, int intenistate);
    void declanseaza();
}
#endif