#pragma once
#include "Item.h"
#include "Monster.h"
#include <vector>
#include <string>

// ===========================================================
// CLASSE : FileLoader
// ===========================================================
// Gère la lecture des fichiers CSV.
// Sépare la responsabilité "lire des fichiers" du reste du jeu.
//
// Toutes les méthodes sont déclarées "static" ici CAR
// on n'a jamais besoin de créer un objet FileLoader :
//   FileLoader::loadItems(...)     <- appel direct, sans "new FileLoader()"
//
// C'est le seul endroit dans ce projet où on utilise "static" :
// c'est un usage simple et justifié (classe utilitaire).
// ===========================================================

class FileLoader {
public:
    // Lit items.csv et retourne un vecteur d'Items
    // Arrête le programme si le fichier est introuvable
    static std::vector<Item>    loadItems(std::string cheminFichier);

    // Lit monsters.csv et retourne un vecteur de Monsters
    // Arrête le programme si le fichier est introuvable
    static std::vector<Monster> loadMonsters(std::string cheminFichier,
                                             const std::vector<ActAction>& catalogue);

private:
    // Découpe une ligne en morceaux selon le séparateur (';' par défaut)
    // Retourne un vecteur de strings
    // ex: "Potion;HEAL;15;3" → {"Potion", "HEAL", "15", "3"}
    static std::vector<std::string> splitLine(std::string ligne, char separateur);

    // Supprime les espaces en début et fin de chaîne
    static std::string trim(std::string s);

    // Convertit un texte de catégorie en enum Category
    static Category parseCategory(std::string texte);
};
