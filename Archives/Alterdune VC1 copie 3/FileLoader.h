#pragma once
#include "Item.h"
#include "Monster.h"
#include "Action.h"
#include <vector>
#include <string>

class FileLoader {
public:
    static std::vector<Item>    loadItems(std::string cheminFichier);

    static std::vector<Monster> loadMonsters(std::string cheminFichier,
                                             const std::vector<Action>& catalogue);

private:
    static std::vector<std::string> splitLine(std::string ligne, char separateur);

    static std::string trim(std::string s);

    static Cat parseCategory(std::string texte);
};
