#include "Monster.h"
#include "Player.h"
#include <iostream>
#include <cstdlib>

Monster::Monster() {
    nom = "";
    hp = 0;
    hpMax = 0;
    categorie = NORMAL;
    mercy = 0;
    objectifMercy = 0;
    tue = false;
}

Monster::Monster(std::string n, int h, Categorie cat, int objMercy, std::vector<std::string> acts) {
    nom = n;
    hp = h;
    hpMax = h;
    categorie = cat;
    mercy = 0;
    objectifMercy = objMercy;
    tue = false;
    actionsDispo = acts;
}

std::string Monster::getNom() const {
    return nom;
}

int Monster::getHp() const {
    return hp;
}

int Monster::getHpMax() const {
    return hpMax;
}

Categorie Monster::getCategorie() const {
    return categorie;
}

int Monster::getMercy() const {
    return mercy;
}

int Monster::getObjectifMercy() const {
    return objectifMercy;
}

bool Monster::getTue() const {
    return tue;
}

std::vector<std::string> Monster::getActionsDispo() const {
    return actionsDispo;
}

void Monster::prendreDegats(int degats) {
    hp = hp - degats;
    if (hp < 0) {
        hp = 0;
    }
}

void Monster::soigner(int points) {
    hp = hp + points;
    if (hp > hpMax) {
        hp = hpMax;
    }
}

bool Monster::estVivant() const {
    return hp > 0;
}

void Monster::setTue(bool v) {
    tue = v;
}

int Monster::attaquer(Player& cible) {
    int degats = rand() % (cible.getHpMax() + 1);
    cible.prendreDegats(degats);
    
    if (degats == 0) {
        std::cout << "  " << nom << " attaque mais rate !" << std::endl;
    } else {
        std::cout << "  " << nom << " inflige " << degats << " degats a " 
                  << cible.getNom() << " !" << std::endl;
    }
    
    return degats;
}

std::string Monster::categorieEnTexte() const {
    if (categorie == NORMAL) return "NORMAL";
    if (categorie == MINIBOSS) return "MINIBOSS";
    if (categorie == BOSS) return "BOSS";
    return "?";
}