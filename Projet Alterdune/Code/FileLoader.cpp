#include "FileLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

std::vector<std::string> FileLoader::parseLine(const std::string& line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    
    while (std::getline(ss, token, ';')) {
        tokens.push_back(token);
    }
    
    return tokens;
}

Category FileLoader::parseCategory(const std::string& s) {
    if (s == "NORMAL") {
        return NORMAL;
    }
    if (s == "MINIBOSS") {
        return MINIBOSS;
    }
    if (s == "BOSS") {
        return BOSS;
    }
    return NORMAL;
}

std::vector<Item> FileLoader::loadItems(const std::string& path) {
    std::vector<Item> items;
    std::ifstream file(path.c_str());
    
    if (!file.is_open()) {
        std::cerr << "Fichier introuvable : " << path << std::endl;
        std::exit(1);
    }
    
    std::string line;
    
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        std::vector<std::string> cols = parseLine(line);
        if (cols.size() < 4) {
            continue;
        }
        
        std::string name = cols[0];
        int value = std::stoi(cols[2]);
        int qty = std::stoi(cols[3]);
        
        Item newItem(name, value, qty);
        items.push_back(newItem);
    }
    
    file.close();
    return items;
}

std::vector<Monster> FileLoader::loadMonsters(const std::string& path) {
    std::vector<Monster> monsters;
    std::ifstream file(path.c_str());
    
    if (!file.is_open()) {
        std::cerr << "Fichier introuvable : " << path << std::endl;
        std::exit(1);
    }
    
    std::string line;
    
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        std::vector<std::string> cols = parseLine(line);
        if (cols.size() < 8) {
            continue;
        }
        
        Category cat = parseCategory(cols[0]);
        std::string name = cols[1];
        int hp = std::stoi(cols[2]);
        int mercyGoal = std::stoi(cols[5]);
        
        std::vector<std::string> actIds;
        for (int i = 6; i < (int)cols.size(); i++) {
            if (cols[i] != "-") {
                actIds.push_back(cols[i]);
            }
        }
        
        Monster newMonster(name, hp, cat, mercyGoal, actIds);
        monsters.push_back(newMonster);
    }
    
    file.close();
    return monsters;
}