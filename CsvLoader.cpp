#include "CsvLoader.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

int CsvLoader::stringVersEntier(std::string s) {
    int resultat = 0;

    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            resultat = resultat * 10 + (s[i] - '0');
        }
    }

    return resultat;
}

std::vector<std::string> CsvLoader::decouper(std::string ligne, char separateur) {
    std::vector<std::string> morceaux;
    std::string morceau = "";

    for (int i = 0; i < (int)ligne.length(); i++) {
        if (ligne[i] == separateur) {
            morceaux.push_back(morceau);
            morceau = "";
        } else if (ligne[i] != ' ') {
            morceau = morceau + ligne[i];
        }
    }

    morceaux.push_back(morceau);

    return morceaux;
}

Categorie CsvLoader::texteVersCategorie(std::string texte) {
    if (texte == "NORMAL") return NORMAL;
    if (texte == "MINIBOSS") return MINIBOSS;
    if (texte == "BOSS") return BOSS;

    std::cout << "ERREUR : categorie inconnue : " << texte << std::endl;
    exit(1);
}

std::vector<Item> CsvLoader::lireItems(std::string chemin) {
    std::vector<Item> items;
    std::ifstream fichier(chemin.c_str());

    if (!fichier.is_open()) {
        std::cout << "ERREUR : impossible d'ouvrir " << chemin << std::endl;
        exit(1);
    }

    std::string ligne;

    while (getline(fichier, ligne)) {
        if (ligne.length() == 0) continue;
        if (ligne[0] == '#') continue;

        std::vector<std::string> colonnes = decouper(ligne, ';');

        if (colonnes.size() < 4) {
            std::cout << "Ligne item ignoree : " << ligne << std::endl;
            continue;
        }

        std::string nom = colonnes[0];
        int valeur = stringVersEntier(colonnes[2]);
        int quantite = stringVersEntier(colonnes[3]);

        items.push_back(Item(nom, valeur, quantite));
    }

    fichier.close();
    return items;
}

std::vector<Monster> CsvLoader::lireMonsters(std::string chemin, const std::vector<Action>& actions) {
    std::vector<Monster> monstres;
    std::ifstream fichier(chemin.c_str());

    if (!fichier.is_open()) {
        std::cout << "ERREUR : impossible d'ouvrir " << chemin << std::endl;
        exit(1);
    }

    std::string ligne;

    while (getline(fichier, ligne)) {
        if (ligne.length() == 0) continue;
        if (ligne[0] == '#') continue;

        std::vector<std::string> colonnes = decouper(ligne, ';');

        if (colonnes.size() < 8) {
            std::cout << "Ligne monstre ignoree : " << ligne << std::endl;
            continue;
        }

        Categorie cat = texteVersCategorie(colonnes[0]);
        std::string nom = colonnes[1];
        int hp = stringVersEntier(colonnes[2]);
        int objectifMercy = stringVersEntier(colonnes[5]);

        std::vector<std::string> actIds;

        for (int i = 6; i < (int)colonnes.size(); i++) {
            if (colonnes[i] != "-" && colonnes[i] != "") {
                const Action* a = trouverAction(actions, colonnes[i]);

                if (a != NULL) {
                    actIds.push_back(colonnes[i]);
                }
            }
        }

        monstres.push_back(Monster(nom, hp, cat, objectifMercy, actIds));
    }

    fichier.close();
    return monstres;
}