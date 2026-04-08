#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
private:
    std::string nom;
    int valeurSoin;   // Points de vie rendus
    int quantite;

public:
    Item(const std::string& nom, int valeurSoin, int quantite);
    
    std::string getNom() const;
    int getValeurSoin() const;
    int getQuantite() const;
    void setQuantite(int nouvelleQuantite);
    
    void afficher() const;
};

#endif