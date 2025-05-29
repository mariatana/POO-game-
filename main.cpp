#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
#include <map>
#include <sstream>
#include <chrono>
#include <thread>
#include <limits>   
#include <cstdlib>  
#include <algorithm> 

#include "camera.h"
#include "inamic.h"

#include "player.h"
#include "arma.h"
#include "Obiect.h"
#include "magazin.h"
#include "potiune.h"
#include "lupta.h"
#include "cufar.h"
#include "npc.h"
#include "materie.h"



#ifndef MAIN_TEXT_COLORS_DEFINED
#define MAIN_TEXT_COLORS_DEFINED
#define TEXT_RED     "\033[1;31m"
#define TEXT_GREEN   "\033[1;32m"
#define TEXT_YELLOW  "\033[1;33m"
#define TEXT_RESET   "\033[0m"
#endif

// Variabilele globale pentru prototipuri si camerele jocului
std::vector<Obiect*> obiecte_globale_prototipuri;
std::vector<Camera*> camere_joc;
std::vector<MateriePrima*> materii_globale_prototipuri;
int monstri_camere_initial = 0;

void afiseazaIntroducere() {
    std::cout << "You have high fever...\n";
    std::cout << "You are going deeper and deeper into deep sleep...\n";
    std::cout << "But no... something is wrong...\n";
    std::cout << "You woke up in a strange room... let's inspect the place.\n\n";
}

void afiseazaReguli() {
    std::cout << "\n========= RULES =========\n";
    std::cout << "-> Explore 10 dream-rooms.\n";
    std::cout << "-> Find helpful items (weapons, potions).\n";
    std::cout << "-> Defeat enemies using the items you find.\n";
    std::cout << "-> You cannot beat the strongest enemy unless you're well prepared!\n";
    std::cout << "-> You can teleport to the Shop at any time using the main menu options.\n"; // Clarificare
    std::cout << "-> Survive the Fever Dream.\n";
    std::cout << "-> Always check your health!\n";
    std::cout << "-> Press Enter to return to main menu";
}

void creeazaPrototipuriObiecte(std::vector<Obiect*>& proto_obj) {
    
    proto_obj.push_back(new Arma(10, 3, "Sabie de Fier", 0));
    proto_obj.push_back(new Potiune(20, 2, "Apa Vie", true, 0));
    proto_obj.push_back(new Arma(15, 2, "Topor Viking", 0));
    proto_obj.push_back(new Potiune(10, 3, "Potiune de Viata Light", true, 0));
    proto_obj.push_back(new Potiune(30, 2, "Potiune Norocoasa", true, 0));
    proto_obj.push_back(new Arma(20, 2, "Katana", 0));
    proto_obj.push_back(new Arma(30, 1, "Pistol", 0));
    proto_obj.push_back(new Potiune(25, 1, "Potiune Blestemata", false, 0)); // false = rea
    proto_obj.push_back(new Potiune(40, 1, "Leacul Spiridusului", true, 0));
    proto_obj.push_back(new Arma(37, 1, "Sfera Dragonului", 0)); 
    proto_obj.push_back(new Arma(19, 1, "Alabarda", 0)); 
    proto_obj.push_back(new Arma(37, 1, "Claymore", 0));
    proto_obj.push_back(new Potiune(39, 2, "Elixirul Zanelor", true, 0)); 
    proto_obj.push_back(new Arma(16, 1, "Pumnal Ascutit", 0)); 
    proto_obj.push_back(new Potiune(18, 2, "Suflare de Vrajitoare", false, 0)); 
    proto_obj.push_back(new Arma(33, 1, "Zweihander", 0)); 
    proto_obj.push_back(new Arma(25, 1, "Coasa Mortii", 0)); 
}

Obiect* daObiectRandom(const std::vector<Obiect*>& proto_obj) {
    if (proto_obj.empty()) return nullptr;
    std::vector<const Obiect*> pool; // Folosim const Obiect* pentru a nu modifica prototipurile
    for (const Obiect* o_prototip : proto_obj) {
        if (o_prototip) {
            for (int i = 0; i < (6 - o_prototip->getRaritate()); ++i) {
                pool.push_back(o_prototip);
            }
        }
    }
    if (pool.empty()) return nullptr;

    int index = rand() % pool.size();
    return pool[index]->clone();
}

void creeazaPrototipuriMaterii(std::vector<MateriePrima*>& proto_materii) {
    proto_materii.push_back(new MateriePrima("osDragon", 1)); 
    proto_materii.push_back(new MateriePrima("infinitefire", 1));
    proto_materii.push_back(new MateriePrima("poison", 1));
    proto_materii.push_back(new MateriePrima("blades", 1));
    proto_materii.push_back(new MateriePrima("poisonflower", 1));
    proto_materii.push_back(new MateriePrima("fierVechi", 1));
    proto_materii.push_back(new MateriePrima("panzaRufei", 1));
}

MateriePrima* daMaterieRandom(Player* player, const std::vector<MateriePrima*>& proto_materii) {
    if (proto_materii.empty()) return nullptr;
    int index_random = std::rand() % proto_materii.size();
    // Returnam un pointer la prototip. Player::adaugaMateriePrima va gestiona cum o adauga.
    // Momentan, Player creeaza o noua MateriePrima pe baza numelui si cantitatii prototipului.
    if (proto_materii[index_random]) { // Verificam pointerul
         return proto_materii[index_random]; 
    }
    return nullptr;
}


void AdaugaMagazinInitial(Magazin &magazin) {
    magazin.adaugaObiect(new Arma(20, 2, "Katana", 20));
    magazin.adaugaObiect(new Potiune(30, 1, "Potiune Super Vindecatoare", true, 50));
    magazin.adaugaObiect(new Arma(18, 2, "Secure de Lupta", 15)); // Renumit, era Potiune inainte
    magazin.adaugaObiect(new Arma(22, 1, "Sulita", 34)); // Renumit, era Potiune inainte
}

std::vector<Camera*> CreareHartaJoc(const std::string& nume_fisier) {
    std::ifstream fin(nume_fisier);
    std::vector<Camera*> camere_create;
    std::map<int, Camera*> mapa_camere;

    if (!fin) {
        std::cerr << TEXT_RED << "Eroare la deschiderea fisierului harti: " << nume_fisier << TEXT_RESET << std::endl;
        return camere_create;
    }

    std::string linie;
    while (getline(fin, linie)) {
        if (linie.empty() || linie[0] == '#') continue; // Ignora linii goale sau comentarii
        std::stringstream ss(linie);
        int idc, are_inamic_flag;
        std::string descriere_raw; // Citeste toata descrierea initial
        ss >> idc >> descriere_raw; // Citeste ID si primul cuvant al descrierii
        
        // Citeste restul descrierii daca exista spatii
        std::string temp_desc_part;
        std::string descriere_finala = descriere_raw;
        while(ss >> temp_desc_part && !(std::istringstream(temp_desc_part) >> are_inamic_flag)) {
            descriere_finala += " " + temp_desc_part;
        }
        if (!(std::istringstream(temp_desc_part) >> are_inamic_flag)) {
             ss.clear(); // Curatam starea de eroare a ss daca ultimul cuvant nu era numar
             if (!(ss >> are_inamic_flag)) { 
                
                 std::cerr << TEXT_YELLOW << "Atentie: flag 'are_inamic' neclar sau lipsa pentru camera ID " << idc << ". Presupun 0." << TEXT_RESET << std::endl;
                 are_inamic_flag = 0;
             }
        }


        Camera* c;
        bool este_monstru_in_camera = (are_inamic_flag == 1);
        if (descriere_finala.find("Shop") != std::string::npos) { // Verificam daca "Shop" e in descriere
            c = new Camera(idc, descriere_finala, true, este_monstru_in_camera);
        } else {
            c = new Camera(idc, descriere_finala, false, este_monstru_in_camera);
        }
        camere_create.push_back(c);
        mapa_camere[idc] = c;
    }

    fin.clear();
    fin.seekg(0, std::ios::beg);

    while (getline(fin, linie)) {
        if (linie.empty() || linie[0] == '#') continue;
        std::stringstream ss(linie);
        int idc, dummy_are_inamic;
        std::string dummy_descriere_raw, dummy_descriere_finala;
        
        ss >> idc >> dummy_descriere_raw; // Citim ID si primul cuvant al descrierii

        std::string temp_part;
        while(ss >> temp_part && !(std::istringstream(temp_part) >> dummy_are_inamic)) {
            // Consumam descrierea si flag-ul de inamic pentru a ajunge la vecini
        }
        // Daca ultimul temp_part nu a fost convertit la dummy_are_inamic, inseamna ca flag-ul e mai incolo
        if (!(std::istringstream(temp_part) >> dummy_are_inamic)) {
            ss.clear();
            ss >> dummy_are_inamic; // Citim flag-ul
        }

        Camera* camera_curenta = mapa_camere[idc];
        if (!camera_curenta) continue;

        int idVecin;
        while (ss >> idVecin) { // Citim ID-urile vecinilor
            auto it = mapa_camere.find(idVecin);
            if (it != mapa_camere.end()) {
                camera_curenta->adaugaVecini(it->second);
            } else {
                std::cerr << TEXT_YELLOW << "Atentie: Vecinul cu id " << idVecin << " nu exista pentru camera " << idc << "!" << TEXT_RESET << std::endl;
            }
        }
    }
    return camere_create;
}


void adaugaInamiciInCamere(std::vector<Camera*>& camere_ptr_vec) {
    monstri_camere_initial = 0;
    for (Camera* c : camere_ptr_vec) {
        if (!c || !c->emonstru() || c->getInamic() != nullptr) { // Daca nu e camera valida, nu e setata sa aiba monstru, sau deja are unul
            continue;
        }
       
        if (c->getId() == 2) c->setInamic(new Inamic(10, 3, 6, "Clicker"));
        else if (c->getId() == 3) c->setInamic(new Inamic(15, 5, 9, "Pyramid Head"));
        else if (c->getId() == 4) c->setInamic(new Inamic(35, 6, 10, "Slender Man"));
        else if (c->getId() == 5) c->setInamic(new Inamic(49, 7, 12, "Taz"));
        else if (c->getId() == 6) c->setInamic(new Inamic(60, 8, 14, "Scorpion King"));
        else if (c->getId() == 7) c->setInamic(new Inamic(68, 10, 16, "Nemesis"));
        else if (c->getId() == 8) c->setInamic(new Inamic(90, 12, 20, "Hydra"));
        else if (c->getId() == 9) c->setInamic(new Inamic(110, 16, 25, "ItClown"));
        else if (c->getId() == 10) c->setInamic(new Inamic(120, 20, 30, "Annabele"));
        else if (c->getId() == 11) c->setInamic(new Inamic(130, 30, 40, "Fourkings"));

        if (c->getInamic()) {
             monstri_camere_initial++;
        }
    }
}

void afiseazaFisierASCII(const std::string& nume_fisier) {
    std::ifstream fin(nume_fisier);
    if (!fin) {
        std::cerr << TEXT_YELLOW << "Eroare la deschiderea fisierului ASCII: " << nume_fisier << TEXT_RESET << std::endl;
        return;
    }
    std::string linie;
    while (getline(fin, linie)) {
        std::cout << linie << std::endl;
    }
    fin.close();
}

std::string obtineFisierASCII(const std::string& nume_inamic) {
    std::map<std::string, std::string> hartaFisiere = {
        {"Clicker", "clicker.txt"},
        {"Pyramid Head", "ascii_pyramidhead.txt"},
        {"Slender Man", "ascii_slenderman.txt"},
        {"Taz", "taz.txt"},
        {"Scorpion King", "scorpion.txt"},
        {"Nemesis", "nemesis.txt"},
        {"Hydra", "hydra.txt"},
        {"ItClown", "it_clown.txt"},
        {"Annabele", "annabelle.txt"},
        {"Fourkings", "fourkings.txt"}
    };
    auto it = hartaFisiere.find(nume_inamic);
    return (it != hartaFisiere.end()) ? it->second : "";
}

void afiseazaharta() { //
    std::cout << "\n============ HARTA FEVER DREAM ============\n\n"; //
    std::cout << "              [3] PyramidHead -> [4]SlenderMan -> -> -> ->  \n"; //
    std::cout << "                  |               |                        |\n"; //
    std::cout << "[1] Start -> [2] Clicker's ->    [5] Taz ->[6] Scorpion -> [7]Nemesis\n"; //
    std::cout << " |\n"; //
    std::cout << "[10]Annabele                            |                |\n"; //
    std::cout << "  |\n"; //
    std::cout << "[11]FourKings -> -> -> -> -> -> -> ->  [9] ITclown   -> [8]Hydra\n "; //
    std::cout << "\n===========================================\n"; //
    std::cout << "Shop-ul este accesibil din meniul principal al camerei (optiunea 4)\n";
}

void efectCrafting() {
    std::cout << "\nCrafting";
    std::cout.flush();
    for (int i = 0; i < 3; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << ".";
        std::cout.flush();
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "\n";
}

void gestioneazaCrafting(Player* p) {
    if (!p) return;
    bool crafting = true;
    while (crafting) {
        std::cout << "\n--- MASA DE CRAFTING ---\n";
        p->afiseazaInventarMaterie(); // Afiseaza ce materii are jucatorul
        std::cout << "-----------------------\n";
        std::cout << "Retete disponibile: \n";
        std::cout << "1. PoisonBlades (1 blades, 2 poisonflower, 4 poison)\n";
        std::cout << "2. SuperOsDragon (2 osDragon)\n";
        std::cout << "3. Inapoi la meniul camerei\n";
        std::cout << "Alege optiunea: ";
        int op;
        std::cin >> op;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << TEXT_RED << "Optiune invalida. Te rog introdu un numar." << TEXT_RESET << std::endl;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (op) {
            case 1: {
                if (p->AreMaterie("blades", 1) && p->AreMaterie("poisonflower", 2) && p->AreMaterie("poison", 4)) {
                    if(p->PoateAdaugaObiect())
                    {
                    p->consumaMateriePunte("blades", 1);
                    p->consumaMateriePunte("poisonflower", 2);
                    p->consumaMateriePunte("poison", 4);
                    p->AdaugaObiect(new Arma(30, 1, "PoisonBlades", 0));
                    efectCrafting();
                     std::cout << TEXT_GREEN << "Ai craftat PoisonBlades!" << TEXT_RESET << std::endl;
                    }
                    else
                    cout<<"Nu ai loc in inventar"<<endl;
                    
                   
                } else {
                    std::cout << TEXT_YELLOW << "Nu ai suficienta materie prima." << TEXT_RESET << std::endl;
                }
                break;
                
            }
            case 2: {
                if (p->AreMaterie("osDragon", 2)) {
                    if(p->PoateAdaugaObiect())
                    {
                    p->consumaMateriePunte("osDragon", 2);
                    Obiect* n = new Arma(25, 1, "SuperOsDragon", 0);
                    p->AdaugaObiect(n);
                    efectCrafting();
                    std::cout << TEXT_GREEN << "Ai craftat SuperOsDragon!" << TEXT_RESET << std::endl;
                    }
                    else
                    cout<<"Nu ai loc in inventar"<<endl;
                } else {
                    std::cout << TEXT_YELLOW << "Nu ai suficienta materie prima." << TEXT_RESET << std::endl;
                }
                break;
            }
            case 3: {
                crafting = false;
                break;
            }
            default:
                std::cout << TEXT_RED << "Optiune de crafting invalida." << TEXT_RESET << std::endl;
        }
         if (crafting) {
             std::cout << "Apasa Enter pentru a continua la masa de crafting sau scrie 'iesi' pentru a te intoarce la meniul camerei...\n";
             std::string alegere_crafting;
             getline(std::cin, alegere_crafting);
             if (alegere_crafting == "iesi") crafting = false;
        }
    }
}

void asteaptaEnter(bool clearBufferFirst = true) {
   
    std::cout << "\nApasa Enter pentru a reveni la meniu...";
    std::cin.get();
}

void gestioneazaInspectCufar(Player* player, Camera* camera_curenta, const std::vector<Obiect*>& proto_obj_globale) {
    if (!player || !camera_curenta || !camera_curenta->getCufar()) {
        std::cout << TEXT_RED << "Eroare interna: Jucator, camera sau cufar invalid." << TEXT_RESET << std::endl;
        asteaptaEnter();
        return;
    }

    if (camera_curenta->getInamic() != nullptr) {
        if (camera_curenta->getId() != 1)
            std::cout << TEXT_YELLOW << "Nu poti deschide cufarul cat timp monstrul pazeste camera!" << TEXT_RESET << std::endl;
        else 
            std::cout << "Cufarul din camera de start este gol sau inaccesibil acum." << std::endl;
    } else if (!camera_curenta->getCufar()->getStateCufar()) {
        std::cout << "Ai gasit un cufar. Vrei sa il deschizi? (1.DA / 2.NU): ";
        int rasp_cufar;
        std::cin >> rasp_cufar;
        if (std::cin.fail()) {
            std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << TEXT_RED << "Raspuns invalid." << TEXT_RESET << std::endl;
            asteaptaEnter(false); return;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (rasp_cufar == 1) {
            camera_curenta->getCufar()->folosesteCufar(); // Afiseaza "Cufarul este folosit"
            std::cout << "Inspectezi cufarul...\n";
            Obiect* obiectPrimit = daObiectRandom(proto_obj_globale);
            if (obiectPrimit) {
                std::cout << TEXT_GREEN << "Felicitari! Ai primit: " << obiectPrimit->getNume() << TEXT_RESET << std::endl;
                Potiune* potiunePrimita = dynamic_cast<Potiune*>(obiectPrimit);//verific daca e potiune
                if (potiunePrimita) {
                    std::cout << "Este o potiune, o folosesti imediat!\n";
                    potiunePrimita->foloseste(player); // Apel polimorfic
                    delete potiunePrimita; // Potiunea e consumata, dealocam clona
                    // Verificam daca jucatorul a murit din cauza potiunii
                    if (player->getHealth() <= 0) {
                        std::cout << TEXT_RED << "Ai fost rapus de o potiune din cufar!" << TEXT_RESET << std::endl;
                    }
                } else {
                    if(player->PoateAdaugaObiect())//verific daca nu se depaseste limita inventarului
                    player->AdaugaObiect(obiectPrimit);
                else
                    cout<<"Nu ai loc in inventar"<<endl;
                }
            } else {
                std::cout << "Cufarul este gol de data aceasta." << std::endl;
            }
            
            camera_curenta->getCufar()->schimbaStareCufar();
        }
    } else {
        std::cout << "Cufarul din aceasta camera a fost deja deschis." << std::endl;
    }
    asteaptaEnter(false);
}

bool gestioneazaLuptaSiRecompense(Player* player, Camera* camera_curenta, const std::vector<Obiect*>& proto_obj, const std::vector<MateriePrima*>& proto_materii) {
    if (!player || !camera_curenta || !camera_curenta->getInamic()) return true;

    std::cout << TEXT_YELLOW << "\n!!! Inamic:  !!!" << TEXT_RESET << std::endl;
    std::string fisierASCII = obtineFisierASCII(camera_curenta->getInamic()->getName());
    if (!fisierASCII.empty()) afiseazaFisierASCII(fisierASCII);
    Inamic* current_enemy = camera_curenta->getInamic();

    if (player->getArmaCurenta() && camera_curenta->getInamic()->getMinimDamage() > player->getHealth()) {
        std::cout << TEXT_YELLOW << "ATENTIE! Acest inamic are minim damage "
                  << camera_curenta->getInamic()->getMinimDamage()
                  << " si tu ai " << player->getHealth() << " sanatate." << TEXT_RESET << std::endl;
    }
    std::cout << "Esti sigur ca vrei sa lupti? (1.DA / 2.NU): ";
    int rasp_lupta;
    std::cin >> rasp_lupta;
    if (std::cin.fail()) { std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); std::cout << TEXT_RED << "Raspuns invalid." << TEXT_RESET << std::endl; return true;}
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (rasp_lupta == 1) {
        if (!player->getArmaCurenta()) {
            std::cout << TEXT_RED << "Nu ai nicio arma echipata! Nu poti lupta." << TEXT_RESET << std::endl;
            asteaptaEnter(false);
            return true;
        }
        Lupta lupta(player, camera_curenta->getInamic());
        bool castigator = lupta.start();

        if (castigator) {
            std::cout << TEXT_GREEN << "Ai invins inamicul!" << TEXT_RESET << std::endl;

            int bani_castigati = camera_curenta->getInamic()->randomMoney();
            player->AdaugaBani(bani_castigati);
            std::cout << "Ai primit " << bani_castigati << " bani.\n";

            Obiect* obiectLoot = daObiectRandom(proto_obj);
            if (obiectLoot) {
                std::cout << "Ai primit obiectul: " << obiectLoot->getNume() << std::endl;
                Potiune* potiuneLoot = dynamic_cast<Potiune*>(obiectLoot);
                if (potiuneLoot) {
                    std::cout << "Este o potiune, o folosesti imediat!\n";
                    potiuneLoot->foloseste(player);
                    delete potiuneLoot;
                    if (player->getHealth() <= 0) {
                         std::cout << TEXT_RED << "Ai murit din cauza unei potiuni blestemate primite dupa lupta!" << TEXT_RESET << std::endl;
                        return false; // A murit
                    }
                } else {
                    if(player->PoateAdaugaObiect())
                    player->AdaugaObiect(obiectLoot);
                    else
                    cout<<"Nu ai loc in inventar"<<endl;
                }
            }

            MateriePrima* materieLoot_prototip = daMaterieRandom(player, proto_materii);
            if (materieLoot_prototip) {
                std::cout << "Ai primit materia prima: " << materieLoot_prototip->getNume() << std::endl;
                player->adaugaMateriePrima(materieLoot_prototip); // Player gestioneaza copierea datelor
            }

            delete camera_curenta->getInamic();
            camera_curenta->setInamic(nullptr);

            if (Player::getMonstriBatuti() == monstri_camere_initial && monstri_camere_initial > 0) {
                std::cout << TEXT_GREEN << "\nFELICITARI! AI CASTIGAT! AI INVINS TOTI MONSTRII!" << TEXT_RESET << std::endl;
                std::cout << "In curand o sa te trezesti...\n";
                std::cout << "In lumea monstrilor adevarati... omenirea.\n";
                NpcInfo batran_final = {"Batranul Intelept", "Sa nu ai incredere in oameni...", false};
                NPC npc_final(batran_final);
                npc_final.Interacționeaza(player);
                return false; // Semnal pentru a termina jocul (game won)
            }
             if (camera_curenta->getCufar() && !camera_curenta->getCufar()->getStateCufar()){
                 std::cout << "\nMonstrul a fost invins. Acum poti inspecta cufarul (daca nu ai facut-o deja).\n";
            }
        } else { // A pierdut lupta
            std::cout << TEXT_RED << "Ai murit! Game over." << TEXT_RESET << std::endl;
            return false; // A murit
        }
    } else {
        std::cout << "Ai ales sa nu lupti. Poate data viitoare.\n";
    }
    asteaptaEnter(false);
    return true;
}

void gestioneazaMagazin(Player* player) { 
    if (!player) return;

    std::cout << TEXT_GREEN << "\n=== Bine ai venit la Magazin! ===" << TEXT_RESET << std::endl;
    Magazin magazin_joc; // 
    AdaugaMagazinInitial(magazin_joc);

    if (magazin_joc.esteGol()) {
        std::cout << "Magazinul este inchis sau nu are marfa acum.\n";
        asteaptaEnter();
        return;
    }

    bool inMagazin = true;
    while(inMagazin) {
        std::cout << "\n--- Vitrina Magazinului ---\n";
        std::cout << "Bani disponibili: " << player->getPocket() << ".\n";
        magazin_joc.afiseazaStoc();
        std::cout << "-------------------------------------\n";
        std::cout << "1. Cumpara obiect (introdu indexul)\n";
        std::cout << "2. Iesi din magazin\n";
        std::cout << "Optiune: ";
        int opt_magazin;
        std::cin >> opt_magazin;

        if (std::cin.fail()) {
            std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << TEXT_RED << "Optiune invalida." << TEXT_RESET << std::endl;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opt_magazin) {
            case 1: {
                std::cout << "Introdu indexul obiectului dorit: ";
                int index_obj;
                std::cin >> index_obj;
                if (std::cin.fail()) {std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); break;}
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                Obiect* cumparat = magazin_joc.cumparaObiect(index_obj, player);
                Potiune *pot=dynamic_cast<Potiune *>(cumparat);
                if(pot)
                pot->foloseste(player);
                else
                 if (cumparat) {
                    player->AdaugaObiect(cumparat); // Adauga clona in inventar
                }
                break;
            }
            case 2: {
                inMagazin = false;
                std::cout << "Ai iesit din magazin.\n";
                break;
            }
            default:
                std::cout << TEXT_RED << "Optiune de magazin invalida." << TEXT_RESET << std::endl;
        }
    }
   
}


int main() {
    srand(static_cast<unsigned int>(time(0)));

    creeazaPrototipuriObiecte(obiecte_globale_prototipuri);
    creeazaPrototipuriMaterii(materii_globale_prototipuri);

    afiseazaIntroducere();
    bool ruleaza_jocul_principal = true;
    bool joc_pornit_efectiv = false;

    while (ruleaza_jocul_principal) {
        std::cout << "\n========= FEVER DREAM MENU =========\n";
        std::cout << "1. Play Game\n";
        std::cout << "2. See Rules\n";
        std::cout << "3. Exit\n";
        std::cout << "Choose an option: ";
        int optiune_meniu_principal;
        std::cin >> optiune_meniu_principal;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << TEXT_RED << "Optiune invalida. Te rog introdu un numar." << TEXT_RESET << std::endl;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (optiune_meniu_principal) {
            case 1:
                std::cout << "Good luck trying to get out... (evil laugh haha)\n";
                camere_joc = CreareHartaJoc("harta.txt"); //
                if (camere_joc.empty()) {
                    std::cerr << TEXT_RED << "Nu s-a putut crea harta. Jocul nu poate incepe." << TEXT_RESET << std::endl;
                    // Curatare prototipuri globale inainte de a iesi
                    //(in caz ca programul zice pa pa sa nu ramana gunoiae :)
                    for(Obiect* obj : obiecte_globale_prototipuri) delete obj;
                    obiecte_globale_prototipuri.clear();
                    for(MateriePrima* mat : materii_globale_prototipuri) delete mat;
                    materii_globale_prototipuri.clear();
                    return 1;
                }
                adaugaInamiciInCamere(camere_joc);
                ruleaza_jocul_principal = false;
                joc_pornit_efectiv = true;
                break;
            case 2:
                afiseazaReguli();
                asteaptaEnter(false);
                break;
            case 3:
                std::cout << "Exiting Fever Dream...\n";
                ruleaza_jocul_principal = false;
                joc_pornit_efectiv = false;
                break;
            default:
                std::cout << TEXT_RED << "Invalid Option. Try again." << TEXT_RESET << std::endl;
        }
    }

    if (!joc_pornit_efectiv) {
        // Curatare prototipuri globale daca jocul nu porneste
        for(Obiect* obj : obiecte_globale_prototipuri) delete obj;
        obiecte_globale_prototipuri.clear();
        for(MateriePrima* mat : materii_globale_prototipuri) delete mat;
        materii_globale_prototipuri.clear();
        // camere_joc ar trebui sa fie goala aici, dar pentru siguranta:
        for(Camera* cam : camere_joc) delete cam;
        camere_joc.clear();
        std::cout << "Jocul s-a terminat inainte de a incepe efectiv.\n";
        return 0;
    }

    Player* player = new Player(70,camere_joc[0], 20);
    Camera* camera_curenta = camere_joc[0]; // Presupunem ca prima camera e camera de start
    player->SetCamera(camera_curenta);

    Arma* sabie_start = new Arma(10, 3, "Sabie de lemn", 0); 
    player->AdaugaObiect(sabie_start);
    player->seteazaArma(sabie_start);

    std::cout << "\n=== START ROOM ===\n";
    std::cout << "Te afli in prima camera: " << camera_curenta->getDescriere() << "\n";
    std::cout << "==================\n";

    NpcInfo batran_info = {"Batranul Intelept", "Clicker-ul ascunde un secret... Nu tot ce straluceste e aur.", true}; 
    NPC npc_batran(batran_info);
    npc_batran.Interacționeaza(player);

    bool in_loop_camera = true;
    while (in_loop_camera && player->getHealth() > 0) { // Adaugam conditia de viata a player-ului in bucla
        std::cout << "\n--- MENIU CAMERA (" << camera_curenta->getDescriere() << ") ---\n";
        std::cout << "Sanatate: " << player->getHealth() << " | Bani: " << player->getPocket() << "\n";
        std::cout << "Arma echipata: " << (player->getArmaCurenta() ? player->getArmaCurenta()->getNume() : "Niciuna") << "\n";
        std::cout << "----------------------------------\n";
        std::cout << "1. Inspecteaza cufar\n";
        std::cout << "2. Vezi harta jocului\n";
        std::cout << "3. Alege camera in care vrei sa mergi\n";
        std::cout << "4. Mergi la Magazin\n";
        std::cout << "5. Inventar Obiecte (si schimba arma)\n";
     
        std::cout << "6. Inventar Materie Prima\n"; 
        std::cout << "7. Crafteaza Obiecte\n";    
        std::cout << "8. Renunta la joc\n";        
        std::cout << "Alege optiunea: ";
        int optiune_camera;
        std::cin >> optiune_camera;

        if (std::cin.fail()) {
            std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << TEXT_RED << "Optiune invalida." << TEXT_RESET << std::endl;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (optiune_camera) {
            case 1:
                gestioneazaInspectCufar(player, camera_curenta, obiecte_globale_prototipuri);
                break;
            case 2:
                afiseazaharta();
                asteaptaEnter(false);
                break;
            case 3: {
                std::cout << "\n--- Alegere Camera Vecina ---\n";
                const auto& vecini = camera_curenta->getVecini();
                if (vecini.empty()) {
                    std::cout << "Nu exista iesiri din aceasta camera!\n";
                    asteaptaEnter(false);
                } else {
                    for (size_t i = 0; i < vecini.size(); ++i) {
                        if(vecini[i])
                            std::cout << i + 1 << ". Camera " << vecini[i]->getId() << " (" << vecini[i]->getDescriere() << ")\n";
                    }
                    std::cout << "Alege numarul camerei (sau 0 pentru a anula): ";
                    int alege_idx_vecin;
                    std::cin >> alege_idx_vecin;
                    if (std::cin.fail()) {std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); std::cout << TEXT_RED << "Selectie invalida." << TEXT_RESET << std::endl; break;}
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (alege_idx_vecin > 0 && alege_idx_vecin <= static_cast<int>(vecini.size())) {
                        Camera* camera_selectata = vecini[alege_idx_vecin - 1];
                        if(camera_selectata) {
                            camera_curenta = camera_selectata;
                            player->SetCamera(camera_curenta);
                            std::cout << "\n== Ai intrat in camera: " << camera_curenta->getDescriere() << " ==\n";
                            if (camera_curenta->esteMagazin()) {
                                std::cout << "Aceasta este o zona de magazin. Poti accesa magazinul din meniu.\n";
                                asteaptaEnter(false);
                            } else if (camera_curenta->getInamic() != nullptr) {
                                if (!gestioneazaLuptaSiRecompense(player, camera_curenta, obiecte_globale_prototipuri, materii_globale_prototipuri)) {
                                    in_loop_camera = false; 
                                }
                            } else {
                                std::cout << "Camera pare linistita.\n";
                                if (camera_curenta->getCufar() && !camera_curenta->getCufar()->getStateCufar()){
                                     std::cout << "Observi un cufar neinspectat.\n";
                                }
                                asteaptaEnter(false);
                            }
                        } else { std::cout << TEXT_RED << "Eroare: Camera selectata este invalida." << TEXT_RESET << std::endl;}
                    } else if (alege_idx_vecin == 0) { std::cout << "Ai ramas in camera curenta.\n"; }
                    else { std::cout << TEXT_RED << "Selectie invalida pentru camera." << TEXT_RESET << std::endl; }
                }
                break;
            }
            case 4:
                gestioneazaMagazin(player);
                asteaptaEnter(false);
                break;
            case 5: {
                player->afiseazaInventar();
                if (player->getNumarArme() > 0) {
                    std::cout << "\nArma curenta: "
                              << (player->getArmaCurenta() ? player->getArmaCurenta()->getNume() : "Niciuna")
                              << std::endl;
                    std::cout << "Doresti sa schimbi arma? (1.DA / 2.NU): ";
                    int opt_arma;
                    std::cin >> opt_arma;
                    if (std::cin.fail()) {std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');break;}
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if (opt_arma == 1) {
                        std::cout << "Scrie numele armei cu care vrei sa schimbi (exact cum apare in inventar): ";
                        std::string nume_arma_noua;
                        getline(std::cin, nume_arma_noua);
                        player->schimbaArma(nume_arma_noua);
                    }
                } else {
                    std::cout << "Nu ai nicio arma in inventar.\n";
                }
                asteaptaEnter(false);
                break;
            }
            case 6:
                player->afiseazaInventarMaterie();
                asteaptaEnter(false);
                break;
            case 7: 
                gestioneazaCrafting(player);
                break;
            case 8: 
                std::cout << TEXT_YELLOW << "Ai ales sa renunti... Visul febril continua fara tine." << TEXT_RESET << std::endl;
                in_loop_camera = false;
                break;
            default:
                std::cout << TEXT_RED << "Optiune invalida in camera." << TEXT_RESET << std::endl;
        }

        if (player->getHealth() <= 0 && in_loop_camera) { // Verificare suplimentara de moarte DUPA actiune
             in_loop_camera = false;
        }
    }

    std::cout << "\nSfarsitul jocului Fever Dream.\n";
    // Cleanup
    delete player;
    player = nullptr;

    for (Camera* c : camere_joc) {
        delete c; // Destructorul Camerei ar trebui sa se ocupe de Inamic si Cufar
    }
    camere_joc.clear();

    for (Obiect* o_prototip : obiecte_globale_prototipuri) {
        delete o_prototip;
    }
    obiecte_globale_prototipuri.clear();

    for (MateriePrima* m_prototip : materii_globale_prototipuri) {
        delete m_prototip;
    }
    materii_globale_prototipuri.clear();

   
    return 0;
}