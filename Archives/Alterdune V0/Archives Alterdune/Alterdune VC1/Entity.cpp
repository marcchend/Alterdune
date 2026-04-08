#include "Entity.h"   // On inclut le .h correspondant
#include <iostream>   // Pour std::cout (affichage)

// ===========================================================
// Implémentation des méthodes de Entity
// ===========================================================

// Constructeur
// La syntaxe ": name(nom), hp(pointsDeVieMax), hpMax(pointsDeVieMax)"
// s'appelle une "liste d'initialisation" : elle initialise les attributs
// directement, avant même d'entrer dans le corps du constructeur {}
Entity::Entity(std::string nom, int pointsDeVieMax)
    : name(nom), hp(pointsDeVieMax), hpMax(pointsDeVieMax)
{
    // Corps vide : tout est fait dans la liste d'initialisation
}

// Destructeur : corps vide, mais il doit exister car on l'a déclaré virtual
Entity::~Entity() {}

// --- Accesseurs ---
std::string Entity::getName() const { return name; }
int         Entity::getHp()   const { return hp; }
int         Entity::getHpMax()const { return hpMax; }

// Réduit les HP, sans jamais descendre sous 0
void Entity::takeDamage(int degats) {
    hp = hp - degats;       // On soustrait les dégâts
    if (hp < 0) hp = 0;     // Si négatif, on remet à 0
}

// Augmente les HP, sans dépasser hpMax
void Entity::heal(int soin) {
    hp = hp + soin;           // On ajoute le soin
    if (hp > hpMax) hp = hpMax; // Si dépassement, on remet au maximum
}

// Retourne true si l'entité est encore en vie
bool Entity::isAlive() const {
    return hp > 0;  // true si hp strictement positif
}
