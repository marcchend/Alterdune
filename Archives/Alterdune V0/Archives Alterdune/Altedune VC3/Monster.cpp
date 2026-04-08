#include "Monster.h"
#include "Player.h"
#include <iostream>
#include <cstdlib>

Monster::Monster(std::string nom,
                 int pointsDeVieMax,
                 Category category_,
                 int mercyGoal_,
                 const std::vector<std::string>& actIds_)
    : Entity(std::move(nom), pointsDeVieMax),
      category(category_),
      mercyGoal(mercyGoal_),
      mercy(0),
      actIds(actIds_),
      wasKilled(false) {
}

std::string Monster::categoryToString() const {
    switch (category) {
        case NORMAL: return "NORMAL";
        case MINIBOSS: return "MINIBOSS";
        case BOSS: return "BOSS";
    }
    return "UNKNOWN";
}

int Monster::getMercy() const {
    return mercy;
}

int Monster::getMercyGoal() const {
    return mercyGoal;
}

const std::vector<std::string>& Monster::getActIds() const {
    return actIds;
}

bool Monster::getWasKilled() const {
    return wasKilled;
}

void Monster::setWasKilled(bool value) {
    wasKilled = value;
}

void Monster::applyAct(const ActAction& action) {
    mercy += action.mercyGain;
    if (mercy > mercyGoal) mercy = mercyGoal;
    std::cout << "  Vous utilisez ACT '" << action.id << "' : "
              << action.description << ".\n";
    std::cout << "  Mercy de " << name << " : " << mercy << " / " << mercyGoal << "\n";
}

void Monster::attack(Player& cible) {
    int degats = rand() % (getHpMax() + 1);
    std::cout << "  " << name << " attaque " << cible.getName()
              << " et inflige " << degats << " degats.\n";
    cible.takeDamage(degats);
}

void Monster::display() const {
    std::cout << "  Monstre : " << name
              << " | HP : " << hp << "/" << hpMax
              << " | Mercy : " << mercy << "/" << mercyGoal << "\n";
}
