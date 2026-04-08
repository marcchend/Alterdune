#include "Item.h"

Item::Item(std::string n, int v, int q) {
    nom = n;
    valeur = v;
    quantite = q;
}

std::string Item::getNom() const {
    return nom;
}

int Item::getValeur() const {
    return valeur;
}

int Item::getQuantite() const {
    return quantite;
}