#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Item.h"

class Player {
private:
    std::string nom;
    int hp;
    int hpMax;
    int kills;
    int epargnes;
    int victoires;
    std::vector<Item> inventaire;  // Declare mais pas utilise

public:
    Player(std::string n, int h);
    
    // Accesseurs
    std::string getNom() const;
    int getHp() const;
    int getHpMax() const;
    int getKills() const;
    int getEpargnes() const;
    int getVictoires() const;
    
    // Methodes utilisees
    void prendreDegats(int degats);
    void soigner(int points);
    bool estVivant() const;
    void ajouterVictoire(bool tue);
    
    // Pour l'inventaire (non utilise mais garde pour la compatibilite)
    void ajouterItem(Item i);
    
    // Utilitaires
    std::string getTypeFin() const;
    void afficherStats() const;
    void afficher() const;
};

#endif