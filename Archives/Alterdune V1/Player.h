#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Item.h"
#include <vector>

class Player : public Entity {
private:
    int monstresTues;
    int monstresEpargnes;
    int victoires;
    std::vector<Item> inventaire;

public:
    Player(const std::string& nom, int hpMax);
    
    // Accesseurs
    int getMonstresTues() const;
    int getMonstresEpargnes() const;
    int getVictoires() const;
    
    // Ajouter une victoire
    void ajouterVictoire(bool tue);
    
    // Gestion inventaire
    void ajouterItem(const Item& item);
    std::vector<Item>& getInventaire();
    
    // Utiliser un item (retourne true si réussi)
    bool utiliserItem(int index);
    
    // Afficher
    void afficher() const override;
    void afficherInventaire() const;
    void afficherStats() const;
    
    // Type de fin
    std::string getTypeFin() const;
};

#endif