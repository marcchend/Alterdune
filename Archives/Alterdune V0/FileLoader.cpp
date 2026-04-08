#include "FileLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>

// ---------- Utilitaires ----------
std::string FileLoader::trim(const std::string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    size_t b = s.find_last_not_of(" \t\r\n");
    return (a == std::string::npos) ? "" : s.substr(a, b - a + 1);
}

std::vector<std::string> FileLoader::parseLine(const std::string& line, char sep) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, sep))
        tokens.push_back(trim(token));
    return tokens;
}

Category FileLoader::parseCategory(const std::string& s) {
    if (s == "NORMAL")   return Category::NORMAL;
    if (s == "MINIBOSS") return Category::MINIBOSS;
    if (s == "BOSS")     return Category::BOSS;
    throw std::invalid_argument("Categorie inconnue : " + s);
}

// ---------- Chargement items.csv ----------
// Format : nom;type;valeur;quantite
std::vector<Item> FileLoader::loadItems(const std::string& path) {
    std::vector<Item> items;
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "[ERREUR] Fichier introuvable : " << path << "\n";
        std::exit(1);
    }
    std::string line;
    int lineNum = 0;
    while (std::getline(file, line)) {
        lineNum++;
        if (line.empty() || line[0] == '#') continue; // commentaire ou vide
        auto cols = parseLine(line);
        if (cols.size() < 4) {
            std::cerr << "[WARN] Ligne " << lineNum << " mal formee, ignoree : " << line << "\n";
            continue;
        }
        try {
            std::string name = cols[0];
            // cols[1] = type (HEAL uniquement pour l'instant, on ignore)
            int value = std::stoi(cols[2]);
            int qty   = std::stoi(cols[3]);
            items.emplace_back(name, value, qty);
        } catch (...) {
            std::cerr << "[WARN] Ligne " << lineNum << " : valeurs invalides, ignoree.\n";
        }
    }
    return items;
}

// ---------- Chargement monsters.csv ----------
// Format : categorie;nom;hp;atk;def;mercyGoal;act1;act2[;act3[;act4]]
std::vector<Monster> FileLoader::loadMonsters(const std::string& path) {
    std::vector<Monster> monsters;
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "[ERREUR] Fichier introuvable : " << path << "\n";
        std::exit(1);
    }
    std::string line;
    int lineNum = 0;
    while (std::getline(file, line)) {
        lineNum++;
        if (line.empty() || line[0] == '#') continue;
        auto cols = parseLine(line);
        if (cols.size() < 8) {
            std::cerr << "[WARN] Ligne " << lineNum << " mal formee, ignoree.\n";
            continue;
        }
        try {
            Category cat = parseCategory(cols[0]);
            std::string name = cols[1];
            int hp        = std::stoi(cols[2]);
            // cols[3]=atk, cols[4]=def : stockés si besoin (non utilisés dans la formule de dégâts du projet)
            int mercyGoal = std::stoi(cols[5]);

            // Récupère les actIds (colonnes 6+), ignore les "-"
            std::vector<std::string> actIds;
            for (size_t i = 6; i < cols.size(); i++) {
                if (cols[i] != "-" && !cols[i].empty())
                    actIds.push_back(cols[i]);
            }
            monsters.emplace_back(name, hp, cat, mercyGoal, actIds);
        } catch (const std::exception& e) {
            std::cerr << "[WARN] Ligne " << lineNum << " : " << e.what() << ", ignoree.\n";
        }
    }
    return monsters;
}
