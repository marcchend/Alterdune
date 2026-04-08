#include "Action.h"

// Constructeur
Action::Action(std::string i, std::string t, int imp) {
    id = i;
    texte = t;
    impact = imp;
}

// Accesseurs
std::string Action::getId() const {
    return id;
}

std::string Action::getTexte() const {
    return texte;
}

int Action::getImpact() const {
    return impact;
}

// Construit le catalogue (10 actions)
std::vector<Action> construireCatalogue() {
    std::vector<Action> catalogue;
    
    catalogue.push_back(Action("JOKE", "Tu racontes une blague.", 20));
    catalogue.push_back(Action("COMPLIMENT", "Tu dis qu'il a de beaux yeux.", 25));
    catalogue.push_back(Action("DISCUSS", "Tu parles de la pluie.", 15));
    catalogue.push_back(Action("OBSERVE", "Tu l'observes.", 10));
    catalogue.push_back(Action("PET", "Tu fais un calin.", 30));
    catalogue.push_back(Action("DANCE", "Tu danses.", 20));
    catalogue.push_back(Action("OFFER_SNACK", "Tu offres a manger.", 35));
    catalogue.push_back(Action("REASON", "Tu parles raison.", 15));
    catalogue.push_back(Action("INSULT", "Tu l'insultes.", -20));
    catalogue.push_back(Action("THREATEN", "Tu le menaces.", -15));
    
    return catalogue;
}

// Cherche une action
const Action* trouverAction(const std::vector<Action>& catalogue, std::string id) {
    for (int i = 0; i < (int)catalogue.size(); i++) {
        if (catalogue[i].getId() == id) {
            return &catalogue[i];
        }
    }
    return NULL;
}