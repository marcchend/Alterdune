#pragma once
#include "Monster.h"
#include "ActAction.h"
#include <vector>
#include <string>

// ===========================================================
// CLASSE : FileLoader
// ===========================================================
// Gere la lecture des fichiers CSV.
//
// TODO : ajouter loadItems() quand Item sera implemente
// ===========================================================

class FileLoader {
public:
    // Lit monsters.csv et retourne un vecteur de Monsters
    static std::vector<Monster> loadMonsters(std::string cheminFichier,
                                             const std::vector<ActAction>& catalogue);

    // TODO : static std::vector<Item> loadItems(std::string cheminFichier);

private:
    static std::vector<std::string> splitLine(std::string ligne, char separateur);
    static std::string trim(std::string s);
    static Category parseCategory(std::string texte);
};
