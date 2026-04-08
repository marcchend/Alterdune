#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "Action.h"
#include "FileLoader.h"

// c'est pour le combat
bool fight(Player& p, Monster m) {
    // debut du combat
    std::cout << "\n============================\n";
    std::cout << "  COMBAT : " << p.getName() << " vs " << m.getName() << "\n";
    std::cout << "============================\n";

    // boucle tant que vivant
    while (p.isAlive() && m.isAlive()) {
        // afficher les vies
        std::cout << "\n  " << p.getName() << " : " << p.getHp() << "/" << p.getHpMax() << " HP\n";
        std::cout << "  " << m.getName() << " : " << m.getHp() << "/" << m.getHpMax() << " HP\n\n";

        // afficher le menu
        std::cout << "  [1] FIGHT\n";
        std::cout << "  [2] ACT\n";
        std::cout << "  [3] ITEM\n";
        std::cout << "  [4] MERCY\n";
        std::cout << "  Choix : ";
        int c;
        std::cin >> c;

        bool acted = true; // si agi

        if (c == 1) {
            // attaquer
            int dmg = rand() % 101; // 0-100 damage
            m.takeDamage(dmg);
            std::cout << "  Vous attaquez et faites " << dmg << " degats !\n";

            if (!m.isAlive()) {
                std::cout << "  Monstre mort !\n";
                m.setWk(true);
                p.addW(true);
                return true; // gagne
            }
        } else if (c == 2) {
            // pas fait
            std::cout << "\n  Pas encore fait.\n";
            acted = false;
        } else if (c == 3) {
            // pas fait
            std::cout << "\n  Pas encore fait.\n";
            acted = false;
        } else if (c == 4) {
            // pas fait
            std::cout << "\n  Pas encore fait.\n";
            acted = false;
        } else {
            std::cout << "  Mauvais choix.\n";
            acted = false;
        }

        // monstre attaque
        if (acted && m.isAlive()) {
            m.att(p);
            if (!p.isAlive()) {
                std::cout << "\n  Perdu !\n";
                return false; // perdu
            }
        }
    }
    return false;
}

// menu principal
void menu(Player& p, std::vector<Monster>& ms, std::vector<Monster>& b) {
    // boucle infinie
    while (true) {
        // afficher le menu
        std::cout << "\n==============================\n";
        std::cout << "      MENU\n";
        std::cout << "  Victoires : " << p.getW() << "/10\n";
        std::cout << "==============================\n";
        std::cout << "  [1] Bestiaire\n";
        std::cout << "  [2] Combat\n";
        std::cout << "  [3] Stats\n";
        std::cout << "  [4] Items\n";
        std::cout << "  [5] Quitter\n";
        std::cout << "  Choix : ";
        int c;
        std::cin >> c;

        if (c == 1) {
            // pas fait
            std::cout << "\n  Pas encore fait.\n";
        } else if (c == 2) {
            // combat
            if (ms.empty()) {
                std::cout << "  Pas de monstres.\n";
                continue;
            }
            Monster chosen = ms[0]; // premier monstre

            bool win = fight(p, chosen);
            if (win) {
                b.push_back(chosen);
                if (p.getW() >= 10) break; // fin
            } else {
                std::cout << "  Game Over.\n";
                exit(0);
            }
        } else if (c == 3) {
            p.dispStats();
        } else if (c == 4) {
            // pas fait
            std::cout << "\n  Pas encore fait.\n";
        } else if (c == 5) {
            std::cout << "  Bye !\n";
            return;
        }
    }
}

// debut
int main() {
    // init
    auto actions = buildCat();

    // nom
    std::string name;
    std::cout << "=== JEU ===\n";
    std::cout << "Nom : ";
    std::cin >> name;

    // charger
    auto items = FileLoader::loadItems("items.csv");
    auto monsters = FileLoader::loadMonsters("monsters.csv", actions);

    // joueur
    Player p(name, 100);
    for (auto& i : items) p.addI(i);

    // bienvenue
    std::cout << "\n=== JOUEUR ===\n";
    std::cout << "Nom: " << p.getName() << "\n";
    std::cout << "HP: " << p.getHp() << "/" << p.getHpMax() << "\n";
    std::cout << "Items:\n";
    auto inv = p.getInv();
    if (inv.empty()) {
        std::cout << "  (aucun)\n";
    } else {
        for (auto& i : inv) {
            std::cout << "  - " << i.getN() << " (x" << i.getQ() << ")\n";
        }
    }

    // bestiaire
    std::vector<Monster> b;

    // menu
    menu(p, monsters, b);

    // fin
    std::cout << "\n============================\n";
    std::cout << "  Gagne !\n";
    std::cout << "============================\n";

    return 0;
}