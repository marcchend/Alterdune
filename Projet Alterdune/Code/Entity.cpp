#include "Entity.h"
#include <iostream>

Entity::Entity(const std::string& name, int hpMax) {
    this->name = name;
    this->hp = hpMax;
    this->hpMax = hpMax;
}

Entity::~Entity() {}

std::string Entity::getName() const {
    return name;
}

int Entity::getHp() const {
    return hp;
}

int Entity::getHpMax() const {
    return hpMax;
}

void Entity::setHp(int value) {
    if (value < 0) {
        hp = 0;
    } else if (value > hpMax) {
        hp = hpMax;
    } else {
        hp = value;
    }
}

void Entity::takeDamage(int dmg) {
    if (dmg > 0) {
        int newHp = hp - dmg;
        setHp(newHp);
    }
}

bool Entity::isAlive() const {
    if (hp > 0) {
        return true;
    }
    return false;
}

void Entity::display() const {
}