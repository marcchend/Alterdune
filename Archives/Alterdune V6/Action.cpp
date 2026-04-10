#include "Action.h"

Action::Action(std::string i, std::string t, int imp) {
    id = i;
    texte = t;
    impact = imp;
}

std::string Action::getId() const {
    return id;
}

std::string Action::getTexte() const {
    return texte;
}

int Action::getImpact() const {
    return impact;
}

void construireCatalogue(std::vector<Action>& catalogue) {
    // On redimensionne pour avoir 10 cases
    catalogue.resize(10);
    
    catalogue[0] = Action("JOKE", "Tu racontes une blague.", 20);
    catalogue[1] = Action("COMPLIMENT", "Tu dis qu'il a de beaux yeux.", 25);
    catalogue[2] = Action("DISCUSS", "Tu parles de la pluie.", 15);
    catalogue[3] = Action("OBSERVE", "Tu l'observes.", 10);
    catalogue[4] = Action("PET", "Tu fais un calin.", 30);
    catalogue[5] = Action("DANCE", "Tu danses.", 20);
    catalogue[6] = Action("OFFER_SNACK", "Tu offres a manger.", 35);
    catalogue[7] = Action("REASON", "Tu parles raison.", 15);
    catalogue[8] = Action("INSULT", "Tu l'insultes.", -20);
    catalogue[9] = Action("THREATEN", "Tu le menaces.", -15);
}

const Action* trouverAction(const std::vector<Action>& catalogue, std::string id) {
    for (int i = 0; i < (int)catalogue.size(); i++) {
        if (catalogue[i].getId() == id) {
            return &catalogue[i];
        }
    }
    return NULL;
}