#pragma once         // Empêche ce fichier d'être inclus deux fois par le compilateur
#include <string>    // Pour utiliser std::string

// ===========================================================
// CLASSE ABSTRAITE : Entity
// ===========================================================
// Une classe abstraite = une classe qu'on ne peut PAS instancier directement.
// Elle sert de "modèle commun" pour Player et Monster.
// Tout ce qui est commun (nom, HP) est défini ici une seule fois.
// ===========================================================

class Entity {

// "protected" = accessible par cette classe ET ses classes filles (Player, Monster)
// Contrairement à "private" qui bloquerait l'accès aux classes filles
protected:
    std::string name;  // Nom de l'entité (joueur ou monstre)
    int hp;            // Points de vie actuels
    int hpMax;         // Points de vie maximum

// "public" = accessible depuis n'importe où dans le programme
public:

    // Constructeur : appelé à la création d'un Player ou Monster
    Entity(std::string nom, int pointsDeVieMax);

    // Destructeur virtuel : obligatoire dès qu'on utilise l'héritage
    // Cela garantit que le bon destructeur est appelé selon le vrai type de l'objet
    virtual ~Entity();

    // ----- Accesseurs (getters) -----
    std::string getName() const;  // Retourne le nom
    int         getHp()   const;  // Retourne les HP actuels
    int         getHpMax()const;  // Retourne les HP maximum

    // ----- Modificateurs -----
    void takeDamage(int degats);  // Réduit les HP (minimum 0)
    void heal(int soin);          // Augmente les HP (maximum hpMax)
    bool isAlive() const;         // Retourne true si hp > 0

    // ===========================================================
    // MÉTHODE VIRTUELLE PURE : display()
    //
    // Le "= 0" signifie deux choses :
    //   1. Cette méthode N'A PAS d'implémentation dans Entity
    //   2. Chaque classe fille EST OBLIGÉE de la redéfinir
    //
    // C'est ce qui rend Entity "abstraite" :
    //   Entity e("test", 100);   <-- le compilateur REFUSE
    //
    // Par contre on peut faire :
    //   Player p("Alice", 100);  <-- OK car Player redéfinit display()
    //   Monster m(...);          <-- OK car Monster redéfinit display()
    // ===========================================================
    virtual void display() const = 0;
};
