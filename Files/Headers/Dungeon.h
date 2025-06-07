#ifndef DUNGEON_H
#define DUNGEON_H

#include "Room.h"
#include "CustomStack.h"
#include "CustomQueue.h"
#include "GameGUI.hpp"
#include "Entity.h"
#include "Player.h"
#include <memory>
#include <map>          
#include <functional>   

class Dungeon {
    private:
    GameGUI* gui = nullptr;

    public:
    std::shared_ptr<Room> startRoom;
    std::shared_ptr<Room> currentRoom;
    CustomStack<std::shared_ptr<Room>> backtrackStack;
    CustomQueue<std::shared_ptr<Enemy>> enemyQueue;
    std::shared_ptr<Room> bossRoom;
    std::map<std::string, std::function<void(Player&)>> itemEffects;

    Dungeon();
    void enterRoom(Player& player, std::shared_ptr<Room> room);
    void backtrack(Player& player);
    void combat(Player& player, std::shared_ptr<Enemy> enemy);
    void useItem(Player& player);
    void handleTraps(Player& player, std::shared_ptr<Room> room);
    void displayVictoryScreen();
    void setGUI(GameGUI* gameGUI) { gui = gameGUI; }
};

#endif