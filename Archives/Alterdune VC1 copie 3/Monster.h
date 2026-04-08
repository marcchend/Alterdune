#pragma once
#include <vector>
#include <string>
#include "Player.h"

enum Cat {
    N, M, B
};

class Monster {
private:
    std::string name;
    int hp;
    int hpMax;
    Cat c; // category
    int m; // mercy
    int mg; // mercyGoal
    bool wk; // wasKilled
    std::vector<std::string> a; // actIds

public:
    Monster(std::string n, int h, Cat cat, int mg, std::vector<std::string> a);

    std::string getName() const;
    int getHp() const;
    int getHpMax() const;
    Cat getC() const;
    int getM() const;
    int getMg() const;
    bool getWk() const;
    const std::vector<std::string>& getA() const;

    void takeDamage(int degats);
    void heal(int soin);
    bool isAlive() const;
    void setWk(bool v);

    void applyA(const std::string& act);
    bool canMerc() const;
    int att(Player& cible);
    std::string catStr() const;
    void display() const;
};
