#ifndef CSVLOADER_H
#define CSVLOADER_H

#include <string>
#include <vector>
#include "Item.h"
#include "Monster.h"
#include "Action.h"

class CsvLoader {
public:
    static std::vector<Item> lireItems(std::string chemin);
    static std::vector<Monster> lireMonsters(std::string chemin, const std::vector<Action>& actions);

private:
    static int stringVersEntier(std::string s);
    static std::vector<std::string> decouper(std::string ligne, char separateur);
    static Categorie texteVersCategorie(std::string texte);
};

#endif