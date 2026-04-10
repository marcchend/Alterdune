// Item.h
#ifndef ITEM_H
#define ITEM_H

#include <string>

class Entity;

class Item {
private:
    std::string name;
    int value;
    int quantity;

public:
    Item();
    Item(const std::string& name, int value, int quantity);

    std::string getName() const;
    int getValue() const;
    int getQuantity() const;
    bool isAvailable() const;

    void use(Entity& target);
    void display() const;
};

#endif