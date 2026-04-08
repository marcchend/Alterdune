#pragma once
#include "Entity.h"
#include <vector>
#include <string>

enum class Category { NORMAL, MINIBOSS, BOSS };

class ActAction;

class Monster : public Entity {
private:
    Category category;
    int mercy;
    int mercyGoal;
    std::vector<std::string> actIds; // identifiants dans le catalogue
    bool killed = false; // résultat final du combat

public:
    Monster(const std::string& name, int hpMax,
            Category category, int mercyGoal,
            const std::vector<std::string>& actIds);

    Category getCategory()  const;
    int getMercy()          const;
    int getMercyGoal()      const;
    bool isKilled()         const;
    void setKilled(bool k);

    const std::vector<std::string>& getActIds() const;

    // Modifie la jauge Mercy (bornée entre 0 et mercyGoal)
    void applyAct(const ActAction& action);

    // Vrai si Mercy >= mercyGoal
    bool canBeMercied() const;

    // Attaque une entité cible (retourne les dégâts infligés)
    int attack(Entity& target) const;

    void display() const override;

    // Retourne la catégorie en string
    static std::string categoryToString(Category c);
};
