#pragma once
#include "Entity.h"   // Player hérite de Entity
#include "Item.h"     // Player possède des items dans son inventaire
#include <vector>

// ===========================================================
// CLASSE : Player
// ===========================================================
// Player HÉRITE de Entity, tout comme Monster.
// Les deux partagent Entity comme base commune (nom, HP).
// ===========================================================

class Player : public Entity {
private:
    int nbKills;   // Nombre de monstres tués
    int nbSpared;  // Nombre de monstres épargnés
    int nbWins;    // Total des victoires (kills + spared = wins)

    // L'inventaire : un vecteur d'Items
    // Composition : Player "contient" des Items (pas d'héritage ici)
    std::vector<Item> inventory;

public:
    // Constructeur
    Player(std::string nom, int pointsDeVieMax);

    // --- Accesseurs ---
    int getNbKills()  const;
    int getNbSpared() const;
    int getNbWins()   const;

    // Ajoute un item dans l'inventaire (appelé lors du chargement de items.csv)
    void addItem(Item item);

    // Retourne une RÉFÉRENCE sur l'inventaire (pas une copie)
    // Utile pour modifier les items directement (consommer une quantité)
    std::vector<Item>& getInventory();

    // Enregistre une victoire :
    //   killed = true  → monstre tué  (nbKills++)
    //   killed = false → épargné      (nbSpared++)
    void addVictory(bool killed);

    // Retourne le type de fin selon l'historique
    // "Genocidaire", "Pacifiste" ou "Neutre"
    std::string getEndingType() const;

    // Override de la méthode virtuelle pure de Entity
    void display() const override;

    // Affichages supplémentaires
    void displayStats()     const;  // Stats complètes du joueur
    void displayInventory() const;  // Liste des items
};
