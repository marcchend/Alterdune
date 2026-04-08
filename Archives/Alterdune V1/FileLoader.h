#ifndef FILELOADER_H
#define FILELOADER_H

#include "Item.h"
#include "Monster.h"
#include <vector>
#include <string>

class FileLoader {
public:
    static std::vector<Item> chargerItems(const std::string& chemin);
    static std::vector<Monster> chargerMonstres(const std::string& chemin);
};

#endif