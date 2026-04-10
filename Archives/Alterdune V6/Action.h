#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <vector>

class Action {
private:
    std::string id;
    std::string texte;
    int impact;

public:
    Action() : id(""), texte(""), impact(0) {}  // constructeur par defaut
    Action(std::string i, std::string t, int imp);
    
    std::string getId() const;
    std::string getTexte() const;
    int getImpact() const;
};

// Fonctions pour le catalogue
void construireCatalogue(std::vector<Action>& catalogue);
const Action* trouverAction(const std::vector<Action>& catalogue, std::string id);

#endif