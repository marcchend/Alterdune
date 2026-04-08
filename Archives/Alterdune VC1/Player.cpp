#include "Player.h"
#include <iostream>

// ===========================================================
// Implémentation des méthodes de Player
// ===========================================================

// Constructeur
// On appelle le constructeur de Entity en premier (classe mère)
Player::Player(std::string nom, int pointsDeVieMax)
    : Entity(nom, pointsDeVieMax),  // Appel du constructeur parent
      nbKills(0),                   // Démarre à 0
      nbSpared(0),
      nbWins(0)
{
    // inventory est automatiquement initialisé vide par std::vector
}

// --- Accesseurs ---
int Player::getNbKills()  const { return nbKills; }
int Player::getNbSpared() const { return nbSpared; }
int Player::getNbWins()   const { return nbWins; }

// Ajoute un item à l'inventaire
void Player::addItem(Item item) {
    inventory.push_back(item);  // push_back = ajoute à la fin du vecteur
}

// Retourne l'inventaire par référence
// Le & évite une copie : on travaille directement sur le vecteur du joueur
std::vector<Item>& Player::getInventory() {
    return inventory;
}

// Enregistre une victoire
void Player::addVictory(bool killed) {
    nbWins++;                      // Toujours +1 victoire
    if (killed) nbKills++;         // Si tué : +1 kill
    else        nbSpared++;        // Si épargné : +1 épargné
}

// Détermine le type de fin
std::string Player::getEndingType() const {
    if (nbSpared == 0) return "Genocidaire";  // Aucun épargné
    if (nbKills  == 0) return "Pacifiste";    // Aucun tué
    return "Neutre";                          // Un peu des deux
}

// Redéfinition de display() (obligatoire : virtuelle pure dans Entity)
void Player::display() const {
    std::cout << "  Joueur : " << name
              << " | HP : " << hp << "/" << hpMax << "\n";
}

// Affiche les statistiques complètes
void Player::displayStats() const {
    std::cout << "\n=== Statistiques de " << name << " ===\n";
    std::cout << "  HP         : " << hp << "/" << hpMax << "\n";
    std::cout << "  Victoires  : " << nbWins << "/10\n";
    std::cout << "  Tues       : " << nbKills  << "\n";
    std::cout << "  Epargnes   : " << nbSpared << "\n";
    std::cout << "  Fin prevue : " << getEndingType() << "\n";
}

// Affiche l'inventaire
void Player::displayInventory() const {
    std::cout << "\n=== Inventaire ===\n";

    // Cas où l'inventaire est vide
    if (inventory.empty()) {
        std::cout << "  (aucun item)\n";
        return;
    }

    // Parcours du vecteur : i va de 0 à inventory.size()-1
    for (int i = 0; i < (int)inventory.size(); i++) {
        std::cout << "  [" << (i + 1) << "] ";
        inventory[i].display();
    }
}
