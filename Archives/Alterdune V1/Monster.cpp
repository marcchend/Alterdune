#include "Monster.h"
#include <iostream>
#include <random>
#include <algorithm>

Monster::Monster(const std::string& nom, int hpMax, CategorieMonstre categorie,
                 int mercyObjectif, const std::vector<std::string>& actionsDisponibles)
    : Entity(nom, hpMax), categorie(categorie), mercy(0), 
      mercyObjectif(mercyObjectif), actionsDisponibles(actionsDisponibles), tue(false) {}

CategorieMonstre Monster::getCategorie() const { return categorie; }
int Monster::getMercy() const { return mercy; }
int Monster::getMercyObjectif() const { return mercyObjectif; }
bool Monster::getTue() const { return tue; }
void Monster::setTue(bool tue) { this->tue = tue; }
const std::vector<std::string>& Monster::getActionsDisponibles() const { return actionsDisponibles; }

void Monster::appliquerAction(const Action& action) {
    int ancienneMercy = mercy;
    mercy += action.getImpactMercy();
    
    // Borner la mercy entre 0 et mercyObjectif
    if (mercy < 0) mercy = 0;
    if (mercy > mercyObjectif) mercy = mercyObjectif;
    
    std::cout << "  " << action.getTexte() << std::endl;
    std::cout << "  Mercy: " << mercy << "/" << mercyObjectif;
    if (mercy >= mercyObjectif) {
        std::cout << " (MERCY disponible !)";
    }
    std::cout << std::endl;
}

bool Monster::peutEtreEpargne() const {
    return mercy >= mercyObjectif;
}

int Monster::attaquer(Entity& cible) const {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, cible.getHpMax());
    int degats = dist(rng);
    
    cible.prendreDegats(degats);
    
    if (degats == 0) {
        std::cout << "  " << nom << " attaque mais rate !" << std::endl;
    } else {
        std::cout << "  " << nom << " inflige " << degats << " degats a " 
                  << cible.getNom() << " !" << std::endl;
        std::cout << "  " << cible.getNom() << " a maintenant " 
                  << cible.getHp() << "/" << cible.getHpMax() << " HP" << std::endl;
    }
    
    return degats;
}

void Monster::afficher() const {
    std::cout << "  [" << categorieToString(categorie) << "] " << nom 
              << " | HP: " << hp << "/" << hpMax 
              << " | Mercy: " << mercy << "/" << mercyObjectif;
    if (tue) {
        std::cout << " | TUÉ";
    } else {
        std::cout << " | ÉPARGNÉ";
    }
    std::cout << std::endl;
}

std::string Monster::categorieToString(CategorieMonstre cat) {
    if (cat == CategorieMonstre::NORMAL) return "NORMAL";
    if (cat == CategorieMonstre::MINIBOSS) return "MINIBOSS";
    return "BOSS";
}