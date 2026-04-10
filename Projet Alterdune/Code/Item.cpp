// Item.cpp
#include "Item.h"
#include "Entity.h"
#include <iostream>

Item::Item() {
    name = "";
    value = 0;
    quantity = 0;
}

Item::Item(const std::string& name, int value, int quantity) {
    this->name = name;
    this->value = value;
    this->quantity = quantity;
}

std::string Item::getName() const {
    return name;
}

int Item::getValue() const {
    return value;
}

int Item::getQuantity() const {
    return quantity;
}

bool Item::isAvailable() const {
    if (quantity > 0) {
        return true;
    }
    return false;
}

void Item::use(Entity& target) {
    if (quantity <= 0) {
        std::cout << "  [Aucune " << name << " restante !]" << std::endl;
        return;
    }
    
    int before = target.getHp();
    int newHp = before + value;
    target.setHp(newHp);
    int healed = target.getHp() - before;
    quantity = quantity - 1;
    
    std::cout << "  " << target.getName() << " utilise " << name
              << " et recupere " << healed << " HP. ("
              << target.getHp() << "/" << target.getHpMax() << " HP)" << std::endl;
}

void Item::display() const {
    std::cout << "  - " << name << "  |  Soin : +" << value
              << " HP  |  Qte : " << quantity << std::endl;
}