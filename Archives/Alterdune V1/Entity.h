#ifndef ENTITY_H
#define ENTITY_H

#include <string>

// Classe abstraite (contient une méthode virtuelle pure)
class Entity {
protected:
    std::string nom;
    int hp;
    int hpMax;

public:
    Entity(const std::string& nom, int hpMax);
    virtual ~Entity() {}  // Destructeur virtuel (important pour le polymorphisme)
    
    // Accesseurs
    std::string getNom() const;
    int getHp() const;
    int getHpMax() const;
    
    // Modificateurs
    void setHp(int nouveauHp);
    void prendreDegats(int degats);
    void soigner(int montant);
    bool estVivant() const;
    
    // Méthode virtuelle pure (rend la classe abstraite)
    virtual void afficher() const = 0;
};

#endif