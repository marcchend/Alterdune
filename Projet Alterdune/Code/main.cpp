// main.cpp
#include <iostream>
#include <string>

#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "ActAction.h"
#include "FileLoader.h"
#include "Game.h"

int main() {
    std::string playerName;
    std::cout << "=== ALTERDUNE ===" << std::endl;
    std::cout << "Entrez le nom de votre personnage : ";
    std::cin >> playerName;
    
    Game game;
    game.start(playerName);
    
    return 0;
}