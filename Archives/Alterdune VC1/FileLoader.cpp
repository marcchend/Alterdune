#include "FileLoader.h"
#include <fstream>    // Pour lire des fichiers (ifstream)
#include <sstream>    // Pour découper des strings (stringstream)
#include <iostream>
#include <cstdlib>    // Pour exit()

// ===========================================================
// Implémentation de FileLoader
// ===========================================================

// ----- Utilitaire : supprime les espaces autour d'une string -----
std::string FileLoader::trim(std::string s) {
    // Trouve le premier caractère non-espace
    int debut = 0;
    while (debut < (int)s.size() && s[debut] == ' ') debut++;

    // Trouve le dernier caractère non-espace
    int fin = (int)s.size() - 1;
    while (fin >= 0 && s[fin] == ' ') fin--;

    // Retourne la sous-string sans espaces
    if (debut > fin) return "";           // Que des espaces → string vide
    return s.substr(debut, fin - debut + 1);
}

// ----- Utilitaire : découpe une ligne selon un séparateur -----
std::vector<std::string> FileLoader::splitLine(std::string ligne, char separateur) {
    std::vector<std::string> morceaux;
    std::stringstream ss(ligne);   // On wrappe la ligne dans un flux
    std::string morceau;

    // getline lit jusqu'au séparateur, puis recommence
    while (std::getline(ss, morceau, separateur)) {
        morceaux.push_back(trim(morceau));  // On nettoie les espaces
    }
    return morceaux;
}

// ----- Utilitaire : convertit un texte en enum Category -----
Category FileLoader::parseCategory(std::string texte) {
    if (texte == "NORMAL")   return NORMAL;
    if (texte == "MINIBOSS") return MINIBOSS;
    if (texte == "BOSS")     return BOSS;

    // Catégorie inconnue : on affiche une erreur et on arrête
    std::cerr << "[ERREUR] Categorie inconnue : " << texte << "\n";
    exit(1);
}

// ----- Lecture de items.csv -----
// Format attendu : nom;type;valeur;quantite
std::vector<Item> FileLoader::loadItems(std::string cheminFichier) {
    std::vector<Item> items;

    // On ouvre le fichier en lecture
    std::ifstream fichier(cheminFichier);

    // Vérifie si le fichier existe et est lisible
    if (!fichier.is_open()) {
        std::cerr << "[ERREUR] Impossible d'ouvrir : " << cheminFichier << "\n";
        std::cerr << "Verifiez que le fichier existe dans le dossier data/\n";
        exit(1);  // Arrêt propre du programme
    }

    std::string ligne;
    int numeroLigne = 0;

    // On lit le fichier ligne par ligne
    while (std::getline(fichier, ligne)) {
        numeroLigne++;

        // On ignore les lignes vides et les commentaires (#)
        if (ligne.empty() || ligne[0] == '#') continue;

        // On découpe la ligne en colonnes
        std::vector<std::string> colonnes = splitLine(ligne, ';');

        // On vérifie qu'il y a bien 4 colonnes
        if ((int)colonnes.size() < 4) {
            std::cerr << "[WARN] Ligne " << numeroLigne
                      << " ignoree (format incorrect) : " << ligne << "\n";
            continue;
        }

        // On extrait les valeurs
        std::string nom   = colonnes[0];
        // colonnes[1] = type (HEAL), on l'ignore pour l'instant
        int valeur        = std::stoi(colonnes[2]);  // stoi = string to int
        int quantite      = std::stoi(colonnes[3]);

        // On crée l'item et on l'ajoute au vecteur
        items.push_back(Item(nom, valeur, quantite));
    }

    fichier.close();  // Bonne pratique : fermer le fichier après usage
    return items;
}

// ----- Lecture de monsters.csv -----
// Format : categorie;nom;hp;atk;def;mercyGoal;act1;act2[;act3[;act4]]
std::vector<Monster> FileLoader::loadMonsters(std::string cheminFichier,
                                              const std::vector<ActAction>& catalogue) {
    std::vector<Monster> monsters;

    std::ifstream fichier(cheminFichier);
    if (!fichier.is_open()) {
        std::cerr << "[ERREUR] Impossible d'ouvrir : " << cheminFichier << "\n";
        exit(1);
    }

    std::string ligne;
    int numeroLigne = 0;

    while (std::getline(fichier, ligne)) {
        numeroLigne++;

        if (ligne.empty() || ligne[0] == '#') continue;

        std::vector<std::string> colonnes = splitLine(ligne, ';');

        // Il faut au minimum 8 colonnes (cat;nom;hp;atk;def;mercy;act1;act2)
        if ((int)colonnes.size() < 8) {
            std::cerr << "[WARN] Ligne " << numeroLigne << " ignoree : " << ligne << "\n";
            continue;
        }

        // Extraction des champs
        Category    cat       = parseCategory(colonnes[0]);
        std::string nom       = colonnes[1];
        int         hp        = std::stoi(colonnes[2]);
        // colonnes[3] = atk, colonnes[4] = def : non utilisés dans la formule de dégâts
        int         mercyGoal = std::stoi(colonnes[5]);

        // Récupération des actIds (colonnes 6 et après), on ignore les "-"
        std::vector<std::string> actIds;
        for (int i = 6; i < (int)colonnes.size(); i++) {
            if (colonnes[i] != "-" && !colonnes[i].empty()) {
                // On vérifie que l'action existe dans le catalogue
                const ActAction* a = findAction(catalogue, colonnes[i]);
                if (a == nullptr) {
                    std::cerr << "[WARN] Action inconnue '" << colonnes[i]
                              << "' pour " << nom << ", ignoree.\n";
                } else {
                    actIds.push_back(colonnes[i]);
                }
            }
        }

        monsters.push_back(Monster(nom, hp, cat, mercyGoal, actIds));
    }

    fichier.close();
    return monsters;
}
