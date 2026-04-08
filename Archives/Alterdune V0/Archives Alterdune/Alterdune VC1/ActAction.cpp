#include "ActAction.h"

// ===========================================================
// buildCatalogue() : construit la liste de toutes les actions ACT
//
// On utilise la syntaxe d'initialisation de struct :
//   {"ID", "texte affiché", impactMercy}
//
// Contraintes respectées :
//   - Au moins 8 actions différentes ✓
//   - Au moins 2 actions à impact NÉGATIF (INSULT, THREATEN) ✓
//   - Impact borné dans Monster::applyAct(), pas ici ✓
// ===========================================================

std::vector<ActAction> buildCatalogue() {

    // On crée le vecteur avec une liste d'initialisation
    // Chaque ligne = une ActAction {id, texte, mercyImpact}
    std::vector<ActAction> catalogue = {
        {"JOKE",        "Tu racontes une blague terrible. Le monstre rit malgre lui.",     +20},
        {"COMPLIMENT",  "Tu dis au monstre qu'il a de beaux yeux. Il rougit.",             +25},
        {"DISCUSS",     "Vous discutez du prix des potions. C'est plus profond qu'on croit.", +15},
        {"OBSERVE",     "Tu observes le monstre en silence. Il se sent enfin compris.",    +10},
        {"PET",         "Tu lui fais un calin maladroit. C'est awkward mais efficace.",    +30},
        {"DANCE",       "Tu improvises une danse. Le monstre est hypnotise.",              +20},
        {"OFFER_SNACK", "Tu lui offres un snack. Personne ne refuse un snack.",            +35},
        {"REASON",      "Tu expliques calmement pourquoi la violence ne sert a rien.",     +15},
        // --- Actions à impact NÉGATIF (obligatoire : min 2) ---
        {"INSULT",      "Tu insultes le monstre. C'etait clairement une mauvaise idee.",  -20},
        {"THREATEN",    "Tu brandis ton poing. Le monstre est maintenant tres en colere.",-15}
    };

    return catalogue;  // Le vecteur est retourné par copie
}

// ===========================================================
// findAction() : recherche linéaire dans le catalogue
//
// On parcourt le vecteur avec une boucle for classique.
// Dès qu'on trouve l'id correspondant, on retourne l'adresse de cet élément.
// Si rien n'est trouvé, on retourne nullptr.
// ===========================================================

const ActAction* findAction(const std::vector<ActAction>& catalogue, const std::string& id) {
    // i = indice courant, catalogue.size() = nombre d'éléments
    for (int i = 0; i < (int)catalogue.size(); i++) {
        if (catalogue[i].id == id) {
            return &catalogue[i];  // On retourne l'adresse (pointeur) de l'élément
        }
    }
    return nullptr;  // Rien trouvé
}
