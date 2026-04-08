#include "Player.h"
#include <iostream>

Player::Player(std::string nom, int pointsDeVieMax)
    : Entity(nom, pointsDeVieMax),
      nbKills(0),
      nbSpared(0),
      nbWins(0)
{
}

int Player::getNbKills()  const { return nbKills; }
int Player::getNbSpared() const { return nbSpared; }
int Player::getNbWins()   const { return nbWins; }

// TODO : void Player::addItem(Item item) { ... }
// TODO : std::vector<Item>& Player::getInventory() { ... }

void Player::addVictory(bool killed) {
    nbWins++;
    if (killed) nbKills++;
    else        nbSpared++;
}

std::string Player::getEndingType() const {
    if (nbSpared == 0) return "Genocidaire";
    if (nbKills  == 0) return "Pacifiste";
    return "Neutre";
}

void Player::display() const {
    std::cout << "  Joueur : " << name
              << " | HP : " << hp << "/" << hpMax << "\n";
}

void Player::displayStats() const {
    std::cout << "\n=== Statistiques de " << name << " ===\n";
    std::cout << "  HP         : " << hp << "/" << hpMax << "\n";
    std::cout << "  Victoires  : " << nbWins << "/10\n";
    std::cout << "  Tues       : " << nbKills  << "\n";
    std::cout << "  Epargnes   : " << nbSpared << "\n";
    std::cout << "  Fin prevue : " << getEndingType() << "\n";
}
