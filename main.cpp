#include <iostream>
#include <fstream>
#include <cstring>
#include "camera.h"
#include "inamic.h"
#include "actor.h"
#include "player.h"
#include "arma.h"
#include "Obiect.h"
#include "magazin.h"
#include "potiune.h"
#include "lupta.h"
#include "cufar.h"
#include <vector>
#include <sstream>
#include <limits>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

#include <ctime>
#include <map>
#include <algorithm>
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"


using namespace std;
//VECTORUL GLOBAL CU OBIECTE:
vector<Obiect*> obiecteGlobal;
vector<Camera*> camere;
int MonstriCamereInitial=0;
void afiseazaIntroducere() {
    cout << "You have high fever...\n";
    cout << "You are going deeper and deeper into deep sleep...\n";
    cout << "But no... something is wrong...\n";
    cout << "You woke up in a strange room... let's insepct the place.\n\n";
}
void afiseazaReguli() {
    cout << "\n========= RULES =========\n";
    cout << "-> Explore 10 dream-rooms.\n";
    cout << "-> Find helpful items (weapons, potions).\n";
    cout << "-> Defeat enemies using the items you find.\n";
    cout << "-> You cannot beat the strongest enemy unless you're well prepared!\n";
    cout << "-> You can teleport to the Shop at any time.\n";
    cout << "-> Survive the Fever Dream.\n";
    cout << "-> Always check your health!\n";
    cout<<"->Press Enter to return to main menu";

}
const int WIDTH = 7;
const int HEIGHT = 7;

char labirint[HEIGHT][WIDTH + 1] = {
    "#######",
    "#     #",
    "# ### #",
    "# # # #",
    "# # # #",
    "#   #E#",
    "#######"
};  //labirintul pt random event

int playerX = 1, playerY = 1; // poziția inițială

void afiseazaLabirint() {
    system("cls");  // șterge ecranul
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == playerX && y == playerY)
                std::cout << 'P';
            else
                std::cout << labirint[y][x];
        }
        std::cout << '\n';
    }
}

bool estePozitieValida(int x, int y) {
    return labirint[y][x] != '#';
}

void joacaLabirint(Player *player) {
    playerX = 1; playerY = 1; // reset poziția de început

    std::cout << "Ai intrat intr-un labirint misterios...\n";
    std::cout<<"Incearca sa iesi pt a primi 100 de bani"<<endl;
    std::cout<<"apasa q daca vrei sa renunti"<<endl;
    system("pause");

    while (true) {
        afiseazaLabirint();
        char tasta = _getch(); // citește tasta fără Enter

        int nouX = playerX, nouY = playerY;
        switch (tasta) {
            case 'w': nouY--; break;
            case 's': nouY++; break;
            case 'a': nouX--; break;
            case 'd': nouX++; break;
            case 'q': std::cout << "Ai renuntat la labirint.\n"; return;
        }

        if (estePozitieValida(nouX, nouY)) {
            playerX = nouX;
            playerY = nouY;
        }

        if (labirint[playerY][playerX] == 'E') {
            afiseazaLabirint();
            std::cout << " Ai iesit din labirint! Bravo!\n";
            cout<<"Ai primit 100 de bani"<<endl;
            player->AdaugaBani(100);
            break;
        }
    }
}
void testPOO(Player *player)
{
    cout<<"Completeaza acest quiz de OOP cu succes si vei primi 100 de bani"<<endl;
    cout<<"Ce folosim pt a avea polimorfism la executare?"<<endl;
    cout<<"1.Pointeri spre clasa de baza"<<endl;
    cout<<"2.Virtualizare"<<endl;
    cout<<"3.Referinte la toate clasele derivate"<<endl;
    int raspuns;
    switch(raspuns)
    {
        case 1:
        {
          cout<<"Ai pierdut...study more"<<endl;
        }
        case 2:
        {
          cout<<"FELICITARI! ai castigat!"<<endl;
        }
        case 3:
        {
            cout<<"Ai pierdut...study more"<<endl;
        }
    }
}
void declanseazaEvenimentRandom(Player *player)
{
    int tip=rand()%2;
    switch(tip)
    {
        case 1:
        {
        joacaLabirint(player);
        break;
        }
        case 2:
        {
        testPOO(player);
        break;
        }
        
    }
}

void creeazaObiecteGlobale(std::vector<Obiect*>& obiecteGlobal) {
    obiecteGlobal.push_back(new Arma(10, 3, "Sabie de Fier",0));
    obiecteGlobal.push_back(new Potiune(20, 2, "Apa vie", true,0));
    obiecteGlobal.push_back(new Arma(15, 2, "Topor Viking",0));
    obiecteGlobal.push_back(new Potiune(10,3 , "Potiune de Viata light", true,0));
    obiecteGlobal.push_back(new Potiune(30, 2, "Potiune Norocoasa", true,0));
    obiecteGlobal.push_back(new Arma(20, 2, "katana",0));
    obiecteGlobal.push_back(new Arma(30, 1, "pistol",0));
    obiecteGlobal.push_back(new Potiune(10, 1, "Potiune Blestemata", false,0));
    obiecteGlobal.push_back(new Potiune(10, 1, "Leacul spiridusului", true,0));

   
}
Obiect* daObiectRandom(Player* player, const std::vector<Obiect*>& obiecteGlobal) {
    if (obiecteGlobal.empty()) return nullptr;
    // Creează o listă cu probabilități inverse proporționale cu raritatea
        vector<Obiect*> pool;
    for (Obiect* o : obiecteGlobal) {
    for (int i = 0; i < (6 - o->getRaritate()); ++i) {
        pool.push_back(o);
                                                     }
                                 }
        int index = rand() % pool.size();
        Obiect* obj = pool[index]->clone();
        return obj;

}
vector<Camera*> CreareHarta(const string& NumeFisier) {
    ifstream fin(NumeFisier);
    vector<Camera*> camere;
    map<int, Camera*> mapaCamere;

    if (!fin) {
        cerr << "Eroare la deschiderea fisierului!\n";
        return camere;
    }

    string linie;

    // 1. Creăm camerele și le punem în mapă
    while (getline(fin, linie)) {
        if (linie.empty()) continue;

        stringstream ss(linie);
        int idc, areInamic;
        string descriere;

        ss >> idc >> descriere >> areInamic;
        Camera* c;
        if (descriere == "Shop")
            c = new Camera(idc, descriere, true, areInamic);
        else 
            c = new Camera(idc, descriere, false, areInamic);
        camere.push_back(c);
        mapaCamere[idc] = c;
    }

    // 2. Revin la începutul fișierului pentru a adăuga vecinii
    fin.clear();
    fin.seekg(0, ios::beg);

    while (getline(fin, linie)) {
        if (linie.empty()) continue;

        stringstream ss(linie);
        int idc, areInamic;
        string descriere;

        ss >> idc >> descriere >> areInamic;

        Camera* cameraCurenta = mapaCamere[idc];

        int idVecin;
        while (ss >> idVecin) {
            auto it = mapaCamere.find(idVecin);
            if (it != mapaCamere.end()) {
                cameraCurenta->adaugaVecini(it->second);
             
            } else {
                cerr << "Atenție: Vecinul cu id " << idVecin << " nu există pentru camera " << idc << "!\n";
            }
        }
    }
    creeazaObiecteGlobale(obiecteGlobal);

    return camere;
}



void adaugaInamiciCamere(vector<Camera*>&camere)
{
    for (Camera* c : camere) {
         
        
        if (!c->emonstru()) {
            continue;
        }

        // În funcție de ID, atribuim un monstru specific
        if (c->getId()== 2) {
            c->setInamic(new Inamic(18,3, 6, "Clicker"));
        } else if ( c->getId()== 3) {
            c->setInamic(new Inamic(30,5, 9, "Pyramid Head"));
        } else if (c->getId() == 4) {
            c->setInamic(new Inamic(45,6, 10, "Slender Man"));
        } else if (c->getId() == 5) {
            c->setInamic(new Inamic(60,7, 12, "Taz"));
        } 
        else if (c->getId() == 6) {
            c->setInamic(new Inamic(80,8, 14, "Scorpion King"));
        } else if (c->getId() == 7) {
            c->setInamic(new Inamic(100,10, 16, "Nemesis"));
        } else if (c->getId() == 8) {
            c->setInamic(new Inamic(140,12, 20, "Hydra"));
        }
        MonstriCamereInitial++;
       
    }
    
}
void afiseazaFisierASCII(const string& numeFisier) {
    ifstream fin(numeFisier);
    if (!fin) {
        cerr << "Eroare la deschiderea fisierului " << numeFisier << "!\n";
        return;
    }

    string linie;
    while (getline(fin, linie)) {
        cout << linie << endl;
    }

    fin.close();
}
#include <map>

// returnează numele fișierului ASCII pe baza numelui inamicului
string obtineFisierASCII(const string& numeInamic) {
    map<string, string> hartaFisiere = {//asociere numele fisierului->numele inamicului
        {"Clicker", "clicker.txt"},
        {"Pyramid Head", "ascii_pyramidhead.txt"},
        {"Slender Man", "ascii_slenderman.txt"},
        {"Taz", "taz.txt"},
        {"Scorpion King", "scorpion.txt"},
        {"Nemesis", "nemesis.txt"},
        {"Hydra", "hydra.txt"}
    };

    auto it = hartaFisiere.find(numeInamic);//cautam cheia (nume inamic) in mapa
    if (it != hartaFisiere.end()) {
        return it->second;
    } else {
        return ""; // fallback dacă nu există fișier
    }
}

int TotalMonstriCamere()
{
    int total=0;
    for(Camera *c:camere)
    {
        if(c->getInamic()!=nullptr)
        total=total+1;

    }
    return total;
}
void afiseazaharta() {
    cout << "\n============ HARTA FEVER DREAM ============\n\n";

    cout << "              [3] PyramidHead\n";
    cout << "                   |\n";
    cout << "[1] Start -> [2] Clicker's -> [5] Taz ->[6] Scorpion\n";
    cout << "                   |                    |\n";
    cout << "              [4] SlenderMan         [7] Nemesis\n";
    cout << "                                         |\n";
    cout << "                                     [8] Hydra\n";

    cout << "\n===========================================\n";
}

void asteaptaEnter() {
    cout << "\nApasa Enter pentru a reveni la meniu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // golire buffer
    cin.get(); // așteaptă Enter
}

using namespace std;
int main()
{
    srand(time(0));
  //asigur ca nu se vor da mereu aceleasi obiecte 
  
    
    int optiune1;
    bool ruleaza=true;
    afiseazaIntroducere();
    while(ruleaza)
    {
       
        cout << "========= FEVER DREAM =========\n";
        cout << "1. Play Game\n";
        cout << "2. See Rules\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> optiune1;
        cin.ignore(); // curăță '\n' din buffer
        switch(optiune1)
        {
            case 1:
            {
            cout<<"Good luck to get out..(evil laugh haha)"<<endl;
            camere=CreareHarta("harta.txt");
            adaugaInamiciCamere(camere);
            if(camere.empty())
            cout<<"eroare incarcare harta"<<endl;
            else
            {
             cout<<"Harta a fost incarcata cu succes"<<endl;
             for (Camera* c : camere) {
                if (c != nullptr && c->getId() != 1 && c->getId()!=9 && c->getInamic() != nullptr) {
                    cout << "Camera " << c->getId() << " cu inamicul " << c->getInamic()->getName() << endl;
                }
            }
            
            ruleaza=false;
            break;
        }
            case 2:
            {
                afiseazaReguli();
            cout<<"Apasa ENTER pentru a reveni la meniu"<<endl;
            cin.get();
            break;
            }
            case 3:
            cout<<"Exiting Fever Dream..."<<endl;
            ruleaza=false;
            break;
            default:
            cout<<"Invalid Option.Try again"<<endl;



        }
    }
}
  
    
    Camera* startCamera = camere[0]; // presupunem că prima cameră e camera de start
    Player* player = new Player(20,startCamera, 0); // 0 bani la început
    Camera* cameraCurenta = startCamera;
    
   

    Obiect* sabie = new Arma(10, 1, "Sabie de start",0); // damage 10, raritate 1
    //! setare arma 
    player->AdaugaObiect(sabie);
    int optiune2;
    bool IntrareCamera=true;
    int alegecamera;

    cout<<"===START ROOM==="<<endl;
    cout<<"Te afli in prima camera"<<endl;
    cout<<"================"<<endl;
    while(IntrareCamera)
    {
        cout<<RED<<"1.Inspecteaza cufar"<<RESET<<endl;
        cout<<RED<<"2.Vezi harta"<<RESET<<endl;
        cout<<RED<<"3.Alege camera in care vrei sa mergi"<<RESET<<endl;
        cout<<RED<<"4.Du-te la magazin"<<RESET<<endl;
        cout<<RED<<"5.Inspecteza inventar"<<RESET<<endl;
        cout<<RED<<"6.Verifica sanatate"<<RESET<<endl;
        cout<<RED<<"7.Renunta"<<RESET<<endl;
        //asta separat de meniu as vrea sa am un random event care sa aiba cumva mostenire multipla 
        cin >> optiune2;
        cin.ignore();

        switch(optiune2)
        {
            case 1:
            {
                if(cameraCurenta->getInamic()!=nullptr)
                {
                    if(cameraCurenta->getId()!=1)
                        cout<<"Nu poti deschide cufarul fara sa bati monstrul!"<<endl;
                    else
                        cout<<"Ghinion...cufarul este gol!"<<endl;
                        cout<<"Apasa ENTER pentru a te intoarce la meniu.."<<endl;
                        cin.get();
                }
                
                //daca nu mai e inamic, dar inca mai e cufar
               else if(cameraCurenta->getInamic()==nullptr&&cameraCurenta->getCufar()->getStateCufar()==false)
                {
                    cout<<"Vrei sa deschizi cufarul?"<<endl;
                    cout<<"1.DA"<<endl;
                    cout<<"2.NU"<<endl;
                    int raspunsCufar2;
                    cin>>raspunsCufar2;
                    switch(raspunsCufar2)
                    {
                        case 1:
                        {
                            cameraCurenta->getCufar()->folosesteCufar();
                            cout << "Inspectezi cufarul..." << endl;
                            Obiect *obiectPrimit=daObiectRandom(player,obiecteGlobal);
                            cout<<"Felicitari!ai primit: "<<*obiectPrimit<<endl;
                            if(player->verificaDubluInventar(obiectPrimit)==true)
                               player->AdaugaObiect(obiectPrimit);//pt a nu a adauga in inevntar de 2 ori

                            player->afiseazaInventar(); // Vezi ce ai în inventar
                            cameraCurenta->getCufar()->schimbaStareCufar();//schimb starea cufarului la folosit
                           cout<<"Apasa ENTER pentru a te intoarce la meniu.."<<endl;
                           cin.get();
                            break;
                        }
                        case 2:
                        {
                            cout<<"Apasa ENTER pentru a te intoarce la meniu.."<<endl;
                           cin.get();
                            break;
                        }
                    }
                }
                else
                cout<<"Ai invins monstrul si nu mai este niciun cufar in camera!"<<endl;
                break;
            }
            case 2:
            {
                afiseazaharta();
                cout<<"Apasa ENTER pentru a te intoarce la meniu"<<endl;
                cin.get();
                break;
            }
            case 3:
            {
                cout<<"Alege camera"<<endl;
                cout << "Camerele vecine disponibile sunt: ";
                //for care merge prin vecinii camerei curente
                for (auto vecin : cameraCurenta->getVecini()) {
                    cout << vecin->getId() << " (" << vecin->getDescriere() << ") ";
                                                              }
                cin>>alegecamera;
                bool gasit=false;
                bool murit=false;
                bool ok=false;//verifica daca am luat vecinii bine
               for(Camera* c :cameraCurenta->getVecini())
                 if (c->getId()==alegecamera)
                 {
                  cameraCurenta=c;
                  ok=true;
                  player->SetCamera(cameraCurenta);
                  gasit=true;
                  break;
                 }
                 if(ok==false)
                 {
                    cout<<"Vecin invalid!"<<endl;
                    asteaptaEnter();
                 }
                 else
                 {
                 cout<<"==Ai intrat in camera=="<<cameraCurenta->getDescriere()<<endl;

                 //cazul in care nu am invins inamicul din camera=> am si cufar in camera (caz 1)
                 if(cameraCurenta->getId()!=1&&cameraCurenta->getInamic()!=nullptr)
                 {
                     cout<<"==Inamicul:=="<<cameraCurenta->getInamic()->getName()<<endl;
                     string numeInamic = cameraCurenta->getInamic()->getName();
                     string fisierASCII = obtineFisierASCII(numeInamic);
                     if (!fisierASCII.empty()) {
                    afiseazaFisierASCII(fisierASCII);
                            }               else {
                     cout << "Nu exista desen pentru acest inamic.\n";
                             }
                     if(cameraCurenta->getInamic()->getMinimDamage()>player->getHealth())
                        cout<<"Esti sigur ca vrei sa lupti? ATENTIE! ACEST INAMIC ARE MINIM DAMAGE "<<cameraCurenta->getInamic()->getMinimDamage()<<"si tu ai "<<player->getHealth()<<" sanatate"<<endl;
                     cout<<"Esti sigur ca vrei sa lupti?"<<endl;
                     cout<<"1.DA"<<endl;
                     cout<<"2.NU"<<endl;
                     int raspunslupta;
                     cin>>raspunslupta;
                     cin.ignore();
                     if(raspunslupta==1)
                     {
                     Lupta lupta(player, cameraCurenta->getInamic());
                     bool castigator = lupta.start();
                     if (castigator) {
                         int BaniCastigati=cameraCurenta->getInamic()->randomMoney();//se adauga bani in functie de boss ul omorat
                         player->AdaugaBani(BaniCastigati);
                         Obiect *obiectPrimit= daObiectRandom(player, obiecteGlobal);
                       
                         //daca e potiune, o folosesc indiferent
                          Player::AdaugaMosntriBatuti();
                
                         //afisare comeback
                         cout << "Ai invins inamicul!"<<" Ai primit "<<BaniCastigati<<" bani si un obiect: "<<obiectPrimit->getNume()<< endl;
                         if(player->getMonstriBatuti()==MonstriCamereInitial)
                         {
                            cout<<"FELICITARI!AI CASTIGAT! AI INVINS TOTI MONSTRI!"<<endl;
                            cout<<"In curand o sa te trezesti..."<<endl;
                            cout<<"In lumea monstrilor adevarati...omenirea"<<endl;
                            IntrareCamera=false;
                         }
                         Potiune *potiune=dynamic_cast<Potiune*>(obiectPrimit);//urmeaza sa vad daca obiectul este potiune
                         if(potiune)
                         {
                            player->folosestePotiune(potiune);
                            if(player->getHealth()<=0)
                            {
                                cout<<"Ai murit. Game Over"<<endl;
                                exit(0);
                            }
                         }
                         else
                         if(!potiune)
                         {
                            if(player->verificaDubluInventar(obiectPrimit)==true)
                            player->AdaugaObiect(obiectPrimit);
                         }
                         player->afiseazaInventar();
                         delete cameraCurenta->getInamic();
                         cameraCurenta->setInamic(nullptr);//setam inamicul la null
                         
                         //--mecanica folosirii cufarului---
                         cout<<"Felicitari...ai invins..uite un cufar, il deschizi?"<<endl;
                         cout<<"1.DA"<<endl;
                         cout<<"2.NU"<<endl;
                         int raspunsCufar;
                         cin>>raspunsCufar;
                         cin.ignore();
                         switch(raspunsCufar)
                         {
                            case 1:
                            {
                            cameraCurenta->getCufar()->schimbaStareCufar();

                            cout << "Inspectezi cufarul..." << endl;
                            Obiect *obiectPrimit=daObiectRandom(player,obiecteGlobal);
                            Potiune *potiune=dynamic_cast<Potiune*>(obiectPrimit);//urmeaza sa vad daca obiectul este potiune
                            cout<<"Felicitari!ai primit: "<<*obiectPrimit<<endl;
                            if(potiune)
                            {
                                player->folosestePotiune(potiune);
                                if(player->getHealth()<=0)
                                {
                                    cout<<"Ai murit. Game Over"<<endl;
                                    exit(0);
                                }
                            }
                            else
                            { 
                                if(player->verificaDubluInventar(obiectPrimit))
                                player->AdaugaObiect(obiectPrimit);
                            }
                            player->afiseazaInventar(); // Vezi ce ai în inventar
                            cameraCurenta->getCufar()->schimbaStareCufar();//schimb starea cufarului la folosit
                           
                            break;
                            }
                            case 2:
                            {
                                
                                break;
                            }
                         }
                         
                        int sansa = rand() % 100; // dă un număr între 0 și 99
                        if (sansa < 40) {
                            declanseazaEvenimentRandom(player);
                        }
                     else {
                         cout << "Ai murit! Game over.\n";
                         exit(0);
                          }//aici!
                        }
                        else
                        {
                            cout<<"E ok..keep going..poate alt inamic e potrivit pentru tine"<<endl;
                            cout<<"Apasa ENTER pentru a reveni la meniu"<<endl;
                            cin.get();

                        }
                        }
                        else
                          if(cameraCurenta->getInamic()==nullptr&&cameraCurenta->getCufar()->getStateCufar()==false)
                            cout<<"hmmm..inca e un cufar aici"<<endl;
                          else
                             cout<<"se pare ca nu mai este nimic interesant in aceasta camera"<<endl;
                            if(cameraCurenta->getId()==1)
                            {
                                cout<<"Nimic interesant de vazut aici...continua aventura in celelalte camere"<<endl;
                                asteaptaEnter();
                                break;
                            }
                        

                 }
                 asteaptaEnter();
                break;

            }
            case 4:
            {
            cout<<"===Bine ai venit la magazin==="<<endl;
            Camera *cameraCurenta=camere[8];
            player->SetCamera(cameraCurenta);
            //de pus separat obiectele in magazin
            Magazin magazin;
            magazin.adaugaObiect(new Arma(10, 2, "Katana",20));
            magazin.adaugaObiect(new Potiune(15, 1, "Potiune Super Heal", true,50));
            magazin.adaugaObiect(new Arma(80,1,"finisher",50));
            magazin.adaugaObiect(new Arma(20,2,"Toxic Fume",40));
            cout << "Lista de obiecte pe care le poti cumpara: "<<endl;
            magazin.afiseazaStoc();
            cout<<"Momentan ai: "<<player->getPocket()<<" bani"<<endl;
            cout<<"Vrei sa cumperi ceva?"<<endl;
            cout<<"1.Da"<<endl;
            cout<<"2.NU"<<endl;
            int raspunsMagazin;
            cin>>raspunsMagazin;
            if(raspunsMagazin==1)
            {
                // daca cumpar o potiune intra in stoc! de schimbat putin mecanica folosirii armelor ca sa pot sa utilizez si potiune SAU cand o cumpar o folosesc instant
            magazin.afiseazaStoc();
            cout<<"Scrie indexul obiectului pe care il doresti"<<endl;
            int index;
            cin >> index;
            Obiect* cumparat = magazin.cumparaObiect(index, player);
            if (cumparat) {
                Potiune *potiune=dynamic_cast<Potiune*>(cumparat);
                if(potiune)
                {
                    player->folosestePotiune(potiune);
                
                }
                else
                player->AdaugaObiect(cumparat);
            }
        }
        else
        {
            asteaptaEnter();
            break;
            
        }
            asteaptaEnter();
            break;
            }
            case 5:
            {
                player->afiseazaInventar();
                cout<<"Arma curenta: "<<player->getArmaCurenta()->getNume()<<endl;
                cout<<"Doresti sa schimbi arma?"<<endl;
                cout<<"1.DA"<<endl;
                cout<<"2.NU"<<endl;
                int optiuneArma;
                cin>>optiuneArma;
                cin.ignore();
                switch(optiuneArma)
                {
                    case 1:
                    {
                        player->afiseazaInventar();
                        cout<<"Scrieti numele armei cu care vreti sa schimbati "<<player->getArmaCurenta()->getNume()<<endl;
                        string numeArma;
                       
                        getline(cin, numeArma); // citește tot, inclusiv spații
                          
                        player->schimbaArma(numeArma);
                        cout<<player->getArmaCurenta()->getNume()<<endl;
                        cout<<"Apasa Enter pentru a te intoarce la meniu"<<endl;
                        cin.get();
                        break;
                    }
                
                   case 2:
                   {
                    cout<<"Apasa Enter pentru a te intoarce la meniu"<<endl;
                   cin.get();
                    break;
                   }
                }
               
               
                break;
                  
            }
            case 6:
            {
                player->getStatus();
                cin.get();
                break;
            }
            case 7:
            {
                
            cout<<"Proasta alegere..nu ai curaj..poate ca nu te vei mai trezi niciodata..";
            exit(0);
            }
        }
    }
   
   ///! evenimente random 
   /// stand by cand se lupta(ceva pt suspans-eventaul functie windows)
   ///*extra: text color+sunete; la final achivmenturile
    return 0;




}