// Monster.h
#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"
#include <vector>
#include <string>

enum Category { NORMAL, MINIBOSS, BOSS };

class ActAction;

class Monster : public Entity {
private:
    Category category;
    int mercy;
    int mercyGoal;
    std::vector<std::string> actIds;
    bool killed;

public:
    Monster(const std::string& name, int hpMax,
            Category category, int mercyGoal,
            const std::vector<std::string>& actIds);

    Category getCategory() const;
    int getMercy() const;
    int getMercyGoal() const;
    bool isKilled() const;
    void setKilled(bool k);

    std::vector<std::string> getActIds() const;

    void applyAct(const ActAction& action);
    bool canBeMercied() const;

    int attack(Entity& target) const;

    void display() const;

    static std::string categoryToString(Category c);
};

#endif