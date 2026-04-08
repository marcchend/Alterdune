#pragma once
#include <string>
#include <vector>   // Pour std::vector, qu'on connaît déjà

// ===========================================================
// STRUCTURE : ActAction
// ===========================================================
// Une "struct" en C++ c'est comme une classe, mais tous les
// membres sont "public" par défaut. On l'utilise ici pour
// représenter une action ACT simple, sans comportement complexe.
//
// Le catalogue de toutes les actions est un simple vector<ActAction>
// qu'on crée dans main.cpp. Pas de "static", pas de "map".
// ===========================================================

struct ActAction {
    std::string id;           // Identifiant unique (ex: "JOKE", "INSULT")
    std::string texte;        // Texte affiché quand on utilise l'action
    int         mercyImpact;  // Variation de Mercy : positif = apaise, négatif = énerve
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
std::vector<ActAction> buildCatalogue();

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
const ActAction* findAction(const std::vector<ActAction>& catalogue, const std::string& id);
