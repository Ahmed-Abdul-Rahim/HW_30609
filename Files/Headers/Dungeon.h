#ifndef DUNGEON_H
#define DUNGEON_H

#include "Room.h"
#include "CustomStack.h"
#include "CustomQueue.h"
#include "GameGUI.hpp"
#include <memory>

class Dungeon {
    private:
    GameGUI* gui = nullptr;

    public:
    std::shared_ptr<Room> startRoom;
    std::shared_ptr<Room> currentRoom;
    CustomStack<std::shared_ptr<Room>> backtrackStack;
    CustomQueue<std::shared_ptr<Enemy>> enemyQueue;
    std::shared_ptr<Room> bossRoom;

    Dungeon();
    void enterRoom(Player& player, std::shared_ptr<Room> room);
    void combat(Player& player, std::shared_ptr<Enemy> enemy);
    void useItem(Player& player);
    void handleTraps(Player& player, std::shared_ptr<Room> room);
    void displayVictoryScreen();
    void setGUI(GameGUI* gameGUI) { gui = gameGUI; }
};

#endif
