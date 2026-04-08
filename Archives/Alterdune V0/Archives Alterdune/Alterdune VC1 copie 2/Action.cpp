#include "Action.h"

// Catalogue statique
std::vector<Action> Action::catalogue;

// ===========================================================
// initCatalogue() : initialise le catalogue
// ===========================================================
void Action::initCatalogue() {
    catalogue = buildCatalogue();
}

// ===========================================================
// getById() : retourne l'action par id
// ===========================================================
const Action& Action::getById(const std::string& id) {
    for (const auto& act : catalogue) {
        if (act.getId() == id) {
            return act;
        }
    }
    // Si pas trouvé, retourner la première (ou gérer erreur, mais pour simplifier)
    return catalogue[0];
}

// ===========================================================
// getCatalogue() : retourne le catalogue
// ===========================================================
const std::vector<Action>& Action::getCatalogue() {
    return catalogue;
}

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

std::vector<Action> buildCatalogue() {

    // On crée le vecteur avec une liste d'initialisation
    // Chaque ligne = une Action {id, texte, mercyImpact}
    std::vector<Action> catalogue = {
        Action("JOKE",        "Tu racontes une blague terrible. Le monstre rit malgre lui.",     +20),
        Action("COMPLIMENT",  "Tu dis au monstre qu'il a de beaux yeux. Il rougit.",             +25),
        Action("DISCUSS",     "Vous discutez du prix des potions. C'est plus profond qu'on croit.", +15),
        Action("OBSERVE",     "Tu observes le monstre en silence. Il se sent enfin compris.",    +10),
        Action("PET",         "Tu lui fais un calin maladroit. C'est awkward mais efficace.",    +30),
        Action("DANCE",       "Tu improvises une danse. Le monstre est hypnotise.",              +20),
        Action("OFFER_SNACK", "Tu lui offres un snack. Personne ne refuse un snack.",            +35),
        Action("REASON",      "Tu expliques calmement pourquoi la violence ne sert a rien.",     +15),
        // --- Actions à impact NÉGATIF (obligatoire : min 2) ---
        Action("INSULT",      "Tu insultes le monstre. C'etait clairement une mauvaise idee.",  -20),
        Action("THREATEN",    "Tu brandis ton poing. Le monstre est maintenant tres en colere.",-15)
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

const Action* findAction(const std::vector<Action>& catalogue, const std::string& id) {
    // i = indice courant, catalogue.size() = nombre d'éléments
    for (int i = 0; i < (int)catalogue.size(); i++) {
        if (catalogue[i].getId() == id) {
            return &catalogue[i];  // On retourne l'adresse (pointeur) de l'élément
        }
    }
    return nullptr;  // Rien trouvé
}
