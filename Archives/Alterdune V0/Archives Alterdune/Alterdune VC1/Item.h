#pragma once
#include <string>
#include "Entity.h"   // Nécessaire car useOn() prend une Entity& en paramètre

// ===========================================================
// CLASSE : Item
// ===========================================================
// Représente un objet utilisable par le joueur (type HEAL = soin).
// Item N'hérite PAS de Entity : c'est un objet, pas un combattant.
// ===========================================================

class Item {
private:
    std::string name;  // Nom de l'item (ex: "Potion")
    int value;         // Nombre de HP rendus lors de l'utilisation
    int quantity;      // Quantité disponible dans l'inventaire

public:
    // Constructeur : crée un item avec son nom, sa valeur de soin et sa quantité
    Item(std::string nom, int valeurSoin, int quantiteInitiale);

    // --- Accesseurs ---
    std::string getName()    const;  // Retourne le nom
    int         getValue()   const;  // Retourne la valeur de soin
    int         getQuantity()const;  // Retourne la quantité restante

    // Retourne true s'il reste au moins 1 exemplaire
    bool isAvailable() const;

    // Utilise l'item sur une cible : soigne et décrémente la quantité
    // On passe la cible par RÉFÉRENCE (&) pour modifier ses HP directement
    // (sans &, on travaillerait sur une copie et rien ne changerait)
    void useOn(Entity& cible);

    // Affiche l'item dans la console
    void display() const;
};
