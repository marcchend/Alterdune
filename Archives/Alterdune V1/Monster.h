#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"
#include "Action.h"
#include <string>
#include <vector>

enum class CategorieMonstre {
    NORMAL,
    MINIBOSS,
    BOSS
};

class Monster : public Entity {
private:
    CategorieMonstre categorie;
    int mercy;           // Jauge de clémence (0 à mercyObjectif)
    int mercyObjectif;
    std::vector<std::string> actionsDisponibles;  // IDs des actions ACT
    bool tue;            // True si le monstre a été tué, false si épargné

public:
    Monster(const std::string& nom, int hpMax, CategorieMonstre categorie,
            int mercyObjectif, const std::vector<std::string>& actionsDisponibles);
    
    // Accesseurs
    CategorieMonstre getCategorie() const;
    int getMercy() const;
    int getMercyObjectif() const;
    bool getTue() const;
    void setTue(bool tue);
    const std::vector<std::string>& getActionsDisponibles() const;
    
    // Mécanique Mercy
    void appliquerAction(const Action& action);
    bool peutEtreEpargne() const;
    
    // Combat
    int attaquer(Entity& cible) const;  // Dégâts aléatoires entre 0 et hpMax de la cible
    
    // Affichage
    void afficher() const override;
    
    // Utilitaires
    static std::string categorieToString(CategorieMonstre cat);
};

#endif