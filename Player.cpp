#include "Player.h"
#include <iostream>

Player::Player(std::string n, int h) {
    nom = n;
    hp = h;
    hpMax = h;
    kills = 0;
    epargnes = 0;
    victoires = 0;
}

std::string Player::getNom() const {
    return nom;
}

int Player::getHp() const {
    return hp;
}

int Player::getHpMax() const {
    return hpMax;
}

int Player::getKills() const {
    return kills;
}

int Player::getEpargnes() const {
    return epargnes;
}

int Player::getVictoires() const {
    return victoires;
}

void Player::prendreDegats(int degats) {
    hp = hp - degats;
    if (hp < 0) {
        hp = 0;
    }
}

void Player::soigner(int points) {
    hp = hp + points;
    if (hp > hpMax) {
        hp = hpMax;
    }
}

bool Player::estVivant() const {
    return hp > 0;
}

void Player::ajouterVictoire(bool tue) {
    victoires++;
    if (tue) {
        kills++;
    } else {
        epargnes++;
    }
}

void Player::ajouterItem(Item i) {
    // Pas utilise - juste pour que le code compile
}

std::string Player::getTypeFin() const {
    if (epargnes == 0) return "Genocidaire";
    if (kills == 0) return "Pacifiste";
    return "Neutre";
}

void Player::afficherStats() const {
    std::cout << "\n=== Stats de " << nom << " ===\n";
    std::cout << "  HP : " << hp << "/" << hpMax << std::endl;
    std::cout << "  Victoires : " << victoires << "/10" << std::endl;
    std::cout << "  Tue : " << kills << std::endl;
    std::cout << "  Epargne : " << epargnes << std::endl;
    std::cout << "  Fin prevue : " << getTypeFin() << std::endl;
}

void Player::afficher() const {
    std::cout << "  Joueur : " << nom << "  HP: " << hp << "/" << hpMax << std::endl;
}