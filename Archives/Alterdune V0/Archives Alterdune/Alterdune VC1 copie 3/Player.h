#pragma once
#include "Item.h"
#include <vector>
#include <string>

class Player {
private:
    std::string name;
    int hp;
    int hpMax;
    int k; // kills
    int s; // spared
    int w; // wins
    std::vector<Item> inv; // inventory

public:
    Player(const std::string& n, int h);

    std::string getName() const;
    int getHp() const;
    int getHpMax() const;
    int getK() const;
    int getS() const;
    int getW() const;

    void takeDamage(int degats);
    void heal(int soin);
    bool isAlive() const;
    void addW(bool killed);

    void addI(const Item& i);
    std::vector<Item>& getInv();

    std::string getEnd() const;

    void display() const;
    void dispInv() const;
    void dispStats() const;
};