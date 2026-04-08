#include "Entity.h"
#include <algorithm>  // pour std::min, std::max

Entity::Entity(const std::string& nom, int hpMax)
    : nom(nom), hp(hpMax), hpMax(hpMax) {}

std::string Entity::getNom() const { return nom; }
int Entity::getHp() const { return hp; }
int Entity::getHpMax() const { return hpMax; }

void Entity::setHp(int nouveauHp) {
    // On borne entre 0 et hpMax
    if (nouveauHp < 0) {
        hp = 0;
    } else if (nouveauHp > hpMax) {
        hp = hpMax;
    } else {
        hp = nouveauHp;
    }
}

void Entity::prendreDegats(int degats) {
    if (degats > 0) {
        int nouveauHp = hp - degats;
        setHp(nouveauHp);
    }
}

void Entity::soigner(int montant) {
    if (montant > 0) {
        int nouveauHp = hp + montant;
        setHp(nouveauHp);
    }
}

bool Entity::estVivant() const {
    return hp > 0;
}