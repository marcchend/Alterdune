#include "Item.h"
#include "Player.h"
#include <iostream>

Item::Item(const std::string& n, int v, int q) : n(n), v(v), q(q) {}

std::string Item::getN() const { return n; }
int Item::getV() const { return v; }
int Item::getQ() const { return q; }
bool Item::isAv() const { return q > 0; }

void Item::useOn(Player& cible) {
    // pas fait
}

void Item::disp() const {
    // pas fait
}