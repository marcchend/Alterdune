// Monster.cpp
#include "Monster.h"
#include "ActAction.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Monster::Monster(const std::string& name, int hpMax,
                 Category category, int mercyGoal,
                 const std::vector<std::string>& actIds)
    : Entity(name, hpMax) {
    this->category = category;
    this->mercy = 0;
    this->mercyGoal = mercyGoal;
    this->actIds = actIds;
    this->killed = false;
}

Category Monster::getCategory() const {
    return category;
}

int Monster::getMercy() const {
    return mercy;
}

int Monster::getMercyGoal() const {
    return mercyGoal;
}

bool Monster::isKilled() const {
    return killed;
}

void Monster::setKilled(bool k) {
    killed = k;
}

std::vector<std::string> Monster::getActIds() const {
    return actIds;
}

void Monster::applyAct(const ActAction& action) {
    int impact = action.getImpact();
    std::cout << "  [ACT] " << action.getText() << std::endl;
    
    mercy = mercy + impact;
    if (mercy < 0) {
        mercy = 0;
    }
    if (mercy > mercyGoal) {
        mercy = mercyGoal;
    }
    
    std::cout << "  Mercy : " << mercy << "/" << mercyGoal;
    if (mercy >= mercyGoal) {
        std::cout << "  --> MERCY disponible !";
    }
    std::cout << std::endl;
}

bool Monster::canBeMercied() const {
    if (mercy >= mercyGoal) {
        return true;
    }
    return false;
}

int Monster::attack(Entity& target) const {
    int dmg = rand() % (target.getHpMax() + 1);
    target.takeDamage(dmg);
    
    if (dmg == 0) {
        std::cout << "  " << name << " attaque " << target.getName() << " mais rate !" << std::endl;
    } else {
        std::cout << "  " << name << " attaque " << target.getName()
                  << " pour " << dmg << " degats. ("
                  << target.getHp() << "/" << target.getHpMax() << " HP)" << std::endl;
    }
    return dmg;
}

void Monster::display() const {
    std::cout << "  [" << categoryToString(category) << "] " << name
              << "  HP: " << hp << "/" << hpMax
              << "  Mercy: " << mercy << "/" << mercyGoal << std::endl;
}

std::string Monster::categoryToString(Category c) {
    if (c == NORMAL) {
        return "NORMAL";
    } else if (c == MINIBOSS) {
        return "MINIBOSS";
    } else {
        return "BOSS";
    }
}