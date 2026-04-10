#ifndef FILELOADER_H
#define FILELOADER_H

#include "Item.h"
#include "Monster.h"
#include <vector>
#include <string>

class FileLoader {
public:
    std::vector<Item> loadItems(const std::string& path);
    std::vector<Monster> loadMonsters(const std::string& path);

private:
    std::vector<std::string> parseLine(const std::string& line);
    std::string trim(const std::string& s);
    Category parseCategory(const std::string& s);
};

#endif