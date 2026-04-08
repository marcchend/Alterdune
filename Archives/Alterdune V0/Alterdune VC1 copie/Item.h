#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
private:
    std::string nom;
    int valeur;
    int quantite;

public:
    Item(std::string n, int v, int q);
    
    std::string getNom() const;
    int getValeur() const;
    int getQuantite() const;
};

#endif