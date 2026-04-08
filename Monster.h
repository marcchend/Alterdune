#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <vector>

class Player;

enum Categorie {
    NORMAL,
    MINIBOSS,
    BOSS
};

class Monster {
private:
    std::string nom;
    int hp;
    int hpMax;
    Categorie categorie;
    int mercy;
    int objectifMercy;
    bool tue;
    std::vector<std::string> actionsDispo;

public:
    Monster();
    Monster(std::string n, int h, Categorie cat, int objMercy, std::vector<std::string> acts);
    
    // Accesseurs
    std::string getNom() const;
    int getHp() const;
    int getHpMax() const;
    Categorie getCategorie() const;
    int getMercy() const;
    int getObjectifMercy() const;
    bool getTue() const;
    std::vector<std::string> getActionsDispo() const;
    
    // Methodes utilisees
    void prendreDegats(int degats);
    void soigner(int points);
    bool estVivant() const;
    void setTue(bool v);
    
    // Combat
    int attaquer(Player& cible);
    
    // Utilitaires
    std::string categorieEnTexte() const;
};

#endif