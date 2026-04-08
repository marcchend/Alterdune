#include "Item.h"
#include "Entity.h"
#include <iostream>

Item::Item(const std::string& name, int value, int quantity)
    : name(name), value(value), quantity(quantity) {}

std::string Item::getName()     const { return name; }
int         Item::getValue()    const { return value; }
int         Item::getQuantity() const { return quantity; }
bool        Item::isAvailable() const { return quantity > 0; }

void Item::useOn(Entity& cible) {
    if (!isAvailable()) {
        std::cout << "  Item indisponible.\n";
        return;
    }
    cible.heal(value);
    quantity--;
    std::cout << "  Vous utilisez " << name << " et soignez " << value << " HP !\n";
}

void Item::display() const {
    std::cout << "  - " << name << " (x" << quantity << ") : +" << value << " HP\n";
}