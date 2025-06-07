 #ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>
#include "Entity.h"

using namespace std;
#define RED     "\033[1;31m"
#define ORANGE  "\033[1;38;5;208m"  
#define YELLOW  "\033[1;33m"
#define GREEN   "\033[1;32m"
#define BLUE    "\033[1;34m"
#define INDIGO  "\033[1;35m"
#define VIOLET  "\033[1;37m"  
#define RESET   "\033[0m"


class Player : public Entity {
public:
    int stamina;
    std::vector<std::string> inventory;
    std::string equippedWeapon;

    Player();

    void restoreHealth(int amount);
    void addItem(std::string item);
    bool hasItem(std::string item);
    void displayStats();
    void viewInventory();
    
    void attack(Entity& target) override;
    void update() override;
};

#endif