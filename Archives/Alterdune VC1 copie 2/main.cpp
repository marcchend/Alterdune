#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

#include "Entity.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "Action.h"
#include "FileLoader.h"

// -------- Aléatoire --------
static std::mt19937 rng(std::random_device{}());

// Tire un entier entre 0 et hpMax du défenseur
static int rollDamage(int hpMax) {
    std::uniform_int_distribution<int> dist(0, hpMax);
    return dist(rng);
}

// -------- Combat --------
// Retourne true si le joueur a gagné
bool runCombat(Player& player, Monster monster) {
    std::cout << "\n============================\n";
    std::cout << "  COMBAT : " << player.getName()
              << " vs " << monster.getName()
              << " [" << monster.categoryToString() << "]\n";
    std::cout << "============================\n";

    while (player.isAlive() && monster.isAlive()) {

        // Affichage des HP
        std::cout << "\n  " << player.getName() << " : " << player.getHp()
                  << "/" << player.getHpMax() << " HP\n";
        std::cout << "  " << monster.getName() << " : " << monster.getHp()
                  << "/" << monster.getHpMax() << " HP"
                  << "  |  Mercy : " << monster.getMercy()
                  << "/" << monster.getMercyGoal() << "\n\n";

        // Menu de combat
        std::cout << "  [1] FIGHT   [2] ACT   [3] ITEM   [4] MERCY\n";
        std::cout << "  Choix : ";
        int choice;
        std::cin >> choice;

        bool playerActed = true;

        if (choice == 1) {
            // FIGHT
            int dmg = rollDamage(monster.getHpMax());
            monster.takeDamage(dmg);
            if (dmg == 0)
                std::cout << "  Vous attaquez... mais ratez !\n";
            else
                std::cout << "  Vous infligez " << dmg << " degats a "
                          << monster.getName() << " !\n";

            if (!monster.isAlive()) {
                std::cout << "  " << monster.getName() << " est vaincu !\n";
                monster.setWasKilled(true);
                player.addWin(true);
                return true;
            }

        } else if (choice == 2) {
            // ACT - NON IMPLEMENTE
            std::cout << "\n  [EN DEVELOPPEMENT] Le système ACT n'est pas encore disponible.\n";
            std::cout << "  Cette option sera implémentée dans une version future.\n";
            playerActed = false;

        } else if (choice == 3) {
            // ITEM
            auto& inv = player.getInventory();
            if (inv.empty()) {
                std::cout << "  Aucun item disponible.\n";
                playerActed = false;
            } else {
                std::cout << "  Items disponibles :\n";
                for (size_t i = 0; i < inv.size(); i++) {
                    if (inv[i].isAvailable()) {
                        std::cout << "    [" << (i+1) << "] ";
                        inv[i].display();
                    }
                }
                std::cout << "  Choix : ";
                int itemChoice;
                std::cin >> itemChoice;
                if (itemChoice >= 1 && itemChoice <= (int)inv.size() && inv[itemChoice-1].isAvailable()) {
                    inv[itemChoice-1].useOn(player);
                } else {
                    std::cout << "  Choix invalide.\n";
                    playerActed = false;
                }
            }

        } else if (choice == 4) {
            // MERCY - NON IMPLEMENTE
            std::cout << "\n  [EN DEVELOPPEMENT] Le système Mercy n'est pas encore disponible.\n";
            std::cout << "  Cette option sera implémentée dans une version future.\n";
            playerActed = false;
            
        } else {
            std::cout << "  Choix invalide.\n";
            playerActed = false;
        }

        // Tour du monstre (si le joueur a réellement agi)
        if (playerActed && monster.isAlive()) {
            monster.attack(player);
            if (!player.isAlive()) {
                std::cout << "\n  DEFAITE ! Vous avez ete vaincu...\n";
                return false;
            }
        }
    }
    return false;
}

// -------- Menu principal --------
void mainMenu(Player& player, std::vector<Monster>& monsterPool,
              std::vector<Monster>& bestiary) {
    while (true) {
        std::cout << "\n==============================\n";
        std::cout << "      ALTERDUNE - Menu\n";
        std::cout << "  Victoires : " << player.getWins() << "/10\n";
        std::cout << "==============================\n";
        std::cout << "  [1] Bestiaire\n";
        std::cout << "  [2] Demarrer un combat\n";
        std::cout << "  [3] Statistiques\n";
        std::cout << "  [4] Items\n";
        std::cout << "  [5] Quitter\n";
        std::cout << "  Choix : ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            // Bestiaire
            std::cout << "\n=== Bestiaire ===\n";
            if (bestiary.empty()) { std::cout << "  (aucun monstre vaincu)\n"; continue; }
            for (const auto& m : bestiary) {
                std::cout << "  - " << m.getName()
                          << " [" << m.categoryToString() << "]"
                          << "  HP max: " << m.getHpMax()
                          << "  --> " << (m.getWasKilled() ? "Tue" : "Epargne") << "\n";
            }

        } else if (choice == 2) {
            // Combat aléatoire
            if (monsterPool.empty()) {
                std::cout << "  Aucun monstre disponible.\n"; continue;
            }
            std::uniform_int_distribution<int> d(0, (int)monsterPool.size() - 1);
            Monster chosen = monsterPool[d(rng)]; // copie pour réinitialiser le monstre

            bool victory = runCombat(player, chosen);
            if (victory) {
                bestiary.push_back(chosen);
                if (player.getWins() >= 10) break; // fin de partie
            } else {
                std::cout << "  Game Over.\n";
                std::exit(0);
            }

        } else if (choice == 3) {
            player.displayStats();

        } else if (choice == 4) {
            // Items
            player.displayInventory();
            std::cout << "  Appuyez sur Entree pour continuer...";
            std::cin.ignore();
            std::cin.get();

        } else if (choice == 5) {
            std::cout << "  Au revoir !\n"; return;
        }
    }
}

// -------- Point d'entree --------
int main() {
    // Initialise le catalogue ACT une seule fois
    Action::initCatalogue();

    // Nom du personnage
    std::string playerName;
    std::cout << "=== ALTERDUNE ===\n";
    std::cout << "Entrez le nom de votre personnage : ";
    std::cin >> playerName;

    // Chargement des fichiers
    auto items    = FileLoader::loadItems("items.csv");
    auto monsters = FileLoader::loadMonsters("monsters.csv", Action::getCatalogue());

    // Creation du joueur
    Player player(playerName, 100);
    // Ajouter les items au joueur
    for (const auto& item : items) player.addItem(item);

    // Resume de depart
    std::cout << "\n--- Bienvenue, " << player.getName() << " ---\n";
    player.display();
    std::cout << "\n  [INFO] Système ACT et système Mercy non implémentés.\n";
    std::cout << "  Seuls les combats FIGHT et ITEM sont disponibles.\n";
    player.displayInventory();

    // Bestiaire (monstres vaincus au fil du jeu)
    std::vector<Monster> bestiary;

    // Menu principal
    mainMenu(player, monsters, bestiary);

    // Fin de partie
    std::cout << "\n============================\n";
    std::cout << "  10 victoires atteintes !\n";
    std::cout << "  FIN : " << player.getEndingType() << "\n";
    std::cout << "============================\n";

    return 0;
}