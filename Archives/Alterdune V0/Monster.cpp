#include "Monster.h"
#include "ActAction.h"
#include <iostream>
#include <random>
#include <algorithm>

Monster::Monster(const std::string& name, int hpMax,
                 Category category, int mercyGoal,
                 const std::vector<std::string>& actIds)
    : Entity(name, hpMax), category(category),
      mercy(0), mercyGoal(mercyGoal), actIds(actIds) {}

Category    Monster::getCategory()  const { return category; }
int         Monster::getMercy()     const { return mercy; }
int         Monster::getMercyGoal() const { return mercyGoal; }
bool        Monster::isKilled()     const { return killed; }
void        Monster::setKilled(bool k)    { killed = k; }

const std::vector<std::string>& Monster::getActIds() const { return actIds; }

void Monster::applyAct(const ActAction& action) {
    int impact = action.getImpact();
    std::cout << "  [ACT] " << action.getText() << "\n";
    mercy = std::max(0, std::min(mercy + impact, mercyGoal));
    std::cout << "  Mercy : " << mercy << "/" << mercyGoal;
    if (mercy >= mercyGoal) std::cout << "  --> MERCY disponible !";
    std::cout << "\n";
}

bool Monster::canBeMercied() const { return mercy >= mercyGoal; }

int Monster::attack(Entity& target) const {
    // Tirage aléatoire entre 0 et hpMax du défenseur (inclus)
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, target.getHpMax());
    int dmg = dist(rng);
    target.takeDamage(dmg);
    if (dmg == 0)
        std::cout << "  " << name << " attaque " << target.getName() << " mais rate !\n";
    else
        std::cout << "  " << name << " attaque " << target.getName()
                  << " pour " << dmg << " degats. ("
                  << target.getHp() << "/" << target.getHpMax() << " HP)\n";
    return dmg;
}

void Monster::display() const {
    std::cout << "  [" << categoryToString(category) << "] " << name
              << "  HP: " << hp << "/" << hpMax
              << "  Mercy: " << mercy << "/" << mercyGoal << "\n";
}

std::string Monster::categoryToString(Category c) {
    switch (c) {
        case Category::NORMAL:   return "NORMAL";
        case Category::MINIBOSS: return "MINIBOSS";
        case Category::BOSS:     return "BOSS";
    }
    return "?";
}
