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

// TODO : #include "Item.h"  <- a activer quand Item sera implemente

// ===========================================================
// Fonction : rollDamage
// ===========================================================
// Formule du projet : entier aleatoire entre 0 et hpMax du defenseur
// ===========================================================
int rollDamage(int hpMaxDefenseur) {
    return rand() % (hpMaxDefenseur + 1);
}

// ===========================================================
// Fonction : runCombat
// ===========================================================
// Gere un combat complet joueur vs monstre.
// Le monstre est passe par VALEUR (copie) : chaque combat
// repart d'un monstre avec ses HP max, sans modifier le pool.
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

        // Affichage de l'etat courant
        std::cout << "\n";
        joueur.display();
        monstre.display();
        std::cout << "\n";

        std::cout << "  [1] FIGHT   [2] ACT   [3] ITEM   [4] MERCY\n";
        std::cout << "  Votre choix : ";

        int choix;
        std::cin >> choix;

        // joueurAgi = false si le joueur annule ou fait un choix invalide
        // Dans ce cas le monstre ne contre-attaque pas ce tour
        bool joueurAgi = true;

        // -----------------------------------------------
        // CAS 1 : FIGHT  <- FONCTIONNEL
        // -----------------------------------------------
        if (choix == 1) {

            int degats = rollDamage(monstre.getHpMax());
            monstre.takeDamage(degats);

            if (degats == 0) {
                std::cout << "  Vous attaquez " << monstre.getName()
                          << " mais vous ratez !\n";
            } else {
                std::cout << "  Vous infligez " << degats << " degats a "
                          << monstre.getName() << " !\n";
            }

            // Verifie si le monstre est mort
            if (!monstre.isAlive()) {
                std::cout << "  " << monstre.getName() << " est vaincu !\n";
                monstre.setWasKilled(true);   // On retient qu'il a ete tue
                joueur.addVictory(true);      // +1 victoire, +1 kill
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
                // Affiche uniquement les actions de CE monstre
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
                    // findAction retourne un pointeur, nullptr si introuvable
                    const ActAction* action = findAction(catalogue, actIds[choixAct - 1]);
                    if (action == nullptr) {
                        std::cout << "  Action introuvable dans le catalogue.\n";
                        joueurAgi = false;
                    } else {
                        // *action = dereference du pointeur pour obtenir l'ActAction
                        monstre.applyAct(*action);
                    }
                }
            }

        // -----------------------------------------------
        // CAS 3 : ITEM  <- TODO
        // -----------------------------------------------
        } else if (choix == 3) {
            std::cout << "  [TODO] L'inventaire n'est pas encore implemente.\n";
            joueurAgi = false;

        // -----------------------------------------------
        // CAS 4 : MERCY  <- TODO
        // -----------------------------------------------
        } else if (choix == 4) {
            std::cout << "  [TODO] La condition MERCY n'est pas encore implementee.\n";
            std::cout << "  (Mercy actuelle : " << monstre.getMercy()
                      << " / " << monstre.getMercyGoal() << ")\n";
            joueurAgi = false;

        } else {
            std::cout << "  Choix invalide, recommencez.\n";
            joueurAgi = false;
        }

        // -----------------------------------------------
        // TOUR DU MONSTRE (seulement si le joueur a vraiment agi)
        // -----------------------------------------------
        if (joueurAgi && monstre.isAlive()) {
            monstre.attack(joueur);

            if (!joueur.isAlive()) {
                std::cout << "\n  DEFAITE ! " << joueur.getName()
                          << " a ete vaincu...\n";
                return false;
            }
        }

    } // fin boucle de combat

    return false;
}

// ===========================================================
// Fonction : runMainMenu
// ===========================================================
// Gere le menu principal entre les combats.
// bestiaire = liste des monstres deja vaincus (grandit a chaque victoire)
// ===========================================================
void runMainMenu(Player& joueur,
                 std::vector<Monster>& pool,
                 std::vector<Monster>& bestiaire,
                 const std::vector<ActAction>& catalogue) {

    while (true) {

        std::cout << "\n==============================\n";
        std::cout << "         ALTERDUNE\n";
        std::cout << "   Victoires : " << joueur.getNbWins() << " / 10\n";
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
        // OPTION 1 : Bestiaire  <- FONCTIONNEL
        // -----------------------------------------------
        if (choix == 1) {

            std::cout << "\n=== Bestiaire (" << bestiaire.size()
                      << " monstre(s) vaincu(s)) ===\n";

            if (bestiaire.empty()) {
                std::cout << "  (Aucun monstre vaincu pour l'instant)\n";
            } else {
                for (int i = 0; i < (int)bestiaire.size(); i++) {
                    std::string resultat = bestiaire[i].getWasKilled() ? "Tue" : "Epargne";
                    std::cout << "  " << (i + 1) << ". "
                              << bestiaire[i].getName()
                              << " [" << bestiaire[i].categoryToString() << "]"
                              << "  HP max : " << bestiaire[i].getHpMax()
                              << "  --> " << resultat << "\n";
                }
            }

        // -----------------------------------------------
        // OPTION 2 : Demarrer un combat  <- FONCTIONNEL
        // -----------------------------------------------
        } else if (choix == 2) {

            if (pool.empty()) {
                std::cout << "  Aucun monstre disponible dans le pool.\n";
                continue;
            }

            // Tirage aleatoire dans le pool de monstres
            int index = rand() % (int)pool.size();

            // On passe une COPIE du monstre : le pool n'est pas modifie
            Monster monstrechoisi = pool[index];

            bool victoire = runCombat(joueur, monstrechoisi, catalogue);

            if (victoire) {
                // On ajoute la copie (avec son etat final) au bestiaire
                bestiaire.push_back(monstrechoisi);
                std::cout << "\n  Victoire ! Total : " << joueur.getNbWins() << "/10\n";

                // Condition de fin de partie
                if (joueur.getNbWins() >= 10) {
                    return;  // On sort du menu pour aller a l'ecran de fin
                }

            } else {
                // Defaite = game over immediat
                std::cout << "\n  GAME OVER.\n";
                exit(0);
            }

        // -----------------------------------------------
        // OPTION 3 : Statistiques  <- FONCTIONNEL
        // -----------------------------------------------
        } else if (choix == 3) {

            joueur.displayStats();

        // -----------------------------------------------
        // OPTION 4 : Items  <- TODO
        // -----------------------------------------------
        } else if (choix == 4) {

            // Option non disponible pour l'instant

        // -----------------------------------------------
        // OPTION 5 : Quitter
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
// POINT D'ENTREE : main()
// ===========================================================
int main() {

    // Initialise le generateur aleatoire avec l'heure (different a chaque lancement)
    srand((unsigned int)time(nullptr));

    // Titre
    std::cout << "==============================\n";
    std::cout << "         ALTERDUNE\n";
    std::cout << "==============================\n";

    // Saisie du nom
    std::string nomJoueur;
    std::cout << "Entrez le nom de votre personnage : ";
    std::cin >> nomJoueur;

    // Construction du catalogue ACT (une seule fois)
    std::vector<ActAction> catalogue = buildCatalogue();

    // Chargement des monstres depuis monsters.csv
    std::vector<Monster> monsters = FileLoader::loadMonsters("data/monsters.csv", catalogue);

    // TODO : charger items.csv et les ajouter a l'inventaire du joueur

    // Creation du joueur avec 100 HP
    Player joueur(nomJoueur, 100);

    // Resume de depart
    std::cout << "\n--- Bienvenue, " << joueur.getName() << " ! ---\n";
    joueur.display();
    std::cout << "  Inventaire : (TODO)\n";

    // Bestiaire : se remplit au fil des victoires
    std::vector<Monster> bestiaire;

    // Lancement du menu principal
    runMainMenu(joueur, monsters, bestiaire, catalogue);

    // ===========================================================
    // ECRAN DE FIN  <- FONCTIONNEL
    // S'affiche seulement si le joueur atteint 10 victoires
    // ===========================================================
    std::cout << "\n==============================\n";
    std::cout << "  10 VICTOIRES ! FIN DE PARTIE\n";
    std::cout << "==============================\n";
    std::cout << "  Tues    : " << joueur.getNbKills()  << "\n";
    std::cout << "  Epargnes: " << joueur.getNbSpared() << "\n";
    std::cout << "\n";

    std::string typeFin = joueur.getEndingType();

    if (typeFin == "Genocidaire") {
        std::cout << "  FIN GENOCIDAIRE\n";
        std::cout << "  Vous avez tue tous vos adversaires.\n";
        std::cout << "  La legende vous craint.\n";
    } else if (typeFin == "Pacifiste") {
        std::cout << "  FIN PACIFISTE\n";
        std::cout << "  Vous avez epargne tout le monde.\n";
        std::cout << "  La paix regne enfin.\n";
    } else {
        std::cout << "  FIN NEUTRE\n";
        std::cout << "  Ni tout blanc, ni tout noir.\n";
        std::cout << "  Une fin nuancee.\n";
    }

    return 0;
}
