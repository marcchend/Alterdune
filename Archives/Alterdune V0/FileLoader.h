#pragma once
#include "Item.h"
#include "Monster.h"
#include <vector>
#include <string>

class FileLoader {
public:
    // Charge items.csv → vecteur d'Item
    static std::vector<Item> loadItems(const std::string& path);

    // Charge monsters.csv → vecteur de Monster
    static std::vector<Monster> loadMonsters(const std::string& path);

private:
    // Découpe une ligne CSV selon le séparateur ';'
    static std::vector<std::string> parseLine(const std::string& line, char sep = ';');
    static std::string trim(const std::string& s);
    static Category parseCategory(const std::string& s);
};
