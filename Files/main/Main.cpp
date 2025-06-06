// #include "../Headers/Player.h"
// #include "../Headers/Enemy.h"
// #include "../Headers/Room.h"
#include "../Headers/Dungeon.h"
#include "../Source/Map.cpp"
#include "../Source/rules.cpp"
#include <ctime>

//void rules();
// void displayMap(Room* currentRoom);


int main(){
std::srand(std::time(0));
Player player;
Dungeon dungeon;
int choice;
rules();


while (player.isAlive() && player.stamina > 0 && dungeon.bossRoom->enemy->isAlive()) {
        cout << "\n[1] Move North  [2] Move South  [3] Move East  [4] Move West  "
             << "[5] View Inventory  \n[6] Check Stats " << VIOLET << " [7] USE Map IF STUCK PLS " << RESET
             << "[8] Use Item  [9] Exit\n";
        cin >> choice;
    
        if (choice == 9) break;  
        else if (choice == 6) player.displayStats();
        else if (choice == 5) player.viewInventory();
        else if (choice == 7) displayMap(dungeon.currentRoom);
        else if (choice == 8) dungeon.useItem(player);
        else dungeon.enterRoom(player, (choice == 1) ? dungeon.currentRoom->north :
                                        (choice == 2) ? dungeon.currentRoom->south :
                                        (choice == 3) ? dungeon.currentRoom->east :
                                        (choice == 4) ? dungeon.currentRoom->west :
                                        nullptr);

          player.stamina--;//YOU HAVE LIMITED NUMBER OF MOVES!!!!!!
    }
    if (player.isAlive() && dungeon.bossRoom->enemy && !dungeon.bossRoom->enemy->isAlive()) {
     dungeon.displayVictoryScreen();
 }
 
        
}