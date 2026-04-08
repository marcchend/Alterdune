#pragma once
#include "Entity.h"   // Player hérite de Entity
// TODO : #include "Item.h"  ← à activer quand l'inventaire sera implémenté

// ===========================================================
// CLASSE : Player
// ===========================================================
// Player HÉRITE de Entity, tout comme Monster.
// Les deux partagent Entity comme base commune (nom, HP).
//
// TODO : ajouter l'inventaire d'items (vector<Item> inventory)
// ===========================================================

class Player : public Entity {
private:
    int nbKills;   // Nombre de monstres tués
    int nbSpared;  // Nombre de monstres épargnés
    int nbWins;    // Total des victoires

    // TODO : std::vector<Item> inventory;

public:
    Player(std::string nom, int pointsDeVieMax);

    int getNbKills()  const;
    int getNbSpared() const;
    int getNbWins()   const;

    // TODO : void addItem(Item item);
    // TODO : std::vector<Item>& getInventory();

    void addVictory(bool killed);
    std::string getEndingType() const;

    void display()      const override;
    void displayStats() const;
};
