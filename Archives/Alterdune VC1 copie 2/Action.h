#pragma once
#include <string>
#include <vector>   // Pour std::vector, qu'on connaît déjà

// ===========================================================
// CLASSE : Action
// ===========================================================
// Représente une action ACT.
// ===========================================================

class Action {
private:
    std::string id;           // Identifiant unique (ex: "JOKE", "INSULT")
    std::string texte;        // Texte affiché quand on utilise l'action
    int         mercyImpact;  // Variation de Mercy : positif = apaise, négatif = énerve

    static std::vector<Action> catalogue;

public:
    // Constructeur
    Action(std::string i, std::string t, int mi) : id(i), texte(t), mercyImpact(mi) {}

    // Accesseurs
    std::string getId() const { return id; }
    std::string getTexte() const { return texte; }
    int getMercyImpact() const { return mercyImpact; }

    // Méthodes statiques
    static void initCatalogue();
    static const Action& getById(const std::string& id);
    static const std::vector<Action>& getCatalogue();
};

// ===========================================================
// Fonction libre (pas dans une classe) : buildCatalogue()
//
// Crée et retourne le vecteur contenant TOUTES les actions ACT.
// On appelle cette fonction une seule fois dans main().
//
// On retourne par valeur : le vecteur est copié à la sortie.
// C'est simple et suffisant pour notre projet.
// ===========================================================
std::vector<Action> buildCatalogue();

// ===========================================================
// Fonction libre : findAction()
//
// Cherche une action par son id dans le catalogue.
// Retourne un POINTEUR vers l'action trouvée, ou nullptr si introuvable.
//
// On utilise un pointeur ici car :
//   - Si on retournait par valeur, on ne pourrait pas signaler "pas trouvé"
//   - nullptr est la convention C++ pour "rien trouvé"
// ===========================================================
const Action* findAction(const std::vector<Action>& catalogue, const std::string& id);
