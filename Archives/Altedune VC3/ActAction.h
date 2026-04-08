#pragma once
#include <string>
#include <vector>

struct ActAction {
    std::string id;
    std::string description;
    int mercyGain;

    ActAction(std::string id_, std::string description_, int mercyGain_);
};

std::vector<ActAction> buildCatalogue();
const ActAction* findAction(const std::vector<ActAction>& catalogue, const std::string& id);
