#pragma once
#include <string>

class Entity {
protected:
    std::string name;
    int hp;
    int hpMax;

public:
    Entity(std::string nom, int pointsDeVieMax);
    virtual ~Entity() = default;

    const std::string& getName() const;
    int getHp() const;
    int getHpMax() const;
    bool isAlive() const;
    void takeDamage(int amount);

    virtual void display() const;
};
