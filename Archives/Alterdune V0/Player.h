#pragma once
#include "Entity.h"
#include "Item.h"
#include <vector>

class Player : public Entity {
private:
    int kills;
    int spared;
    int wins;
    std::vector<Item> inventory;

public:
    Player(const std::string& name, int hpMax);

    int getKills()  const;
    int getSpared() const;
    int getWins()   const;

    // Ajoute une victoire ; killed=true si monstre tué, false si épargné
    void addWin(bool killed);

    // Inventaire
    void addItem(const Item& item);
    std::vector<Item>& getInventory();

    // Retourne "Genocidaire", "Pacifiste" ou "Neutre"
    std::string getEndingType() const;

    void display() const override;
    void displayInventory() const;
    void displayStats() const;
};
