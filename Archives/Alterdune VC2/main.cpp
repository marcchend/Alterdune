#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Entity.h"
#include "Player.h"
#include "Monster.h"
#include "ActAction.h"
#include "FileLoader.h"

// TODO : #include "Item.h"  <- a activer quand l'inventaire sera implemente

// ===========================================================
// Fonction : rollDamage
// Calcule les degats : entier aleatoire entre 0 et hpMax
// ===========================================================
int rollDamage(int hpMaxDefenseur) {
    return rand() % (hpMaxDefenseur + 1);
}

// ===========================================================
// Fonction : runCombat
// Gere un combat complet (joueur vs monstre).
// Retourne true si victoire, false si defaite.
// ===========================================================
bool runCombat(Player& joueur, Monster monstre,
               const std::vector<ActAction>& catalogue) {

    std::cout << "\n===================================\n";
    std::cout << " COMBAT : " << joueur.getName()
              << "  vs  " << monstre.getName()
              << " [" << monstre.categoryToString() << "]\n";
    std::cout << "===================================\n";

    while (joueur.isAlive() && monstre.isAlive()) {

        // Affichage de l'etat
        std::cout << "\n";
        joueur.display();
        monstre.display();
        std::cout << "\n";

        // Menu de combat
        std::cout << "  [1] FIGHT   [2] ACT   [3] ITEM   [4] MERCY\n";
        std::cout << "  Votre choix : ";

        int choix;
        std::cin >> choix;

        bool joueurAgi = true;

        // -----------------------------------------------
        // CAS 1 : FIGHT  <- FONCTIONNEL
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

            if (!monstre.isAlive()) {
                std::cout << "  " << monstre.getName() << " est vaincu !\n";
                monstre.setWasKilled(true);
                joueur.addVictory(true);
                return true;
            }

        // -----------------------------------------------
        // CAS 2 : ACT  <- FONCTIONNEL
        // -----------------------------------------------
        } else if (choix == 2) {

            const std::vector<std::string>& actIds = monstre.getActIds();

            if (actIds.empty()) {
                std::cout << "  Ce monstre n'a aucune action ACT disponible.\n";
                joueurAgi = false;
            } else {
                std::cout << "  Actions disponibles :\n";
                for (int i = 0; i < (int)actIds.size(); i++) {
                    std::cout << "    [" << (i + 1) << "] " << actIds[i] << "\n";
                }
                std::cout << "  Votre choix : ";

                int choixAct;
                std::cin >> choixAct;

                if (choixAct < 1 || choixAct > (int)actIds.size()) {
                    std::cout << "  Choix invalide.\n";
                    joueurAgi = false;
                } else {
                    const ActAction* action = findAction(catalogue, actIds[choixAct - 1]);
                    if (action == nullptr) {
                        std::cout << "  Action introuvable dans le catalogue.\n";
                        joueurAgi = false;
                    } else {
                        monstre.applyAct(*action);
                    }
                }
            }

        // -----------------------------------------------
        // CAS 3 : ITEM  <- TODO
        // -----------------------------------------------
        } else if (choix == 3) {
            std::cout << "  [TODO] Le systeme d'inventaire n'est pas encore implemente.\n";
            joueurAgi = false;

        // -----------------------------------------------
        // CAS 4 : MERCY  <- TODO
        // -----------------------------------------------
        } else if (choix == 4) {
            std::cout << "  [TODO] La condition MERCY n'est pas encore implementee.\n";
            std::cout << "  (Mercy actuelle : " << monstre.getMercy()
                      << "/" << monstre.getMercyGoal() << ")\n";
            joueurAgi = false;

        } else {
            std::cout << "  Choix invalide.\n";
            joueurAgi = false;
        }

        // Tour du monstre
        if (joueurAgi && monstre.isAlive()) {
            monstre.attack(joueur);

            if (!joueur.isAlive()) {
                std::cout << "\n  DEFAITE ! " << joueur.getName()
                          << " a ete vaincu...\n";
                return false;
            }
        }
    }

    return false;
}

// ===========================================================
// Fonction : runMainMenu
// ===========================================================
void runMainMenu(Player& joueur, std::vector<Monster>& pool,
                 std::vector<Monster>& bestiaire,
                 const std::vector<ActAction>& catalogue) {

    while (true) {
        std::cout << "\n==============================\n";
        std::cout << "        ALTERDUNE\n";
        std::cout << "  Victoires : " << joueur.getNbWins() << " / 10\n";
        std::cout << "==============================\n";
        std::cout << "  [1] Bestiaire\n";
        std::cout << "  [2] Demarrer un combat\n";
        std::cout << "  [3] Statistiques\n";
        std::cout << "  [4] Items          (TODO)\n";
        std::cout << "  [5] Quitter\n";
        std::cout << "  Votre choix : ";

        int choix;
        std::cin >> choix;

        if (choix == 1) {
            // Bestiaire
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

        } else if (choix == 2) {
            // Combat aleatoire
            if (pool.empty()) { std::cout << "  Aucun monstre disponible.\n"; continue; }

            int index = rand() % (int)pool.size();
            Monster monstrechoisi = pool[index];

            bool victoire = runCombat(joueur, monstrechoisi, catalogue);

            if (victoire) {
                bestiaire.push_back(monstrechoisi);
                std::cout << "\n  Victoire ! (" << joueur.getNbWins() << "/10)\n";
                if (joueur.getNbWins() >= 10) return;
            } else {
                std::cout << "  GAME OVER.\n";
                exit(0);
            }

        } else if (choix == 3) {
            // Statistiques
            joueur.displayStats();

        } else if (choix == 4) {
            // Items : non implemente
            std::cout << "\n  [TODO] L'inventaire n'est pas encore implemente.\n";

        } else if (choix == 5) {
            std::cout << "  Au revoir !\n";
            exit(0);

        } else {
            std::cout << "  Choix invalide.\n";
        }
    }
}

// ===========================================================
// POINT D'ENTREE : main()
// ===========================================================
int main() {

    srand((unsigned int)time(nullptr));

    std::cout << "===========================\n";
    std::cout << "       ALTERDUNE\n";
    std::cout << "===========================\n";

    std::string nomJoueur;
    std::cout << "Entrez le nom de votre personnage : ";
    std::cin >> nomJoueur;

    // Catalogue ACT
    std::vector<ActAction> catalogue = buildCatalogue();

    // Chargement des monstres (items non charges : TODO)
    std::vector<Monster> monsters = FileLoader::loadMonsters("data/monsters.csv", catalogue);

    // TODO : charger items.csv et les ajouter a l'inventaire du joueur

    // Creation du joueur
    Player joueur(nomJoueur, 100);

    // Resume de depart
    std::cout << "\n--- Bienvenue, " << joueur.getName() << " ! ---\n";
    joueur.display();
    std::cout << "  Inventaire : (TODO)\n";

    // Bestiaire (rempli au fil des combats)
    std::vector<Monster> bestiaire;

    // Menu principal
    runMainMenu(joueur, monsters, bestiaire, catalogue);

    // Fin de partie
    std::cout << "\n===================================\n";
    std::cout << "   10 VICTOIRES ! PARTIE TERMINEE\n";
    std::cout << "===================================\n";
    // TODO : afficher la fin selon getEndingType() (Genocidaire / Pacifiste / Neutre)
    std::cout << "  (TODO : fins multiples a implementer)\n";

    return 0;
}
