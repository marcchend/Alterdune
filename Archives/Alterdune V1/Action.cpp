#include "Action.h"

Action::Action(const std::string& id, const std::string& texte, int impactMercy)
    : id(id), texte(texte), impactMercy(impactMercy) {}

std::string Action::getId() const { return id; }
std::string Action::getTexte() const { return texte; }
int Action::getImpactMercy() const { return impactMercy; }

std::vector<Action> initialiserCatalogueActions() {
    std::vector<Action> catalogue;
    
    // Ajouter les actions disponibles
    catalogue.push_back(Action("COMPLIMENT", "Vous faites un compliment au monstre!", 25));
    catalogue.push_back(Action("JOKE", "Vous racontez une blague!", 15));
    catalogue.push_back(Action("DANCE", "Vous dansez!", 30));
    catalogue.push_back(Action("SING", "Vous chantez!", 20));
    
    return catalogue;
}

const Action* trouverActionParId(const std::vector<Action>& catalogue, const std::string& id) {
    for (const Action& action : catalogue) {
        if (action.getId() == id) {
            return &action;
        }
    }
    return nullptr;
}