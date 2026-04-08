#pragma once
#include "Entity.h"
#include "ActAction.h"
#include <string>
#include <vector>

enum Category {
    NORMAL,
    MINIBOSS,
    BOSS
};

class Player;

class Monster : public Entity {
private:
    Category category;
    int mercyGoal;
    int mercy;
    std::vector<std::string> actIds;
    bool wasKilled;

public:
    Monster(std::string nom,
            int pointsDeVieMax,
            Category category,
            int mercyGoal,
            const std::vector<std::string>& actIds);

    std::string categoryToString() const;
    int getMercy() const;
    int getMercyGoal() const;
    const std::vector<std::string>& getActIds() const;
    bool getWasKilled() const;
    void setWasKilled(bool value);
    void applyAct(const ActAction& action);
    void attack(Player& cible);

    void display() const override;
};
