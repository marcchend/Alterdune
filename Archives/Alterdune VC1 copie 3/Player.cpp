#include "Player.h"
#include <iostream>

Player::Player(const std::string& n, int h) : name(n), hp(h), hpMax(h), k(0), s(0), w(0) {}

std::string Player::getName() const { return name; }
int Player::getHp() const { return hp; }
int Player::getHpMax() const { return hpMax; }
int Player::getK() const { return k; }
int Player::getS() const { return s; }
int Player::getW() const { return w; }

void Player::takeDamage(int degats) {
    hp = hp - degats;
    if (hp < 0) hp = 0;
}

void Player::heal(int soin) {
    hp = hp + soin;
    if (hp > hpMax) hp = hpMax;
}

bool Player::isAlive() const {
    return hp > 0;
}

void Player::addW(bool killed) {
    w++;
    if (killed) k++;
    else s++;
}

void Player::addI(const Item& i) {
    // pas fait
}

std::vector<Item>& Player::getInv() {
    // pas fait
    static std::vector<Item> empty;
    return empty;
}

std::string Player::getEnd() const {
    return "Fin";
}

void Player::display() const {
    std::cout << "  Joueur : " << name << "  HP: " << hp << "/" << hpMax << "\n";
}

void Player::dispInv() const {
    // pas fait
}

void Player::dispStats() const {
    std::cout << "\n=== Stats de " << name << " ===\n";
    std::cout << "  HP : " << hp << "/" << hpMax << "\n";
    std::cout << "  Wins : " << w << "/10\n";
    std::cout << "  Kills : " << k << "\n";
    std::cout << "  Spared : " << s << "\n";
    std::cout << "  End: " << getEnd() << "\n";
}