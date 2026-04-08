#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

#include "Action.h"
#include "Item.h"
#include "Monster.h"
#include "Player.h"

// ===========================================================
// FONCTIONS POUR LIRE LES FICHIERS (sans stringstream)
// ===========================================================

// Convertit un string en entier (sans atoi)
int stringVersEntier(std::string s) {
    int resultat = 0;
    for (int i = 0; i < (int)s.length(); i++) {
        resultat = resultat * 10 + (s[i] - '0');
    }
    return resultat;
}

// Decoupe une ligne avec un separateur (sans stringstream)
std::vector<std::string> decouper(std::string ligne, char separateur) {
    std::vector<std::string> morceaux;
    std::string morceau = "";
    int nbMorceaux = 0;
    
    // Parcourir la ligne
    for (int i = 0; i < (int)ligne.length(); i++) {
        if (ligne[i] == separateur) {
            // Agrandir le tableau et ajouter le morceau
            morceaux.resize(nbMorceaux + 1);
            morceaux[nbMorceaux] = morceau;
            nbMorceaux++;
            morceau = "";
        } else {
            morceau = morceau + ligne[i];
        }
    }
    
    // Ajouter le dernier morceau
    morceaux.resize(nbMorceaux + 1);
    morceaux[nbMorceaux] = morceau;
    
    return morceaux;
}

Categorie texteVersCategorie(std::string texte) {
    if (texte == "NORMAL") return NORMAL;
    if (texte == "MINIBOSS") return MINIBOSS;
    if (texte == "BOSS") return BOSS;
    
    std::cerr << "ERREUR: Categorie inconnue " << texte << std::endl;
    exit(1);
}

void lireItems(std::string chemin, std::vector<Item>& items) {
    std::ifstream fichier;
    fichier.open(chemin.c_str());
    
    if (!fichier.is_open()) {
        std::cerr << "ERREUR: Impossible d'ouvrir " << chemin << std::endl;
        exit(1);
    }
    
    std::string ligne;
    while (true) {
        std::getline(fichier, ligne);
        if (fichier.eof()) break;
        
        if (ligne.length() == 0) continue;
        if (ligne[0] == '#') continue;
        
        std::vector<std::string> colonnes = decouper(ligne, ';');
        if (colonnes.size() < 4) continue;
        
        std::string nom = colonnes[0];
        int valeur = stringVersEntier(colonnes[2]);
        int quantite = stringVersEntier(colonnes[3]);
        
        // Ajouter l'item
        int taille = (int)items.size();
        items.resize(taille + 1);
        items[taille] = Item(nom, valeur, quantite);
    }
    
    fichier.close();
}

void lireMonsters(std::string chemin, const std::vector<Action>& catalogue, std::vector<Monster>& monsters) {
    std::ifstream fichier;
    fichier.open(chemin.c_str());
    
    if (!fichier.is_open()) {
        std::cerr << "ERREUR: Impossible d'ouvrir " << chemin << std::endl;
        exit(1);
    }
    
    std::string ligne;
    while (true) {
        std::getline(fichier, ligne);
        if (fichier.eof()) break;
        
        if (ligne.length() == 0) continue;
        if (ligne[0] == '#') continue;
        
        std::vector<std::string> colonnes = decouper(ligne, ';');
        if (colonnes.size() < 8) continue;
        
        Categorie cat = texteVersCategorie(colonnes[0]);
        std::string nom = colonnes[1];
        int hp = stringVersEntier(colonnes[2]);
        int objectifMercy = stringVersEntier(colonnes[5]);
        
        std::vector<std::string> actIds;
        int nbActs = 0;
        for (int i = 6; i < (int)colonnes.size(); i++) {
            if (colonnes[i] != "-" && colonnes[i].length() > 0) {
                const Action* a = trouverAction(catalogue, colonnes[i]);
                if (a != NULL) {
                    actIds.resize(nbActs + 1);
                    actIds[nbActs] = colonnes[i];
                    nbActs++;
                }
            }
        }
        
        // Ajouter le monstre
        int taille = (int)monsters.size();
        monsters.resize(taille + 1);
        monsters[taille] = Monster(nom, hp, cat, objectifMercy, actIds);
    }
    
    fichier.close();
}

// ===========================================================
// COMBAT
// ===========================================================

bool combat(Player& joueur, Monster monstre, const std::vector<Action>& actions) {
    std::cout << "\n============================\n";
    std::cout << "  COMBAT : " << joueur.getNom() << " vs " << monstre.getNom() << "\n";
    std::cout << "============================\n";
    
    while (joueur.estVivant() && monstre.estVivant()) {
        
        std::cout << "\n  " << joueur.getNom() << " : " << joueur.getHp() 
                  << "/" << joueur.getHpMax() << " HP\n";
        std::cout << "  " << monstre.getNom() << " : " << monstre.getHp() 
                  << "/" << monstre.getHpMax() << " HP\n\n";
        
        std::cout << "  [1] FIGHT   [2] ACT   [3] ITEM   [4] MERCY\n";
        std::cout << "  Choix : ";
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
                monstre.setEpargne(false);
                joueur.ajouterVictoire(true);
                return true;
            }
            
        } else if (choix == 2) {
            // ACT : afficher les actions disponibles du monstre
            std::vector<std::string> acts = monstre.getActionsDispo();
            std::cout << "\n  Actions disponibles :\n";
            for (int i = 0; i < (int)acts.size(); i++) {
                const Action* a = trouverAction(actions, acts[i]);
                if (a != NULL) {
                    std::cout << "  [" << (i + 1) << "] " << a->getId();
                    // On affiche si l'action est positive ou negative pour donner un indice
                    if (a->getImpact() > 0) {
                        std::cout << " (+mercy)";
                    } else {
                        std::cout << " (-mercy)";
                    }
                    std::cout << "\n";
                }
            }
            std::cout << "  Choix : ";
            int choixAct;
            std::cin >> choixAct;

            if (choixAct >= 1 && choixAct <= (int)acts.size()) {
                const Action* a = trouverAction(actions, acts[choixAct - 1]);
                if (a != NULL) {
                    // Afficher le texte drole de l'action
                    std::cout << "\n  " << a->getTexte() << "\n";

                    // Modifier la jauge mercy du monstre
                    monstre.ajouterMercy(a->getImpact());

                    std::cout << "  Mercy de " << monstre.getNom()
                              << " : " << monstre.getMercy()
                              << "/" << monstre.getObjectifMercy() << "\n";
                }
            } else {
                std::cout << "  Choix invalide.\n";
                joueurAgit = false;
            }
            
        } else if (choix == 3) {
            // ITEM : afficher l'inventaire et utiliser un item
            joueur.afficherInventaire();

            // Verifier qu'il y a des items
            if (joueur.getNbItems() == 0) {
                std::cout << "  Inventaire vide !\n";
                joueurAgit = false;
            } else {
                std::cout << "  Quel item utiliser ? (0 pour annuler) : ";
                int choixItem;
                std::cin >> choixItem;

                if (choixItem == 0) {
                    joueurAgit = false;
                } else {
                    // utiliserItem prend un index 0-base, le joueur tape 1-base
                    bool ok = joueur.utiliserItem(choixItem - 1);
                    if (!ok) {
                        joueurAgit = false;
                    }
                }
            }
            
        } else if (choix == 4) {
            // MERCY : epargner le monstre si la jauge est pleine
            if (monstre.mercyEstPlein()) {
                std::cout << "\n  " << monstre.getNom()
                          << " accepte d'etre epargne. Combat termine !\n";
                monstre.setTue(false);
                monstre.setEpargne(true);
                joueur.ajouterVictoire(false); // false = pas tue = epargne
                return true;
            } else {
                std::cout << "\n  Mercy insuffisant ("
                          << monstre.getMercy() << "/"
                          << monstre.getObjectifMercy()
                          << "). Utilisez ACT pour augmenter la jauge !\n";
                joueurAgit = false;
            }
            
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

void menuPrincipal(Player& joueur, std::vector<Monster>& monstres, std::vector<Monster>& bestiaire, const std::vector<Action>& actions) {
    while (true) {
        std::cout << "\n==============================\n";
        std::cout << "      ALTERDUNE - Menu\n";
        std::cout << "  Victoires : " << joueur.getVictoires() << "/10\n";
        std::cout << "==============================\n";
        std::cout << "  [1] Bestiaire\n";
        std::cout << "  [2] Combattre\n";
        std::cout << "  [3] Stats\n";
        std::cout << "  [4] Items\n";
        std::cout << "  [5] Quitter\n";
        std::cout << "  Choix : ";
        int choix;
        std::cin >> choix;
        
        if (choix == 1) {
            // BESTIAIRE : afficher tous les monstres vaincus
            std::cout << "\n  === Bestiaire (" << bestiaire.size() << " monstres) ===\n";
            if (bestiaire.size() == 0) {
                std::cout << "  Aucun monstre vaincu pour l'instant.\n";
            }
            for (int i = 0; i < (int)bestiaire.size(); i++) {
                std::cout << "\n  " << (i + 1) << ". " << bestiaire[i].getNom()
                          << " [" << bestiaire[i].categorieEnTexte() << "]"
                          << " - HP max : " << bestiaire[i].getHpMax();
                if (bestiaire[i].getEpargne()) {
                    std::cout << " - Epargne\n";
                } else {
                    std::cout << " - Tue\n";
                }
            }
            
        } else if (choix == 2) {
            if (monstres.size() == 0) {
                std::cout << "  Aucun monstre disponible.\n";
                continue;
            }
            
            // Choisir un monstre aleatoire dans la liste
            int index = rand() % (int)monstres.size();
            Monster adversaire = monstres[index];
            
            bool gagne = combat(joueur, adversaire, actions);
            if (gagne) {
                // Ajouter au bestiaire
                int taille = (int)bestiaire.size();
                bestiaire.resize(taille + 1);
                bestiaire[taille] = adversaire;
                
                if (joueur.getVictoires() >= 10) break;
            } else {
                std::cout << "  Game Over.\n";
                exit(0);
            }
            
        } else if (choix == 3) {
            joueur.afficherStats();
            
        } else if (choix == 4) {
            // Afficher l'inventaire et proposer d'utiliser un item hors combat
            joueur.afficherInventaire();
            std::cout << "  Utiliser un item ? (numero, 0 pour annuler) : ";
            int choixItem;
            std::cin >> choixItem;
            if (choixItem != 0) {
                joueur.utiliserItem(choixItem - 1);
            }
            
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
    std::vector<Action> actions;
    construireCatalogue(actions);
    
    // Nom du joueur
    std::string nomJoueur;
    std::cout << "=== ALTERDUNE ===\n";
    std::cout << "Nom du personnage : ";
    std::cin >> nomJoueur;
    
    // Charge les fichiers
    std::vector<Item> items;
    lireItems("items.csv", items);
    
    std::vector<Monster> monstres;
    lireMonsters("monsters.csv", actions, monstres);
    
    // Cree le joueur
    Player joueur(nomJoueur, 100);
    
    // Ajoute les items
    for (int i = 0; i < (int)items.size(); i++) {
        joueur.ajouterItem(items[i]);
    }
    
    // Message de bienvenue
    std::cout << "\n--- Bienvenue, " << joueur.getNom() << " ---\n";
    joueur.afficher();
    joueur.afficherInventaire();
    
    // Bestiaire
    std::vector<Monster> bestiaire;
    
    // Menu principal
    menuPrincipal(joueur, monstres, bestiaire, actions);
    
    // Fin de partie
    std::cout << "\n============================\n";
    std::cout << "  10 victoires atteintes !\n";
    std::cout << "  FIN : " << joueur.getTypeFin() << "\n";
    std::cout << "============================\n";
    
    return 0;
}