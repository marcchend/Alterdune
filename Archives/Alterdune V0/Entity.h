#pragma once
#include <string>

// Classe abstraite commune au joueur et aux monstres
class Entity {
protected:
    std::string name;
    int hp;
    int hpMax;

public:
    Entity(const std::string& name, int hpMax);
    virtual ~Entity() = default;

    // Accesseurs
    std::string getName() const;
    int getHp() const;
    int getHpMax() const;

    // Modificateurs
    void setHp(int value);
    void takeDamage(int dmg);
    bool isAlive() const;

    // Méthode virtuelle pure : oblige les sous-classes à implémenter
    virtual void display() const = 0;
};
