#include "Monster.h"
#include <iostream>
#include <cstdlib>   // Pour rand() et srand()

// ===========================================================
// Implémentation des méthodes de Monster
// ===========================================================

// Constructeur
// On appelle d'abord le constructeur de Entity (classe mère) grâce à Entity(nom, hp)
// C'est obligatoire quand on hérite : la classe mère doit être initialisée en premier
Monster::Monster(std::string nom, int pointsDeVieMax, Category categorie,
                 int objectifMercy, std::vector<std::string> listeActIds)
    : Entity(nom, pointsDeVieMax),    // Appel du constructeur parent
      category(categorie),
      mercy(0),                        // Mercy démarre toujours à 0
      mercyGoal(objectifMercy),
      wasKilled(false),
      actIds(listeActIds)
{
}

// --- Accesseurs ---
Category                        Monster::getCategory() const { return category; }
int                             Monster::getMercy()    const { return mercy; }
int                             Monster::getMercyGoal()const { return mercyGoal; }
bool                            Monster::getWasKilled()const { return wasKilled; }
const std::vector<std::string>& Monster::getActIds()   const { return actIds; }

void Monster::setWasKilled(bool valeur) {
    wasKilled = valeur;
}

// Applique une action ACT sur la jauge Mercy
void Monster::applyAct(const ActAction& action) {
    // On affiche le texte drôle de l'action
    std::cout << "  >> " << action.texte << "\n";

    // On modifie la jauge
    mercy = mercy + action.mercyImpact;

    // On borne la valeur entre 0 et mercyGoal
    if (mercy < 0)          mercy = 0;
    if (mercy > mercyGoal)  mercy = mercyGoal;

    // On affiche l'état de la jauge
    std::cout << "  Mercy : " << mercy << "/" << mercyGoal;
    if (mercy >= mercyGoal) {
        std::cout << "  --> Vous pouvez utiliser MERCY !";
    }
    std::cout << "\n";
}

// Retourne true si on peut épargner ce monstre
bool Monster::canBeMercied() const {
    return mercy >= mercyGoal;
}

// Le monstre attaque une entité cible
int Monster::attack(Entity& cible) {
    // Formule du projet : dégâts = rand entre 0 et hpMax de la cible
    int degats = rand() % (cible.getHpMax() + 1);  // +1 car rand()%N donne 0 à N-1

    cible.takeDamage(degats);  // On applique les dégâts à la cible

    // Affichage selon le résultat
    if (degats == 0) {
        std::cout << "  " << name << " attaque mais rate !\n";
    } else {
        std::cout << "  " << name << " attaque " << cible.getName()
                  << " pour " << degats << " degats !"
                  << " (" << cible.getHp() << "/" << cible.getHpMax() << " HP)\n";
    }

    return degats;
}

// Convertit la catégorie en texte
std::string Monster::categoryToString() const {
    if (category == NORMAL)   return "NORMAL";
    if (category == MINIBOSS) return "MINIBOSS";
    if (category == BOSS)     return "BOSS";
    return "?";  // Ne devrait jamais arriver
}

// Redéfinition de display() (obligatoire car virtuelle pure dans Entity)
void Monster::display() const {
    std::cout << "  [" << categoryToString() << "] " << name
              << " | HP : " << hp << "/" << hpMax
              << " | Mercy : " << mercy << "/" << mercyGoal << "\n";
}
