#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <vector>

class Action {
private:
    std::string id;
    std::string texte;
    int impactMercy;  // positif = apaise, négatif = énerve

public:
    Action(const std::string& id, const std::string& texte, int impactMercy);
    
    std::string getId() const;
    std::string getTexte() const;
    int getImpactMercy() const;
};

// Fonction pour initialiser le catalogue (appelée une fois au début)
std::vector<Action> initialiserCatalogueActions();

// Fonction pour trouver une action par son ID
const Action* trouverActionParId(const std::vector<Action>& catalogue, const std::string& id);

#endif