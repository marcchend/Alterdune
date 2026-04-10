// Player.cpp
#include "Player.h"
#include <iostream>

Player::Player(const std::string& name, int hpMax) : Entity(name, hpMax) {
    kills = 0;
    spared = 0;
    wins = 0;
}

int Player::getKills() const {
    return kills;
}

int Player::getSpared() const {
    return spared;
}

int Player::getWins() const {
    return wins;
}

void Player::addWin(bool killed) {
    wins = wins + 1;
    if (killed) {
        kills = kills + 1;
    } else {
        spared = spared + 1;
    }
}

void Player::addItem(const Item& item) {
    inventory.push_back(item);
}

std::vector<Item>& Player::getInventory() {
    return inventory;
}

std::string Player::getEndingType() const {
    if (spared == 0) {
        return "Genocidaire";
    }
    if (kills == 0) {
        return "Pacifiste";
    }
    return "Neutre";
}

void Player::display() const {
    std::cout << "  Joueur : " << name << "  HP: " << hp << "/" << hpMax << std::endl;
}

void Player::displayInventory() const {
    std::cout << "\n=== Inventaire ===" << std::endl;
    if (inventory.size() == 0) {
        std::cout << "  (vide)" << std::endl;
        return;
    }
    for (int i = 0; i < (int)inventory.size(); i++) {
        inventory[i].display();
    }
}

void Player::displayStats() const {
    std::cout << "\n=== Statistiques de " << name << " ===" << std::endl;
    std::cout << "  HP        : " << hp << "/" << hpMax << std::endl;
    std::cout << "  Victoires : " << wins << "/10" << std::endl;
    std::cout << "  Tues      : " << kills << std::endl;
    std::cout << "  Epargnes  : " << spared << std::endl;
    std::cout << "  Fin prevue: " << getEndingType() << std::endl;
}