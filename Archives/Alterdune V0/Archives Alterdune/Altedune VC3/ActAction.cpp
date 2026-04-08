#include "ActAction.h"

ActAction::ActAction(std::string id_, std::string description_, int mercyGain_)
    : id(std::move(id_)), description(std::move(description_)), mercyGain(mercyGain_) {
}

std::vector<ActAction> buildCatalogue() {
    return {
        ActAction("PET", "Caresser le monstre", 10),
        ActAction("BRIBE", "Offrir un cadeau", 20),
        ActAction("APOLOGIZE", "S'excuser sincerement", 15),
        ActAction("SING", "Chanter une chanson douce", 5)
    };
}

const ActAction* findAction(const std::vector<ActAction>& catalogue, const std::string& id) {
    for (const ActAction& action : catalogue) {
        if (action.id == id) {
            return &action;
        }
    }
    return nullptr;
}
