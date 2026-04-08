#include "FileLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

std::vector<Item> FileLoader::chargerItems(const std::string& chemin) {
    std::vector<Item> items;
    std::ifstream fichier(chemin);
    
    if (!fichier.is_open()) {
        std::cerr << "ERREUR: Impossible d'ouvrir " << chemin << std::endl;
        std::exit(1);
    }
    
    std::string ligne;
    while (std::getline(fichier, ligne)) {
        if (ligne.empty()) continue;
        
        std::stringstream ss(ligne);
        std::string nom, type, valeurStr, quantiteStr;
        
        if (std::getline(ss, nom, ';') &&
            std::getline(ss, type, ';') &&
            std::getline(ss, valeurStr, ';') &&
            std::getline(ss, quantiteStr, ';')) {
            
            int valeur = std::stoi(valeurStr);
            int quantite = std::stoi(quantiteStr);
            items.push_back(Item(nom, valeur, quantite));
        }
    }
    
    fichier.close();
    return items;
}

CategorieMonstre stringToCategorie(const std::string& s) {
    if (s == "NORMAL") return CategorieMonstre::NORMAL;
    if (s == "MINIBOSS") return CategorieMonstre::MINIBOSS;
    return CategorieMonstre::BOSS;
}

std::vector<Monster> FileLoader::chargerMonstres(const std::string& chemin) {
    std::vector<Monster> monstres;
    std::ifstream fichier(chemin);
    
    if (!fichier.is_open()) {
        std::cerr << "ERREUR: Impossible d'ouvrir " << chemin << std::endl;
        std::exit(1);
    }
    
    std::string ligne;
    while (std::getline(fichier, ligne)) {
        if (ligne.empty()) continue;
        
        std::stringstream ss(ligne);
        std::string categorieStr, nom, hpStr, mercyGoalStr;
        
        std::getline(ss, categorieStr, ';');
        std::getline(ss, nom, ';');
        std::getline(ss, hpStr, ';');
        
        // On saute atk et def (non utilisés)
        std::string temp;
        std::getline(ss, temp, ';');  // atk
        std::getline(ss, temp, ';');  // def
        
        std::getline(ss, mercyGoalStr, ';');
        
        // Lire les actions disponibles (jusqu'à 4)
        std::vector<std::string> actions;
        std::string action;
        while (std::getline(ss, action, ';')) {
            if (action != "-" && !action.empty()) {
                actions.push_back(action);
            }
        }
        
        CategorieMonstre cat = stringToCategorie(categorieStr);
        int hp = std::stoi(hpStr);
        int mercyGoal = std::stoi(mercyGoalStr);
        
        monstres.push_back(Monster(nom, hp, cat, mercyGoal, actions));
    }
    
    fichier.close();
    return monstres;
}