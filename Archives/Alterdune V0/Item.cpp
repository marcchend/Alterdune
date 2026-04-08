#include "Item.h"
#include "Entity.h"
#include <iostream>

Item::Item(const std::string& name, int value, int quantity)
    : name(name), value(value), quantity(quantity) {}

std::string Item::getName()     const { return name; }
int         Item::getValue()    const { return value; }
int         Item::getQuantity() const { return quantity; }
bool        Item::isAvailable() const { return quantity > 0; }

void Item::use(Entity& target) {
    if (quantity <= 0) {
        std::cout << "  [Aucune " << name << " restante !]\n";
        return;
    }
    int before = target.getHp();
    target.setHp(target.getHp() + value);
    int healed = target.getHp() - before;
    quantity--;
    std::cout << "  " << target.getName() << " utilise " << name
              << " et récupère " << healed << " HP. ("
              << target.getHp() << "/" << target.getHpMax() << " HP)\n";
}

void Item::display() const {
    std::cout << "  - " << name << "  |  Soin : +" << value
              << " HP  |  Qte : " << quantity << "\n";
}
