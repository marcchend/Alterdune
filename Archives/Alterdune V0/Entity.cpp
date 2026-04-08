#include "Entity.h"
#include <iostream>
#include <algorithm>

Entity::Entity(const std::string& name, int hpMax)
    : name(name), hp(hpMax), hpMax(hpMax) {}

std::string Entity::getName() const { return name; }
int Entity::getHp()    const { return hp; }
int Entity::getHpMax() const { return hpMax; }

void Entity::setHp(int value) {
    hp = std::max(0, std::min(value, hpMax));
}

void Entity::takeDamage(int dmg) {
    if (dmg > 0) setHp(hp - dmg);
}

bool Entity::isAlive() const { return hp > 0; }
