#pragma once
#include "Entity.h"       // Monster hérite de Entity
#include "Action.h"       // Pour utiliser Action et le catalogue
#include <vector>
#include <string>

// ===========================================================
// ÉNUMÉRATION : Category
// ===========================================================
// Un "enum" définit un ensemble de valeurs nommées.
// Au lieu d'écrire if (cat == 0) ou if (cat == "NORMAL"),
// on écrit if (cat == Category::NORMAL) → plus lisible et sûr.
// ===========================================================
enum Category {
    NORMAL,    // valeur = 0 en interne
    MINIBOSS,  // valeur = 1
    BOSS       // valeur = 2
};

// ===========================================================
// CLASSE : Monster
// ===========================================================
// Monster HÉRITE de Entity.
// "public Entity" signifie qu'on hérite de tout ce qui est
// public et protected dans Entity (name, hp, hpMax, etc.)
// ===========================================================

class Monster : public Entity {
private:
    Category    category;     // NORMAL, MINIBOSS ou BOSS
    int         mercy;        // Jauge Mercy actuelle (commence à 0)
    int         mercyGoal;    // Seuil pour pouvoir épargner (souvent 100)
    bool        wasKilled;    // true = tué, false = épargné (utile pour le bestiaire)

    // Liste des identifiants d'actions ACT disponibles pour CE monstre
    // ex: {"COMPLIMENT", "DISCUSS"} pour un NORMAL
    std::vector<std::string> actIds;

public:
    // Constructeur
    Monster(std::string nom, int pointsDeVieMax, Category categorie,
            int objectifMercy, std::vector<std::string> listeActIds);

    // --- Accesseurs ---
    Category                         getCategory() const;
    int                              getMercy()    const;
    int                              getMercyGoal()const;
    bool                             getWasKilled()const;
    const std::vector<std::string>&  getActIds()   const;  // & = retourne par référence constante (pas de copie)

    // Marque si le monstre a été tué ou épargné (stocké pour le bestiaire)
    void setWasKilled(bool valeur);

    // Applique une action ACT : modifie la jauge Mercy (bornée entre 0 et mercyGoal)
    // On passe l'action par référence constante pour éviter une copie inutile
    void applyAct(const Action& action);

    // Retourne true si mercy >= mercyGoal (peut être épargné)
    bool canBeMercied() const;

    // Attaque une entité (joueur) et retourne les dégâts infligés
    // On passe la cible par référence pour modifier ses HP
    int attack(Entity& cible);

    // Utilitaire : convertit la catégorie en texte lisible
    std::string categoryToString() const;

    // Override de la méthode virtuelle pure de Entity
    // "override" dit au compilateur "je redéfinis intentionnellement une méthode virtuelle"
    // → le compilateur signale une erreur si on fait une faute de frappe
    void display() const override;
};
