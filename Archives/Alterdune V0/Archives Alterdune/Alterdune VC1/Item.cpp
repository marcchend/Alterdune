#include "Item.h"
#include <iostream>

// ===========================================================
// Implémentation des méthodes de Item
// ===========================================================

// Constructeur
Item::Item(std::string nom, int valeurSoin, int quantiteInitiale)
    : name(nom), value(valeurSoin), quantity(quantiteInitiale)
{
    // Liste d'initialisation : on initialise directement les 3 attributs
}

// --- Accesseurs ---
std::string Item::getName()    const { return name; }
int         Item::getValue()   const { return value; }
int         Item::getQuantity()const { return quantity; }

// Retourne true s'il reste au moins 1 item
bool Item::isAvailable() const {
    return quantity > 0;
}

// Utilise l'item sur une entité cible (joueur en général)
void Item::useOn(Entity& cible) {
    // Vérifie qu'il en reste
    if (quantity <= 0) {
        std::cout << "  Plus de " << name << " disponible !\n";
        return;  // On arrête la fonction ici
    }

    // On soigne la cible grâce à la méthode heal() héritée de Entity
    cible.heal(value);

    // On consomme un exemplaire
    quantity = quantity - 1;

    // On informe le joueur
    std::cout << "  Vous utilisez " << name << " et recuperez " << value << " HP.\n";
    std::cout << "  HP actuels : " << cible.getHp() << "/" << cible.getHpMax() << "\n";
}

// Affiche l'item dans la console
void Item::display() const {
    std::cout << "  - " << name
              << "  (Soin : +" << value << " HP)"
              << "  [x" << quantity << "]\n";
}
