#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <vector>
#include <string>
#include "Action.h"
#include "Item.h"
#include "Monster.h"
#include "Player.h"
#include "CsvLoader.h"

class Launcher {
private:
    Player* joueur;
    std::vector<Action> actions;
    std::vector<Item> items;
    std::vector<Monster> monstres;
    std::vector<Monster> bestiaire;

public:
    Launcher();
    ~Launcher();

    void lancerJeu();

private:
    void initialiser();
    void chargerFichiers();
    void afficherResumeDebut();
    void menuPrincipal();
    bool combat(Monster& monstre);
    void afficherFin();
};

#endif