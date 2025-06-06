    #ifndef PLAYER_H
    #define PLAYER_H

    #include <iostream>
    #include <vector>
    using namespace std;
    #define RED     "\033[1;31m"
    #define ORANGE  "\033[1;38;5;208m"  // Bright Orange
    #define YELLOW  "\033[1;33m"
    #define GREEN   "\033[1;32m"
    #define BLUE    "\033[1;34m"
    #define INDIGO  "\033[1;35m"
    #define VIOLET  "\033[1;37m"  // Soft Purple
    #define RESET   "\033[0m"


    class Player {
    public:
        int hp, stamina;
        vector<string> inventory;
        string equippedWeapon;

        Player();
        void takeDamage(int dmg);
        void restoreHealth(int amount);
        void addItem(string item);
        bool hasItem(string item);
        void displayStats();
        void viewInventory();
        bool isAlive();
    };


    #endif
