#include "ActAction.h"
#include <stdexcept>
#include <iostream>

ActAction::ActAction() {
    id = "";
    text = "";
    mercyImpact = 0;
}

ActAction::ActAction(const std::string& id, const std::string& text, int impact) {
    this->id = id;
    this->text = text;
    this->mercyImpact = impact;
}

std::string ActAction::getId() const {
    return id;
}

std::string ActAction::getText() const {
    return text;
}

int ActAction::getImpact() const {
    return mercyImpact;
}

void ActAction::initCatalogue() {
    catalogue.clear();
    
    ActAction action1("JOKE", "Tu racontes une blague de papou. Etonnamment, ca marche.", 20);
    catalogue["JOKE"] = action1;
    
    ActAction action2("COMPLIMENT", "Tu dis au monstre qu'il a de beaux yeux. Il rougit.", 25);
    catalogue["COMPLIMENT"] = action2;
    
    ActAction action3("DISCUSS", "Vous parlez du prix des potions. C'est profond.", 15);
    catalogue["DISCUSS"] = action3;
    
    ActAction action4("OBSERVE", "Tu observes le monstre. Il se sent enfin compris.", 10);
    catalogue["OBSERVE"] = action4;
    
    ActAction action5("PET", "Tu lui fais un calin. C'est awkward mais efficace.", 30);
    catalogue["PET"] = action5;
    
    ActAction action6("DANCE", "Tu improvises une danse. Le monstre est hypnotise.", 20);
    catalogue["DANCE"] = action6;
    
    ActAction action7("OFFER_SNACK", "Tu offres un snack. Personne ne refuse un snack.", 35);
    catalogue["OFFER_SNACK"] = action7;
    
    ActAction action8("REASON", "Tu expliques calmement pourquoi la violence ne sert a rien.", 15);
    catalogue["REASON"] = action8;
    
    ActAction action9("INSULT", "Tu insultes le monstre. C'etait clairement une mauvaise idee.", -20);
    catalogue["INSULT"] = action9;
    
    ActAction action10("THREATEN", "Tu menaces le monstre. Il est maintenant tres en colere.", -15);
    catalogue["THREATEN"] = action10;
}

const ActAction& ActAction::getById(const std::string& id) {
    std::map<std::string, ActAction>::iterator it = catalogue.find(id);
    if (it == catalogue.end()) {
        throw std::invalid_argument("Action ACT inconnue : " + id);
    }
    return it->second;
}

const std::map<std::string, ActAction>& ActAction::getCatalogue() {
    return catalogue;
}