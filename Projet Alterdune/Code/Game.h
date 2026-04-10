// Game.h
#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Monster.h"
#include "ActAction.h"
#include <vector>
#include <string>

class Game {
private:
    ActAction actCatalogue;
    Player* player;
    std::vector<Monster> monsterPool;
    std::vector<Monster> bestiary;
    
public:
    Game();
    ~Game();
    
    void start(const std::string& playerName);
    void mainMenu();
    void showBestiary();
    void startCombat();
    void showStats();
    void showItems();
    bool runCombat(Monster monster);
    
    int rollDamage(int hpMax);
};

#endif