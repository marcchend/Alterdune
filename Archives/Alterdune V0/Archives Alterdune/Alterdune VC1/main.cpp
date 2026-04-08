#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>   // Pour rand(), srand(), exit()
#include <ctime>     // Pour time() → graine aléatoire unique à chaque lancement

#include "Entity.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "ActAction.h"
#include "FileLoader.h"

// ===========================================================
// Fonction : rollDamage
// ===========================================================
// Calcule les dégâts selon la formule du projet :
//   degats = entier aléatoire entre 0 et hpMax du défenseur
// ===========================================================
int rollDamage(int hpMaxDefenseur) {
    // rand() % N donne un nombre entre 0 et N-1
    // On veut 0 à hpMax inclus, donc on fait % (hpMax + 1)
    return rand() % (hpMaxDefenseur + 1);
}

// ===========================================================
// Fonction : runCombat
// ===========================================================
// Gère un combat complet entre le joueur et un monstre.
// On passe le monstre par VALEUR (copie) : ainsi chaque combat
// repart d'un monstre frais, sans altérer le pool de base.
// On passe le joueur par RÉFÉRENCE : ses HP et stats persistent.
// Le catalogue est passé par référence constante (pas de copie).
//
// Retourne true si le joueur gagne, false s'il perd.
// ===========================================================
bool runCombat(Player& joueur, Monster monstre,
               const std::vector<ActAction>& catalogue) {

    std::cout << "\n===================================\n";
    std::cout << " COMBAT : " << joueur.getName()
              << "  vs  " << monstre.getName()
              << " [" << monstre.categoryToString() << "]\n";
    std::cout << "===================================\n";

    // Boucle de combat : continue tant que les deux sont en vie
    while (joueur.isAlive() && monstre.isAlive()) {

        // --- Affichage de l'état actuel ---
        std::cout << "\n";
        joueur.display();
        monstre.display();
        std::cout << "\n";

        // --- Menu de combat ---
        std::cout << "  [1] FIGHT   [2] ACT   [3] ITEM   [4] MERCY\n";
        std::cout << "  Votre choix : ";

        int choix;
        std::cin >> choix;

        // On utilise ce booléen pour savoir si le joueur a vraiment agi
        // (si faux, le monstre ne contre-attaque pas ce tour)
        bool joueurAgi = true;

        // -----------------------------------------------
        // CAS 1 : FIGHT
        // -----------------------------------------------
        if (choix == 1) {
            int degats = rollDamage(monstre.getHpMax());
            monstre.takeDamage(degats);

            if (degats == 0) {
                std::cout << "  Vous attaquez... mais vous ratez !\n";
            } else {
                std::cout << "  Vous infligez " << degats << " degats a "
                          << monstre.getName() << " !\n";
            }

            // Si le monstre est vaincu
            if (!monstre.isAlive()) {
                std::cout << "  " << monstre.getName() << " est vaincu !\n";
                monstre.setWasKilled(true);   // On note qu'il a été tué
                joueur.addVictory(true);      // +1 victoire, +1 kill
                return true;
            }

        // -----------------------------------------------
        // CAS 2 : ACT
        // -----------------------------------------------
        } else if (choix == 2) {

            const std::vector<std::string>& actIds = monstre.getActIds();

            // Vérifie que le monstre a des actions disponibles
            if (actIds.empty()) {
                std::cout << "  Ce monstre n'a aucune action ACT disponible.\n";
                joueurAgi = false;
            } else {
                // Affiche les actions disponibles pour CE monstre
                std::cout << "  Actions disponibles :\n";
                for (int i = 0; i < (int)actIds.size(); i++) {
                    std::cout << "    [" << (i + 1) << "] " << actIds[i] << "\n";
                }
                std::cout << "  Votre choix : ";

                int choixAct;
                std::cin >> choixAct;

                // Vérifie que le choix est valide
                if (choixAct < 1 || choixAct > (int)actIds.size()) {
                    std::cout << "  Choix invalide.\n";
                    joueurAgi = false;
                } else {
                    // On récupère le pointeur vers l'action dans le catalogue
                    const ActAction* action = findAction(catalogue, actIds[choixAct - 1]);

                    if (action == nullptr) {
                        std::cout << "  Action introuvable dans le catalogue.\n";
                        joueurAgi = false;
                    } else {
                        // On applique l'action : modifie la jauge Mercy
                        monstre.applyAct(*action);  // *action = déréférence du pointeur
                    }
                }
            }

        // -----------------------------------------------
        // CAS 3 : ITEM
        // -----------------------------------------------
        } else if (choix == 3) {

            std::vector<Item>& inv = joueur.getInventory();

            // Affiche les items disponibles (avec leur indice)
            bool auMoinsUnItem = false;
            std::cout << "  Inventaire :\n";
            for (int i = 0; i < (int)inv.size(); i++) {
                if (inv[i].isAvailable()) {
                    std::cout << "  [" << (i + 1) << "] ";
                    inv[i].display();
                    auMoinsUnItem = true;
                }
            }

            if (!auMoinsUnItem) {
                std::cout << "  Aucun item disponible.\n";
                joueurAgi = false;
            } else {
                std::cout << "  Choisir un item (0 = annuler) : ";
                int choixItem;
                std::cin >> choixItem;

                if (choixItem == 0) {
                    joueurAgi = false;  // Annulé : le monstre ne contre-attaque pas
                } else if (choixItem >= 1 && choixItem <= (int)inv.size()) {
                    inv[choixItem - 1].useOn(joueur);  // On utilise l'item sur le joueur
                } else {
                    std::cout << "  Choix invalide.\n";
                    joueurAgi = false;
                }
            }

        // -----------------------------------------------
        // CAS 4 : MERCY
        // -----------------------------------------------
        } else if (choix == 4) {

            if (monstre.canBeMercied()) {
                // Mercy disponible : on épargne le monstre
                std::cout << "  Vous epargnez " << monstre.getName() << " !\n";
                monstre.setWasKilled(false);  // Pas tué
                joueur.addVictory(false);     // +1 victoire, +1 épargné
                return true;
            } else {
                std::cout << "  La jauge Mercy n'est pas assez remplie. ("
                          << monstre.getMercy() << "/" << monstre.getMercyGoal() << ")\n";
                joueurAgi = false;
            }

        } else {
            std::cout << "  Choix invalide, recommencez.\n";
            joueurAgi = false;
        }

        // -----------------------------------------------
        // TOUR DU MONSTRE (uniquement si le joueur a agi)
        // -----------------------------------------------
        if (joueurAgi && monstre.isAlive()) {
            monstre.attack(joueur);  // Le monstre attaque le joueur

            if (!joueur.isAlive()) {
                std::cout << "\n  DEFAITE ! " << joueur.getName()
                          << " a ete vaincu...\n";
                return false;
            }
        }

    } // Fin de la boucle de combat

    return false;
}

// ===========================================================
// Fonction : runMainMenu
// ===========================================================
// Gère le menu principal entre les combats.
// Le bestiaire (monstres vaincus) est un vecteur de Monster.
// ===========================================================
void runMainMenu(Player& joueur, std::vector<Monster>& pool,
                 std::vector<Monster>& bestiaire,
                 const std::vector<ActAction>& catalogue) {

    // Boucle du menu principal
    while (true) {
        std::cout << "\n==============================\n";
        std::cout << "        ALTERDUNE\n";
        std::cout << "  Victoires : " << joueur.getNbWins() << " / 10\n";
        std::cout << "==============================\n";
        std::cout << "  [1] Bestiaire\n";
        std::cout << "  [2] Demarrer un combat\n";
        std::cout << "  [3] Statistiques\n";
        std::cout << "  [4] Items\n";
        std::cout << "  [5] Quitter\n";
        std::cout << "  Votre choix : ";

        int choix;
        std::cin >> choix;

        // -----------------------------------------------
        // CAS 1 : Bestiaire
        // -----------------------------------------------
        if (choix == 1) {
            std::cout << "\n=== Bestiaire ===\n";
            if (bestiaire.empty()) {
                std::cout << "  (Aucun monstre vaincu pour l'instant)\n";
            } else {
                for (int i = 0; i < (int)bestiaire.size(); i++) {
                    std::cout << "  " << (i + 1) << ". "
                              << bestiaire[i].getName()
                              << " [" << bestiaire[i].categoryToString() << "]"
                              << " | HP max : " << bestiaire[i].getHpMax()
                              << " | Resultat : "
                              << (bestiaire[i].getWasKilled() ? "Tue" : "Epargne")
                              << "\n";
                }
            }

        // -----------------------------------------------
        // CAS 2 : Demarrer un combat
        // -----------------------------------------------
        } else if (choix == 2) {

            if (pool.empty()) {
                std::cout << "  Aucun monstre dans le pool !\n";
                continue;
            }

            // Choisit un monstre aléatoirement dans le pool
            int index = rand() % (int)pool.size();

            // On passe une COPIE du monstre à runCombat
            // (pour ne pas modifier le monstre original dans le pool)
            Monster monstrechoisi = pool[index];

            bool victoire = runCombat(joueur, monstrechoisi, catalogue);

            if (victoire) {
                // On ajoute le monstre au bestiaire
                bestiaire.push_back(monstrechoisi);

                std::cout << "\n  Victoire ! (" << joueur.getNbWins() << "/10)\n";

                // Condition de fin : 10 victoires
                if (joueur.getNbWins() >= 10) {
                    return;  // On sort du menu pour afficher la fin
                }
            } else {
                // Défaite → game over
                std::cout << "  GAME OVER.\n";
                exit(0);
            }

        // -----------------------------------------------
        // CAS 3 : Statistiques
        // -----------------------------------------------
        } else if (choix == 3) {
            joueur.displayStats();

        // -----------------------------------------------
        // CAS 4 : Items (hors combat)
        // -----------------------------------------------
        } else if (choix == 4) {
            joueur.displayInventory();

            std::vector<Item>& inv = joueur.getInventory();
            if (!inv.empty()) {
                std::cout << "  Utiliser un item ? (numero, 0 = non) : ";
                int idx;
                std::cin >> idx;
                if (idx >= 1 && idx <= (int)inv.size()) {
                    inv[idx - 1].useOn(joueur);
                }
            }

        // -----------------------------------------------
        // CAS 5 : Quitter
        // -----------------------------------------------
        } else if (choix == 5) {
            std::cout << "  Au revoir !\n";
            exit(0);

        } else {
            std::cout << "  Choix invalide.\n";
        }
    }
}

// ===========================================================
// POINT D'ENTRÉE : main()
// ===========================================================
int main() {

    // Initialise le générateur aléatoire avec l'heure courante
    // Sans ça, rand() donnerait toujours la même séquence
    srand((unsigned int)time(nullptr));

    // --- Titre ---
    std::cout << "===========================\n";
    std::cout << "       ALTERDUNE\n";
    std::cout << "===========================\n";

    // --- Saisie du nom du personnage ---
    std::string nomJoueur;
    std::cout << "Entrez le nom de votre personnage : ";
    std::cin >> nomJoueur;

    // --- Construction du catalogue d'actions ACT ---
    // On appelle la fonction définie dans ActAction.cpp
    std::vector<ActAction> catalogue = buildCatalogue();

    // --- Chargement des fichiers CSV ---
    std::vector<Item>    items    = FileLoader::loadItems("data/items.csv");
    std::vector<Monster> monsters = FileLoader::loadMonsters("data/monsters.csv", catalogue);

    // --- Création du joueur (100 HP) ---
    Player joueur(nomJoueur, 100);

    // On transfère les items chargés dans l'inventaire du joueur
    for (int i = 0; i < (int)items.size(); i++) {
        joueur.addItem(items[i]);
    }

    // --- Résumé de départ ---
    std::cout << "\n--- Bienvenue, " << joueur.getName() << " ! ---\n";
    joueur.display();
    joueur.displayInventory();

    // --- Bestiaire (rempli au fil des combats) ---
    std::vector<Monster> bestiaire;

    // --- Lancement du menu principal ---
    runMainMenu(joueur, monsters, bestiaire, catalogue);

    // --- Fin de partie (10 victoires atteintes) ---
    std::cout << "\n===================================\n";
    std::cout << "   10 VICTOIRES ! PARTIE TERMINEE\n";
    std::cout << "===================================\n";
    std::cout << "  FIN : " << joueur.getEndingType() << "\n";

    // Description selon la fin obtenue
    if (joueur.getEndingType() == "Genocidaire") {
        std::cout << "  Vous avez tue tous vos adversaires. La legende vous craint.\n";
    } else if (joueur.getEndingType() == "Pacifiste") {
        std::cout << "  Vous avez epargne tout le monde. La paix regne.\n";
    } else {
        std::cout << "  Ni tout blanc ni tout noir. Une fin nuancee.\n";
    }

    return 0;
}
