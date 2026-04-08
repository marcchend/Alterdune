#pragma once
#include <string>

class Entity; // forward declaration

class Item {
private:
    std::string name;
    int value;       // HP rendus (type HEAL uniquement pour l'instant)
    int quantity;

public:
    Item(const std::string& name, int value, int quantity);

    std::string getName()    const;
    int         getValue()   const;
    int         getQuantity() const;
    bool        isAvailable() const;

    void use(Entity& target); // applique l'effet et décrémente la quantité
    void display() const;
};
