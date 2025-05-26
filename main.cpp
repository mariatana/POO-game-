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
#include "npc.h"
#include "materie.h"

#include <map>
#include <vector>
#include <sstream>
#include <chrono>
#include <thread>
#include <limits>
#include <cstdlib>
#include <map>
#include <algorithm>
using namespace std;
//VECTORUL GLOBAL CU OBIECTE:
vector<Obiect*> obiecte_global;
//VECTORUL GLOBAL DE CAMERE
vector<Camera*> camere;
//VECTOR GLOBAL MATERII PRIME
vector <MateriePrima*> materii;
int monstri_camere_initial=0;
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


void creeazaObiecteGlobale(std::vector<Obiect*>& obiecte_global) {
    //pun obiectele din vector
    obiecte_global.push_back(new Arma(10, 3, "Sabie de Fier",0));
    obiecte_global.push_back(new Potiune(20, 2, "Apa vie", true,0));
    obiecte_global.push_back(new Arma(15, 2, "Topor Viking",0));
    obiecte_global.push_back(new Potiune(10,3 , "Potiune de Viata light", true,0));
    obiecte_global.push_back(new Potiune(30, 2, "Potiune Norocoasa", true,0));
    obiecte_global.push_back(new Arma(20, 2, "katana",0));
    obiecte_global.push_back(new Arma(30, 1, "pistol",0));
    obiecte_global.push_back(new Potiune(40, 1, "Potiune Blestemata", false,0));
    obiecte_global.push_back(new Potiune(40, 1, "Leacul spiridusului", true,0));
    obiecte_global.push_back(new Arma(37, 1, "DragonBall",0));
    obiecte_global.push_back(new Arma(19, 1, "HalBerd",0));
    obiecte_global.push_back(new Arma(37, 1, "Claymore",0));//sabie mare:) referinta Dark
     obiecte_global.push_back(new Potiune(39, 2, "fairyheal", true,0));
    obiecte_global.push_back(new Arma(16, 1, "Daggar",0));
    obiecte_global.push_back(new Potiune(18, 2, "WitchBreath", false,0));
    obiecte_global.push_back(new Arma(37, 1, "Claymore",0));
    obiecte_global.push_back(new Arma(33, 1, "zweihander",0));
    obiecte_global.push_back(new Arma(25, 1, "scythe",0));
   
}
Obiect* daObiectRandom(Player* player, const std::vector<Obiect*>& obiecte_global) {
    if (obiecte_global.empty()) return nullptr;
    // Creează o listă cu probabilități inverse proporționale cu raritatea
    vector<Obiect*> pool;
    for (Obiect* o : obiecte_global) {

    for (int i = 0; i < (6 - o->getRaritate()); ++i) 
        {
        pool.push_back(o);
        }
                                     }
        //se ia un index random din vector
        int index = rand() % pool.size();
        Obiect* obj = pool[index]->clone();
        return obj;

}

void creeazaMaterialeGlobale(std::vector<MateriePrima*>& materii)
{
    //pun materialele in vectorul global
    materii.push_back(new MateriePrima("osDragon",2));
    materii.push_back(new MateriePrima("infinitefire",1));
    materii.push_back(new MateriePrima("poison",3));
    materii.push_back(new MateriePrima("poison",2));
    materii.push_back(new MateriePrima("blades",4));
    materii.push_back(new MateriePrima("poisonflower",2));
    materii.push_back(new MateriePrima("blades",1));
    materii.push_back(new MateriePrima("infinitefire",2));
    materii.push_back(new MateriePrima("osDragon",3));
    materii.push_back(new MateriePrima("blades",1));

}
void AdaugaMagazin(Magazin &magazin)
{
 magazin.adaugaObiect(new Arma(20, 2, "Katana",20));
 magazin.adaugaObiect(new Potiune(30, 1, "Potiune Super Heal", true,50));
 magazin.adaugaObiect(new Potiune(30, 1, "axe", true,15));
 magazin.adaugaObiect(new Potiune(35, 1, "sulita", true,34));
}
MateriePrima* daMaterieRandom(Player* player, const std::vector<MateriePrima*>& materii) {
    //algoritm pt a primi materie random
    if (materii.empty()) return nullptr;
    int index_random = std::rand() % materii.size();
    return materii[index_random];
}
vector<Camera*> CreareHarta(const string& nume_fisier) {
    ifstream fin(nume_fisier);
    vector<Camera*> camere;
    map<int, Camera*> mapa_camere;
    if (!fin) {
        cerr << "Eroare la deschiderea fisierului!\n";
        return camere;
    }
    string linie;
    // 1. Creăm camerele și le punem în mapă
    while (getline(fin, linie)) {
        if (linie.empty()) continue;
        stringstream ss(linie);
        int idc, are_inamic;
        string descriere;
        ss >> idc >> descriere >> are_inamic;
        Camera* c;
        if (descriere == "Shop")
            c = new Camera(idc, descriere, true, are_inamic);
        else 
            c = new Camera(idc, descriere, false, are_inamic);
        camere.push_back(c);
        mapa_camere[idc] = c;
        //am folosit map -> fiecare camera are asociat un id
    }

    // 2. Revin la începutul fișierului pentru a adăuga vecinii
    fin.clear();
    fin.seekg(0, ios::beg);

    while (getline(fin, linie)) {
        if (linie.empty()) continue;
        stringstream ss(linie);
        int idc, are_inamic;
        string descriere;
        //citesc din nou
        ss >> idc >> descriere >> are_inamic;
        //iau cammera curenta
        Camera* camera_curenta = mapa_camere[idc];
        int idVecin;
        //citesc vecinii
        while (ss >> idVecin) {
            //caut dupa cheie(id)
            auto it = mapa_camere.find(idVecin);
            if (it != mapa_camere.end()) {
                //adaug vecinii( dupa valoare care este Camera* )
                camera_curenta->adaugaVecini(it->second);
             
            } else {
                cerr << "Atenție: Vecinul cu id " << idVecin << " nu există pentru camera " << idc << "!\n";
            }
        }
                               }
    //dupa ce am creat harta, pun obiectele in vectorul global
    creeazaObiecteGlobale(obiecte_global);
    //pun si materialele
    creeazaMaterialeGlobale(materii);

    return camere;
}



void adaugaInamiciCamere(vector<Camera*>&camere)
{
    for (Camera* c : camere) {
         
        if (!c->emonstru()) {
            //daca nu am monstru in camera
            continue;
        }
        // În funcție de ID, atribuim un monstru specific
        if (c->getId()== 2) {
            c->setInamic(new Inamic(10,3, 6, "Clicker"));
        } else if ( c->getId()== 3) {
            c->setInamic(new Inamic(15,5, 9, "Pyramid Head"));
        } else if (c->getId() == 4) {
            c->setInamic(new Inamic(35,6, 10, "Slender Man"));
        } else if (c->getId() == 5) {
            c->setInamic(new Inamic(49,7, 12, "Taz"));
        } 
        else if (c->getId() == 6) {
            c->setInamic(new Inamic(60,8, 14, "Scorpion King"));
        } else if (c->getId() == 7) {
            c->setInamic(new Inamic(68,10, 16, "Nemesis"));
        } else if (c->getId() == 8) {
            c->setInamic(new Inamic(90,12, 20, "Hydra"));
        }
        else if (c->getId() == 9) {
            c->setInamic(new Inamic(110,16, 25, "ItClown"));
        }
        else if (c->getId() == 10) {
            c->setInamic(new Inamic(120,20, 30, "Annabele"));
        }
        else if (c->getId() == 11) {
            c->setInamic(new Inamic(130,30, 40, "Fourkings"));
        }
        monstri_camere_initial++;
       
    }
    
}


void afiseazaFisierASCII(const string& nume_fisier) {
    //functia afiseaza desenele din caractere ascii
    ifstream fin(nume_fisier);
    if (!fin) {
        cerr << "Eroare la deschiderea fisierului " << nume_fisier << "!\n";
        return;
    }

    string linie;
    while (getline(fin, linie)) {
        cout << linie << endl;
    }

    fin.close();
}


// returnează numele fișierului ASCII pe baza numelui inamicului
string obtineFisierASCII(const string& nume_inamic) {
    map<string, string> hartaFisiere = {//asociere numele fisierului->numele inamicului
        {"Clicker", "clicker.txt"},
        {"Pyramid Head", "ascii_pyramidhead.txt"},
        {"Slender Man", "ascii_slenderman.txt"},
        {"Taz", "taz.txt"},
        {"Scorpion King", "scorpion.txt"},
        {"Nemesis", "nemesis.txt"},
        {"Hydra", "hydra.txt"}
    };

    auto it = hartaFisiere.find(nume_inamic);//cautam cheia (nume inamic) in mapa
    if (it != hartaFisiere.end()) {
        //returnam valoarea(fisierul)
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
        //daca gasim monsru in camera il adaugam la total
        if(c->getInamic()!=nullptr)
        total=total+1;

    }
    return total;
}


void afiseazaharta() {
    cout << "\n============ HARTA FEVER DREAM ============\n\n";

    cout << "              [3] PyramidHead -> [4]SlenderMan -> -> -> ->  \n";
    cout << "                  |               |                        |\n";          
    cout << "[1] Start -> [2] Clicker's ->    [5] Taz ->[6] Scorpion -> [7]Nemesis\n";
    cout << " |\n";                        
    cout << "[10]Annabele                            |                |\n";                                         
    cout << "  |\n";                                        
    cout << "[11]fourKings -> -> -> -> -> -> -> ->  [9] ITclown   -> [8]Hydra\n ";

    cout << "\n===========================================\n";
}
void efectCrafting() {
    //functie pentru efect tip loading
    cout << "\nCrafting";
    cout.flush(); // forțează afișarea imediată
    for (int i = 0; i < 3; ++i) {
        this_thread::sleep_for(std::chrono::seconds(1));
        cout << ".";
        cout.flush();
    }
    this_thread::sleep_for(std::chrono::seconds(1));
    cout << "\n";
}
void craft(Player *p)
{
    bool crafting =true;
    while(crafting)
    {
    cout<<"Retete disponibile: "<<endl;
    cout<<"1.PoisonBlades (1 blades, 2 posisonFlower, 4 poison )"<<endl;
    cout<<"2.SuperOsDragon (2 oase de dragon)"<<endl;
    cout<<"3.Revino la meniul principal"<<endl;
    cout<<"Alege optiunea : "<<endl;
    int op;
    cin>>op;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch(op)
    {
        case 1:
        {
            //daca are materialele necesare se vor scoate din inventar si se creaza noua arma
            if(p->AreMaterie("blades",1)&&p->AreMaterie("poisonflower",2)&&p->AreMaterie("poison",4))
            {
                
                p->consumaMateriePunte("blades",1);
                p->consumaMateriePunte("poisonflower",2);
                p->consumaMateriePunte("poison",4);
                p->AdaugaObiect(new Arma(30,1,"PoisonBlades",0));
                efectCrafting();
                cout<<"Ai craftat PoisonBlades"<<endl;
            }
            else
            cout<<"Nu ai suficienta materie prima"<<endl;
            cout<<"Enter pentru a reveni la crafting table"<<endl;
            cin.get();
            break;
        }
        case 2:
        { 
            //overload pe operatorul +, se creaza o arma din doua obiecte identice
             if(p->AreMaterie("osDragon",2))
             {
                 p->consumaMateriePunte("osDragon",2);
                 MateriePrima m1("osDragon", 1);
                 MateriePrima m2("osDragon", 1);
                 MateriePrima rezultat = m1 + m2;
                 Obiect* n = new Arma(25, 1, rezultat.getNume(), 0); // sau alt tip
                 p->AdaugaObiect(n);
                 efectCrafting();
                cout<<"Ai craftat osDragon"<<endl;
             }
             else
               cout<<"Nu ai suficienta materie prima"<<endl;
            cout<<"Enter pentru a reveni la crafting table"<<endl;
            cin.get();
            break;
        }
        case 3:
        {
            crafting=false;
            break;
        }
       crafting=false;
    }
}

}

void asteaptaEnter() {
    //functie pentru revebire la meniu
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
            //se creaza harta si se adauga inamicii
            camere=CreareHarta("harta.txt");
            adaugaInamiciCamere(camere);
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
            {
            cout<<"Exiting Fever Dream..."<<endl;
            ruleaza=false;
            break;
            }
            default:
            cout<<"Invalid Option.Try again"<<endl;



        }
    }

    Camera* start_camera = camere[0]; // presupunem că prima cameră e camera de start
    Player* player = new Player(20,start_camera, 0); // 0 bani la început
    Camera* camera_curenta = start_camera; //camera curanta este camera de start
    Obiect* sabie = new Arma(10, 1, "Sabie de start",0); // damage 10, raritate 1
    player->AdaugaObiect(sabie);//setare arma 
    int optiune2;
    bool intrare_camera=true;
    int alege_camera;
    cout<<"===START ROOM==="<<endl;
    cout<<"Te afli in prima camera"<<endl;
    cout<<"================"<<endl;
    //mecanica folosirii unui struct 
    NpcInfo batranul = {"Batranul Intelept", "Sa nu ai incredere in Clicker.", true};
    NPC npc1(batranul);
    npc1.Interacționeaza(player);//activare NPC
    while(intrare_camera)
    {
        cout<<"1.Inspecteaza cufar"<<endl;
        cout<<"2.Vezi harta"<<endl;
        cout<<"3.Alege camera in care vrei sa mergi"<<endl;
        cout<<"4.Du-te la magazin"<<endl;
        cout<<"5.Inspecteza inventar arme"<<endl;
        cout<<"6.Verifica sanatate"<<endl;
        cout<<"7.Renunta"<<endl;
        cout<<"8.Inspecteaza inventar materie prima"<<endl;
        cout<<"9.Crafteaza"<<endl; 
        cin >> optiune2;
        cin.ignore();
        switch(optiune2)
        {
            case 1:
            {
                //daca am monstru in camera sunt doua posibilitati : fie e camera de start si nu am monstru, fie inca nu l am batut
                //(logica jocului este ca pot deschide cufarul doar dupa ce am invins mosntrul)
                if(camera_curenta->getInamic()!=nullptr)
                {
                    if(camera_curenta->getId()!=1)
                        cout<<"Nu poti deschide cufarul fara sa bati monstrul!"<<endl;
                    else
                        cout<<"Ghinion...cufarul este gol!"<<endl;
                        cout<<"Apasa ENTER pentru a te intoarce la meniu.."<<endl;
                        cin.get();
                }

                //daca nu mai e inamic, dar inca mai e cufar
                else if(camera_curenta->getInamic()==nullptr&&camera_curenta->getCufar()->getStateCufar()==false)
                {
                    cout<<"Vrei sa deschizi cufarul?"<<endl;
                    cout<<"1.DA"<<endl;
                    cout<<"1.NU"<<endl;
                    int raspuns_cufar_2;
                    cin>>raspuns_cufar_2;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    switch(raspuns_cufar_2)
                    {
                        case 1:
                        {
                            //se deschide cufarul si se adauga obiectul primit in inventar
                            camera_curenta->getCufar()->folosesteCufar();
                            cout << "Inspectezi cufarul..." << endl;
                            Obiect *obiectPrimit=daObiectRandom(player,obiecte_global);
                            cout<<"Felicitari!ai primit: "<<*obiectPrimit<<endl;
                            player->AdaugaObiect(obiectPrimit);
                            player->afiseazaInventar(); // Vezi ce ai în inventar
                            camera_curenta->getCufar()->schimbaStareCufar();//schimb starea cufarului la folosit
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
                        break;
                    }
                }
                    else
                    {
                        //cazul in care am invins monstrul si nici nu mai este vreun cufar
                         cout<<"Ai invins monstrul si nu mai este niciun cufar in camera!"<<endl;
                         cout<<"Apasa ENTER pentru a te intoarce la meniu.."<<endl;
                         cin.get();
                         break;
                    }
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
                for (auto vecin : camera_curenta->getVecini()) {
                    cout << vecin->getId() << " (" << vecin->getDescriere() << ") ";}                                                  
                cin>>alege_camera;
                bool gasit=false;
                bool murit=false;
                bool ok=false;//verifica daca am luat vecinii bine

                for(Camera* c :camera_curenta->getVecini())
                 if (c->getId()==alege_camera)
                 {
                  //verificare daca camera aleasa de utilizator este vecina cu camera curenta
                  camera_curenta=c;
                  ok=true;
                  player->SetCamera(camera_curenta);
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
                    cout<<"==Ai intrat in camera=="<<camera_curenta->getDescriere()<<endl;
                     //cazul in care nu am invins inamicul din camera=> am si cufar in camera (caz 1)
                 if(camera_curenta->getId()!=1&&camera_curenta->getInamic()!=nullptr)
                 {
                     cout<<"==Inamicul:=="<<camera_curenta->getInamic()->getName()<<endl;
                     string nume_inamic = camera_curenta->getInamic()->getName();
                     string fisierASCII = obtineFisierASCII(nume_inamic);
                     if (!fisierASCII.empty()) {
                         afiseazaFisierASCII(fisierASCII);
                                               }              
                     else {
                     cout << "Nu exista desen pentru acest inamic.\n";
                           }
                    //se da o avertizare in cazul in care in lupta sunt sanse mari de poierdere
                     if(camera_curenta->getInamic()->getMinimDamage()>player->getHealth())
                        cout<<"Esti sigur ca vrei sa lupti? ATENTIE! ACEST INAMIC ARE MINIM DAMAGE "<<camera_curenta->getInamic()->getMinimDamage()<<"si tu ai "<<player->getHealth()<<" sanatate"<<endl;
                     cout<<"Esti sigur ca vrei sa lupti?"<<endl;

                     cout<<"1.DA"<<endl;
                     cout<<"2.NU"<<endl;

                     int raspuns_lupta;
                     cin>>raspuns_lupta;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                     if(raspuns_lupta==1)
                     {
                     //start lupta
                     Lupta lupta(player, camera_curenta->getInamic());
                     bool castigator = lupta.start();
                     if (castigator) {
                         int bani_castigati=camera_curenta->getInamic()->randomMoney();//se adauga bani in functie de boss ul omorat
                         player->AdaugaBani(bani_castigati);
                         Obiect *obiectPrimit= daObiectRandom(player, obiecte_global);
                         MateriePrima *materiePrimita=daMaterieRandom(player,materii);
                         player->adaugaMateriePrima(materiePrimita);
                         Potiune *potiune=dynamic_cast<Potiune*>(obiectPrimit);//urmeaza sa vad daca obiectul este potiune
                         //daca e potiune, o folosesc indiferent
                         //afisare comeback
                         cout << "Ai invins inamicul!"<<" Ai primit "<<bani_castigati<<" bani un obiect: "<<obiectPrimit->getNume()<< "si materia prima: "<<materiePrimita->getNume()<<endl;
                         if(player->getMonstriBatuti()==monstri_camere_initial)
                         {
                            cout<<"FELICITARI!AI CASTIGAT! AI INVINS TOTI MONSTRI!"<<endl;
                            cout<<"In curand o sa te trezesti..."<<endl;
                            cout<<"In lumea monstrilor adevarati...omenirea"<<endl;
                            NpcInfo batranul = {"Batranul Intelept", "Sa nu ai incredere in oameni...", false};
                            NPC npc1(batranul);
                            npc1.Interacționeaza(player);
                            intrare_camera=false;
                         }
                         //daca este potiune o folosesc direct, nu se adauga la inventar
                         if(potiune)
                            player->folosestePotiune(potiune);
                         else
                         //altefl se adauga obiectul in inventar
                         if(!potiune)
                            player->AdaugaObiect(obiectPrimit);
                         player->afiseazaInventar();
                         //stergem inamcicul din camera 
                         delete camera_curenta->getInamic();
                         camera_curenta->setInamic(nullptr);//setam inamicul la null
                         //--mecanica folosirii cufarului---

                         cout<<"Felicitari...ai invins..uite un cufar, il deschizi?"<<endl;
                         cout<<"1.DA"<<endl;
                         cout<<"2.NU"<<endl;

                         int raspuns_cufar;
                         cin>>raspuns_cufar;
                          cin.ignore(numeric_limits<streamsize>::max(), '\n');
                         switch(raspuns_cufar)
                         {
                            case 1:
                            {
                                //il marcam ca si folosit
                            camera_curenta->getCufar()->schimbaStareCufar();

                            cout << "Inspectezi cufarul..." << endl;
                            Obiect *obiectPrimit=daObiectRandom(player,obiecte_global);
                            MateriePrima *materiePrimita=daMaterieRandom(player,materii);
                            //adaugam obiectele primite in inventar/ cosnsumam daca nu potiunile
                            player->adaugaMateriePrima(materiePrimita);
                            Potiune *potiune=dynamic_cast<Potiune*>(obiectPrimit);//urmeaza sa vad daca obiectul este potiune
                            cout<<"Felicitari!ai primit: "<<*obiectPrimit<<"si materia prima: "<<materiePrimita->getNume()<<endl;
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
                                player->AdaugaObiect(obiectPrimit);
                                player->afiseazaInventar(); // Vezi ce ai în inventar
                                camera_curenta->getCufar()->schimbaStareCufar();//schimb starea cufarului la folosit
                                cout<<"Apasa ENTER pentru a reveni la meniu"<<endl;
                                cin.get();
                                break;
                            }
                            case 2:
                            {
                                cout<<"Apasa ENTER pentru a reveni la meniu"<<endl;
                                cin.get();
                                break;
                            }
                         }
                        }
                     else {//else aferent pierderii luptei
                         cout << "Ai murit! Game over.\n";
                         exit(0);
                          }//aici!
                        }
                        else
                        {
                            //am ales sa nu lupt
                            cout<<"E ok..keep going..poate alt inamic e potrivit pentru tine"<<endl;
                            cout<<"Apasa ENTER pentru a reveni la meniu"<<endl;
                            cin.get();

                        }
                        }
                        //cazul in care intru intr o camera in care inca mai e cufar, dar nu mai e monstru
                        else
                          if(camera_curenta->getInamic()==nullptr&&camera_curenta->getCufar()->getStateCufar()==false)
                          {
                            cout<<"hmmm..inca e un cufar aici"<<endl;
                            asteaptaEnter();
                            break;
                          }
                          else
                          {
                            //cazul in care nu mai e nimic
                             cout<<"se pare ca nu mai este nimic interesant in aceasta camera"<<endl;
                             asteaptaEnter();
                             break;
                          }
                            if(camera_curenta->getId()==1)
                            {
                                //cazul pt camera de start
                                cout<<"Nimic interesant de vazut aici...continua aventura in celelalte camere"<<endl;
                                asteaptaEnter();
                                break;
                            }
                 }
                 
                break;

            }
            case 4:
            {
            cout<<"===Bine ai venit la magazin==="<<endl;
            Camera *camera_curenta=camere[11];
            player->SetCamera(camera_curenta);
            
            Magazin magazin;
            AdaugaMagazin(magazin);
            cout << "Lista de obiecte pe care le poti cumpara: "<<endl;
            magazin.afiseazaStoc();
            cout<<"Momentan ai: "<<player->getPocket()<<" bani"<<endl;
            cout<<"Vrei sa cumperi ceva?"<<endl;
            cout<<"1.Da"<<endl;
            cout<<"2.NU"<<endl;
            int raspuns_magazin;
            cin>>raspuns_magazin;
            if(raspuns_magazin==1)
            {
            magazin.afiseazaStoc();
            cout<<"Scrie indexul obiectului pe care il doresti"<<endl;
            int index;
            cin >> index;
            Obiect* cumparat = magazin.cumparaObiect(index, player);
            if (cumparat) {
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
                //afisare inventar
                player->afiseazaInventar();
                cout<<"Arma curenta: "<<player->getArmaCurenta()->getNume()<<endl;
                cout<<"Doresti sa schimbi arma?"<<endl;
                cout<<"1.DA"<<endl;
                cout<<"2.NU"<<endl;
                int optiune_arma;
                cin>>optiune_arma;
                cin.ignore();
                switch(optiune_arma)
                {
                    case 1:
                    {
                        player->afiseazaInventar();
                        cout<<"Scrieti numele armei cu care vreti sa schimbati "<<player->getArmaCurenta()->getNume()<<endl;
                        string nume_arma;
                       
                        getline(cin, nume_arma); // citește tot, inclusiv spații
                        //schimbam arma
                        player->schimbaArma(nume_arma);
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
                cout<<"Apasa ENTER pentru a reveni la meniu"<<endl;
                cin.get();
                break;
            }
            case 7:
            {
            cout<<"Proasta alegere..nu ai curaj..poate ca nu te vei mai trezi niciodata..";
            exit(0);
            }
            case 8:
            {
                cout<<"===INVENTAR MATERIE PRIMA: ==="<<endl;
                cout<<endl;
                //afisare inventar
                player->afiseazaInventarMaterie();
                cout<<endl;
                cout<<"Apasa ENTER pentru a reveni la meniu"<<endl;
                cin.get();
                break;
            }
            case 9:
            {  
                //functie de crafting 
                craft(player);
                cout<<"Apasa ENTER pentru a reveni la meniu"<<endl;
                cin.get();
            }
        }
    }
    return 0;
}