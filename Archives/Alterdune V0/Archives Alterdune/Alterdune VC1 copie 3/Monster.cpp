#include "Monster.h"
#include <iostream>
#include <cstdlib>

Monster::Monster(std::string n, int h, Cat cat, int mg, std::vector<std::string> a)
    : name(n), hp(h), hpMax(h), c(cat), m(0), mg(mg), wk(false), a(a) {}

std::string Monster::getName() const { return name; }
int Monster::getHp() const { return hp; }
int Monster::getHpMax() const { return hpMax; }
Cat Monster::getC() const { return c; }
int Monster::getM() const { return m; }
int Monster::getMg() const { return mg; }
bool Monster::getWk() const { return wk; }
const std::vector<std::string>& Monster::getA() const { return a; }

void Monster::takeDamage(int degats) {
    hp = hp - degats;
    if (hp < 0) hp = 0;
}

void Monster::heal(int soin) {
    hp = hp + soin;
    if (hp > hpMax) hp = hpMax;
}

bool Monster::isAlive() const {
    return hp > 0;
}

void Monster::setWk(bool v) { wk = v; }

void Monster::applyA(const std::string& act) {
    // pas fait
}

bool Monster::canMerc() const {
    // pas fait
    return false;
}

int Monster::att(Player& cible) {
    int dmg = rand() % (cible.getHpMax() + 1);  // 0-100 damage
    cible.takeDamage(dmg);
    if (dmg == 0) {
        std::cout << "  " << name << " rate !\n";
    } else {
        std::cout << "  " << name << " fait " << dmg << " dmg a " << cible.getName() << " (" << cible.getHp() << "/" << cible.getHpMax() << ")\n";
    }
    return dmg;
}

std::string Monster::catStr() const {
    if (c == N) return "NORMAL";
    if (c == M) return "MINIBOSS";
    if (c == B) return "BOSS";
    return "?";
}

void Monster::display() const {
    // pas fait
}
