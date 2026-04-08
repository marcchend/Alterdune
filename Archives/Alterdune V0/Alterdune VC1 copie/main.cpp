#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include "Action.h"
#include "Item.h"
#include "Monster.h"
#include "Player.h"

// ===========================================================
// FONCTIONS POUR LIRE LES FICHIERS (simplifiées)
// ===========================================================

std::vector<std::string> decouper(std::string ligne, char separateur) {
    std::vector<std::string> morceaux;
    std::stringstream flux(ligne);
    std::string morceau;
    
    while (getline(flux, morceau, separateur)) {
        morceaux.push_back(morceau);  // plus besoin de enleverEspaces
    }
    
    return morceaux;
}

Categorie texteVersCategorie(std::string texte) {
    if (texte == "NORMAL") return NORMAL;
    if (texte == "MINIBOSS") return MINIBOSS;
    if (texte == "BOSS") return BOSS;
    
    std::cerr << "ERREUR: Categorie inconnue " << texte << std::endl;
    exit(1);
}

std::vector<Item> lireItems(std::string chemin) {
    std::vector<Item> items;
    std::ifstream fichier(chemin.c_str());
    
    if (!fichier.is_open()) {
        std::cerr << "ERREUR: Impossible d'ouvrir " << chemin << std::endl;
        exit(1);
    }
    
    std::string ligne;
    while (getline(fichier, ligne)) {
        if (ligne.empty() || ligne[0] == '#') continue;
        
        std::vector<std::string> colonnes = decouper(ligne, ';');
        if (colonnes.size() < 4) continue;
        
        std::string nom = colonnes[0];
        int valeur = atoi(colonnes[2].c_str());
        int quantite = atoi(colonnes[3].c_str());
        
        items.push_back(Item(nom, valeur, quantite));
    }
    
    fichier.close();
    return items;
}

std::vector<Monster> lireMonsters(std::string chemin, const std::vector<Action>& catalogue) {
    std::vector<Monster> monsters;
    std::ifstream fichier(chemin.c_str());
    
    if (!fichier.is_open()) {
        std::cerr << "ERREUR: Impossible d'ouvrir " << chemin << std::endl;
        exit(1);
    }
    
    std::string ligne;
    while (getline(fichier, ligne)) {
        if (ligne.empty() || ligne[0] == '#') continue;
        
        std::vector<std::string> colonnes = decouper(ligne, ';');
        if (colonnes.size() < 8) continue;
        
        Categorie cat = texteVersCategorie(colonnes[0]);
        std::string nom = colonnes[1];
        int hp = atoi(colonnes[2].c_str());
        int objectifMercy = atoi(colonnes[5].c_str());
        
        std::vector<std::string> actIds;
        for (int i = 6; i < (int)colonnes.size(); i++) {
            if (colonnes[i] != "-" && !colonnes[i].empty()) {
                const Action* a = trouverAction(catalogue, colonnes[i]);
                if (a != NULL) {
                    actIds.push_back(colonnes[i]);
                }
            }
        }
        
        monsters.push_back(Monster(nom, hp, cat, objectifMercy, actIds));
    }
    
    fichier.close();
    return monsters;
}

// ===========================================================
// COMBAT
// ===========================================================

bool combat(Player& joueur, Monster monstre) {
    std::cout << "\n============================\n";
    std::cout << "  COMBAT : " << joueur.getNom() << " vs " << monstre.getNom() << "\n";
    std::cout << "============================\n";
    
    while (joueur.estVivant() && monstre.estVivant()) {
        
        std::cout << "\n  " << joueur.getNom() << " : " << joueur.getHp() 
                  << "/" << joueur.getHpMax() << " HP\n";
        std::cout << "  " << monstre.getNom() << " : " << monstre.getHp() 
                  << "/" << monstre.getHpMax() << " HP\n\n";
        
        std::cout << "1. Fight\n";
        std::cout << "2. Act\n";
        std::cout << "3. Item\n";
        std::cout << "4. Mercy\n";
        std::cout << "Choix : ";
        int choix;
        std::cin >> choix;
        
        bool joueurAgit = true;
        
        if (choix == 1) {
            // FIGHT
            int degats = rand() % (monstre.getHpMax() + 1);
            monstre.prendreDegats(degats);
            
            if (degats == 0) {
                std::cout << "  Vous attaquez mais ratez !\n";
            } else {
                std::cout << "  Vous infligez " << degats << " degats a " 
                          << monstre.getNom() << " !\n";
            }
            
            if (!monstre.estVivant()) {
                std::cout << "  " << monstre.getNom() << " est vaincu !\n";
                monstre.setTue(true);
                joueur.ajouterVictoire(true);
                return true;
            }
            
        } else if (choix == 2) {
            std::cout << "\n  [PAS ENCORE FAIT] Systeme ACT\n";
            joueurAgit = false;
            
        } else if (choix == 3) {
            std::cout << "\n  [PAS ENCORE FAIT] Systeme ITEM\n";
            joueurAgit = false;
            
        } else if (choix == 4) {
            std::cout << "\n  [PAS ENCORE FAIT] Systeme MERCY\n";
            joueurAgit = false;
            
        } else {
            std::cout << "  Choix invalide.\n";
            joueurAgit = false;
        }
        
        if (joueurAgit && monstre.estVivant()) {
            monstre.attaquer(joueur);
            if (!joueur.estVivant()) {
                std::cout << "\n  DEFAITE ! Vous avez ete vaincu...\n";
                return false;
            }
        }
    }
    
    return false;
}

// ===========================================================
// MENU PRINCIPAL
// ===========================================================

void menuPrincipal(Player& joueur, std::vector<Monster>& monstres, std::vector<Monster>& bestiaire) {
    while (true) {
        std::cout << "\n==============================\n";
        std::cout << "      ALTERDUNE - Menu\n";
        std::cout << "  Victoires : " << joueur.getVictoires() << "/10\n";
        std::cout << "==============================\n";
        std::cout << "1. Bestiaire\n";
        std::cout << "2. Combattre\n";
        std::cout << "3. Stats\n";
        std::cout << "4. Items\n";
        std::cout << "5. Quitter\n";
        std::cout << "Choix : ";
        int choix;
        std::cin >> choix;
        
        if (choix == 1) {
            std::cout << "\n  [PAS ENCORE FAIT] Bestiaire\n";
            
        } else if (choix == 2) {
            if (monstres.empty()) {
                std::cout << "  Aucun monstre disponible.\n";
                continue;
            }
            
            // Prend le premier monstre
            Monster adversaire = monstres[0];
            
            bool gagne = combat(joueur, adversaire);
            if (gagne) {
                bestiaire.push_back(adversaire);
                if (joueur.getVictoires() >= 10) break;
            } else {
                std::cout << "  Game Over.\n";
                exit(0);
            }
            
        } else if (choix == 3) {
            joueur.afficherStats();
            
        } else if (choix == 4) {
            std::cout << "\n  [PAS ENCORE FAIT] Systeme d'items\n";
            
        } else if (choix == 5) {
            std::cout << "  Au revoir !\n";
            return;
        }
    }
}

// ===========================================================
// MAIN
// ===========================================================

int main() {
    // Initialise l'aleatoire
    srand(time(NULL));
    
    // Construit le catalogue d'actions
    std::vector<Action> actions = construireCatalogue();
    
    // Nom du joueur
    std::string nomJoueur;
    std::cout << "=== ALTERDUNE ===\n";
    std::cout << "Nom du personnage : ";
    std::cin >> nomJoueur;
    
    // Charge les fichiers
    std::vector<Item> items = lireItems("items.csv");
    std::vector<Monster> monstres = lireMonsters("monsters.csv", actions);
    
    // Cree le joueur
    Player joueur(nomJoueur, 100);
    
    // Ajoute les items (non utilise mais ca compile)
    for (int i = 0; i < (int)items.size(); i++) {
        joueur.ajouterItem(items[i]);
    }
    
    // Message de bienvenue
    std::cout << "\n--- Bienvenue, " << joueur.getNom() << " ---\n";
    joueur.afficher();
    std::cout << "\n  [INFO] Seul FIGHT fonctionne. ACT/ITEM/MERCY plus tard.\n";
    
    // Bestiaire
    std::vector<Monster> bestiaire;
    
    // Menu principal
    menuPrincipal(joueur, monstres, bestiaire);
    
    // Fin de partie
    std::cout << "\n============================\n";
    std::cout << "  10 victoires atteintes !\n";
    std::cout << "  FIN : " << joueur.getTypeFin() << "\n";
    std::cout << "============================\n";
    
    return 0;
}