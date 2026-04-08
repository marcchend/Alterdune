#include "Player.h"
#include <iostream>

Player::Player(const std::string& name, int hpMax)
    : Entity(name, hpMax), kills(0), spared(0), wins(0) {}

int Player::getKills()  const { return kills; }
int Player::getSpared() const { return spared; }
int Player::getWins()   const { return wins; }

void Player::addWin(bool killed) {
    wins++;
    if (killed) kills++;
    else        spared++;
}

void Player::addItem(const Item& item) { 
    inventory.push_back(item); 
}

std::vector<Item>& Player::getInventory() { 
    return inventory; 
}

std::string Player::getEndingType() const {
    if (spared == 0)  return "Genocidaire";
    if (kills  == 0)  return "Pacifiste";
    return "Neutre";
}

void Player::display() const {
    std::cout << "  Joueur : " << name
              << "  HP: " << hp << "/" << hpMax << "\n";
}

void Player::displayInventory() const {
    std::cout << "\n=== Inventaire ===\n";
    if (inventory.empty()) {
        std::cout << "  (vide)\n";
    } else {
        for (const auto& item : inventory) {
            item.display();
        }
    }
}

void Player::displayStats() const {
    std::cout << "\n=== Statistiques de " << name << " ===\n";
    std::cout << "  HP        : " << hp << "/" << hpMax << "\n";
    std::cout << "  Victoires : " << wins << "/10\n";
    std::cout << "  Tues      : " << kills  << "\n";
    std::cout << "  Epargnes  : " << spared << "\n";
    std::cout << "  Fin prevue: " << getEndingType() << "\n";
}