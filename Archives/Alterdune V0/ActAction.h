#pragma once
#include <string>
#include <map>

// Représente une action ACT du catalogue pré-défini
class ActAction {
private:
    std::string id;
    std::string text;
    int mercyImpact;  // positif = apaise, négatif = énerve

public:
    ActAction() = default;
    ActAction(const std::string& id, const std::string& text, int mercyImpact);

    std::string getId()     const;
    std::string getText()   const;
    int getImpact()         const;

    // Catalogue statique : initialisé une fois, accessible partout
    static void initCatalogue();
    static const ActAction& getById(const std::string& id);
    static const std::map<std::string, ActAction>& getCatalogue();
};
