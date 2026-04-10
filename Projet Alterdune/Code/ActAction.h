#ifndef ACTACTION_H
#define ACTACTION_H

#include <string>
#include <map>

class ActAction {
private:
    std::string id;
    std::string text;
    int mercyImpact;

public:
    ActAction();
    ActAction(const std::string& id, const std::string& text, int mercyImpact);

    std::string getId() const;
    std::string getText() const;
    int getImpact() const;

    void initCatalogue();
    const ActAction& getById(const std::string& id);
    const std::map<std::string, ActAction>& getCatalogue();

private:
    std::map<std::string, ActAction> catalogue;
};

#endif