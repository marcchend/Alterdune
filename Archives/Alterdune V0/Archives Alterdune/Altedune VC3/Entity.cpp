#include "Entity.h"
#include <iostream>

Entity::Entity(std::string nom, int pointsDeVieMax)
    : name(std::move(nom)), hp(pointsDeVieMax), hpMax(pointsDeVieMax) {
}

const std::string& Entity::getName() const {
    return name;
}

int Entity::getHp() const {
    return hp;
}

int Entity::getHpMax() const {
    return hpMax;
}

bool Entity::isAlive() const {
    return hp > 0;
}

void Entity::takeDamage(int amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
}

void Entity::display() const {
    std::cout << "  Entite : " << name
              << " | HP : " << hp << "/" << hpMax << "\n";
}
