#include "Game.h"
#include "FileLoader.h"
#include <iostream>
#include <cstdlib>

Game::Game() {
    player = NULL;
}

Game::~Game() {
    if (player != NULL) {
        delete player;
    }
}

void Game::start(const std::string& playerName) {
    actCatalogue.initCatalogue();
    
    FileLoader loader;
    std::vector<Item> items = loader.loadItems("data/items.csv");
    monsterPool = loader.loadMonsters("data/monsters.csv");
    
    player = new Player(playerName, 100);
    for (int i = 0; i < (int)items.size(); i++) {
        player->addItem(items[i]);
    }
    
    std::cout << "\n============================" << std::endl;
    std::cout << "      Résumé" << std::endl;
    std::cout << "============================" << std::endl;
    player->display();
    player->displayInventory();
    
    mainMenu();
}

void Game::mainMenu() {
    while (true) {
        std::cout << "\n============================" << std::endl;
        std::cout << "      Menu" << std::endl;
        std::cout << "============================" << std::endl;
        std::cout << "1. Bestiaire" << std::endl;
        std::cout << "2. Demarrer un combat" << std::endl;
        std::cout << "3. Statistiques" << std::endl;
        std::cout << "4. Items" << std::endl;
        std::cout << "5. Quitter" << std::endl;
        std::cout << "Option : ";
        
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            showBestiary();
        } else if (choice == 2) {
            startCombat();
            if (player->getWins() >= 10) {
                break;
            }
        } else if (choice == 3) {
            showStats();
        } else if (choice == 4) {
            showItems();
        } else if (choice == 5) {
            return;
        }
    }
    
    std::cout << "\n============================" << std::endl;
    std::cout << "  10 victoires atteintes !" << std::endl;
    std::cout << "  FIN : " << player->getEndingType() << std::endl;
    std::cout << "============================" << std::endl;
}

void Game::showBestiary() {
    std::cout << "\n=== Bestiaire ===" << std::endl;
    if (bestiary.size() == 0) {
        std::cout << " Aucun monstre vaincu" << std::endl;
        return;
    }
    for (int i = 0; i < (int)bestiary.size(); i++) {
        Monster& m = bestiary[i];
        std::cout << "  - " << m.getName()
                  << " [" << Monster::categoryToString(m.getCategory()) << "]"
                  << "  HP max: " << m.getHpMax();
        if (m.isKilled()) {
            std::cout << "  --> Tue" << std::endl;
        } else {
            std::cout << "  --> Epargne" << std::endl;
        }
    }
}

void Game::startCombat() {
    if (monsterPool.size() == 0) {
        std::cout << "  Aucun monstre disponible." << std::endl;
        return;
    }
    
    int randomIndex = rand() % (int)monsterPool.size();
    Monster chosen = monsterPool[randomIndex];
    
    bool victory = runCombat(chosen);
    if (victory) {
        bestiary.push_back(chosen);
    } else {
        std::cout << "  Perdu" << std::endl;
        std::exit(0);
    }
}

void Game::showStats() {
    player->displayStats();
}

void Game::showItems() {
    player->displayInventory();
    std::cout << "  Utiliser un item ? (0 = non) : ";
    int idx;
    std::cin >> idx;
    
    std::vector<Item>& inv = player->getInventory();
    if (idx >= 1 && idx <= (int)inv.size()) {
        inv[idx - 1].use(*player);
    }
}

int Game::rollDamage(int hpMax) {
    return rand() % (hpMax + 1);
}

bool Game::runCombat(Monster monster) {
    std::cout << "\n============================" << std::endl;
    std::cout << "  COMBAT : " << player->getName()
              << " vs " << monster.getName()
              << " [" << Monster::categoryToString(monster.getCategory()) << "]" << std::endl;
    std::cout << "============================" << std::endl;

    while (player->isAlive() && monster.isAlive()) {
        std::cout << "\n  " << player->getName() << " : " << player->getHp()
                  << "/" << player->getHpMax() << " HP" << std::endl;
        std::cout << "  " << monster.getName() << " : " << monster.getHp()
                  << "/" << monster.getHpMax() << " HP"
                  << "  |  Mercy : " << monster.getMercy()
                  << "/" << monster.getMercyGoal() << std::endl << std::endl;

        std::cout << "1. FIGHT   2. ACT   3. ITEM   4. MERCY" << std::endl;
        std::cout << "Choix : ";
        
        int choice;
        std::cin >> choice;

        bool playerActed = true;

        if (choice == 1) {
            int dmg = rollDamage(monster.getHpMax());
            monster.takeDamage(dmg);
            
            if (dmg == 0) {
                std::cout << "Vous avez ratez votre attaque" << std::endl;
            } else {
                std::cout << "  Vous infligez " << dmg << " degats à "
                          << monster.getName() << " !" << std::endl;
            }

            if (!monster.isAlive()) {
                std::cout << "  " << monster.getName() << " est vaincu !" << std::endl;
                monster.setKilled(true);
                player->addWin(true);
                return true;
            }
        } else if (choice == 2) {
            std::vector<std::string> acts = monster.getActIds();
            
            if (acts.size() == 0) {
                std::cout << "  Aucune action ACT disponible." << std::endl;
            } else {
                std::cout << "  Actions disponibles :" << std::endl;
                for (int i = 0; i < (int)acts.size(); i++) {
                    std::cout << "    [" << (i+1) << "] " << acts[i] << std::endl;
                }
                std::cout << "  Choix : ";
                
                int actChoice;
                std::cin >> actChoice;
                
                if (actChoice >= 1 && actChoice <= (int)acts.size()) {
                    const ActAction& act = actCatalogue.getById(acts[actChoice - 1]);
                    monster.applyAct(act);
                } else {
                    std::cout << "  Choix invalide." << std::endl;
                    playerActed = false;
                }
            }
        } else if (choice == 3) {
            std::vector<Item>& inv = player->getInventory();
            std::cout << "  Inventaire :" << std::endl;
            
            bool anyItem = false;
            for (int i = 0; i < (int)inv.size(); i++) {
                if (inv[i].isAvailable()) {
                    std::cout << "    [" << (i+1) << "] ";
                    inv[i].display();
                    anyItem = true;
                }
            }
            
            if (!anyItem) {
                std::cout << "  Aucun item disponible." << std::endl;
                playerActed = false;
            } else {
                std::cout << "  Choix (0 = annuler) : ";
                int itemChoice;
                std::cin >> itemChoice;
                
                if (itemChoice >= 1 && itemChoice <= (int)inv.size()) {
                    inv[itemChoice - 1].use(*player);
                } else {
                    playerActed = false;
                }
            }
        } else if (choice == 4) {
            if (monster.canBeMercied()) {
                std::cout << "  Vous épargnez " << monster.getName() << " !" << std::endl;
                monster.setKilled(false);
                player->addWin(false);
                return true;
            } else {
                std::cout << "  La jauge Mercy n'est pas assez remplie ! ("
                          << monster.getMercy() << "/" << monster.getMercyGoal() << ")" << std::endl;
                playerActed = false;
            }
        } else {
            std::cout << "  Choix invalide." << std::endl;
            playerActed = false;
        }

        if (playerActed && monster.isAlive()) {
            monster.attack(*player);
            if (!player->isAlive()) {
                std::cout << std::endl << "  Perdu" << std::endl;
                return false;
            }
        }
    }
    return false;
}