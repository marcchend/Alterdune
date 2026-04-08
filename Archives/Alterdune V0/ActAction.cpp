#include "ActAction.h"
#include <stdexcept>
#include <iostream>

// ---------- Catalogue statique ----------
static std::map<std::string, ActAction> catalogue;

void ActAction::initCatalogue() {
    // Au moins 8 actions ; au moins 2 à impact négatif (INSULT, THREATEN)
    catalogue = {
        {"JOKE",        {"JOKE",        "Tu racontes une blague de papou. Etonnamment, ca marche.", +20}},
        {"COMPLIMENT",  {"COMPLIMENT",  "Tu dis au monstre qu'il a de beaux yeux. Il rougit.", +25}},
        {"DISCUSS",     {"DISCUSS",     "Vous parlez du prix des potions. C'est profond.", +15}},
        {"OBSERVE",     {"OBSERVE",     "Tu observes le monstre. Il se sent enfin compris.", +10}},
        {"PET",         {"PET",         "Tu lui fais un calin. C'est awkward mais efficace.", +30}},
        {"DANCE",       {"DANCE",       "Tu improvises une danse. Le monstre est hypnotise.", +20}},
        {"OFFER_SNACK", {"OFFER_SNACK", "Tu offres un snack. Personne ne refuse un snack.", +35}},
        {"REASON",      {"REASON",      "Tu expliques calmement pourquoi la violence ne sert a rien.", +15}},
        // Actions negatives (impact sur Mercy)
        {"INSULT",      {"INSULT",      "Tu insultes le monstre. C'etait clairement une mauvaise idee.", -20}},
        {"THREATEN",    {"THREATEN",    "Tu menaces le monstre. Il est maintenant tres en colere.", -15}},
    };
}

ActAction::ActAction(const std::string& id, const std::string& text, int impact)
    : id(id), text(text), mercyImpact(impact) {}

std::string ActAction::getId()   const { return id; }
std::string ActAction::getText() const { return text; }
int ActAction::getImpact()       const { return mercyImpact; }

const ActAction& ActAction::getById(const std::string& id) {
    auto it = catalogue.find(id);
    if (it == catalogue.end())
        throw std::invalid_argument("Action ACT inconnue : " + id);
    return it->second;
}

const std::map<std::string, ActAction>& ActAction::getCatalogue() {
    return catalogue;
}
