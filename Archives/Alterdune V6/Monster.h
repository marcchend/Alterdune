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
    bool epargne;
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
    bool getEpargne() const;
    std::vector<std::string> getActionsDispo() const;
    
    // Methodes utilisees
    void prendreDegats(int degats);
    void soigner(int points);
    bool estVivant() const;
    void setTue(bool v);
    void setEpargne(bool v);

    // Systeme Mercy
    void ajouterMercy(int valeur);   // ajoute (ou retire) des points de mercy
    bool mercyEstPlein() const;      // retourne true si mercy >= objectifMercy
    
    // Combat
    int attaquer(Player& cible);
    
    // Utilitaires
    std::string categorieEnTexte() const;
};

#endif