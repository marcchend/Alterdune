// Player.h
#ifndef PLAYER_H
#define PLAYER_H

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

    int getKills() const;
    int getSpared() const;
    int getWins() const;

    void addWin(bool killed);

    void addItem(const Item& item);
    std::vector<Item>& getInventory();

    std::string getEndingType() const;

    void display() const;
    void displayInventory() const;
    void displayStats() const;
};

#endif