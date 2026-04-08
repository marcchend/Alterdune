#include "Item.h"
#include <iostream>

Item::Item(const std::string& nom, int valeurSoin, int quantite)
    : nom(nom), valeurSoin(valeurSoin), quantite(quantite) {}

std::string Item::getNom() const { return nom; }
int Item::getValeurSoin() const { return valeurSoin; }
int Item::getQuantite() const { return quantite; }
void Item::setQuantite(int nouvelleQuantite) { quantite = nouvelleQuantite; }

void Item::afficher() const {
    std::cout << "  - " << nom << " x" << quantite << " (soigne " << valeurSoin << " HP)" << std::endl;
}