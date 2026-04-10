#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity {
protected:
    std::string name;
    int hp;
    int hpMax;

public:
    Entity(const std::string& name, int hpMax);
    virtual ~Entity();

    std::string getName() const;
    int getHp() const;
    int getHpMax() const;

    void setHp(int value);
    void takeDamage(int dmg);
    bool isAlive() const;

    virtual void display() const = 0;
};

#endif