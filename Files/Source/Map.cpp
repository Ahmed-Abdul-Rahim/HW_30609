#include "../Headers/Dungeon.h"
#include <map>

// Function to Display Map
void displayMap(Room* currentRoom) {

    string map[11] = {
        "[Room 1]    [Room 6]  ===  [Room 7]   ===  [Room 9] ",
        "  ||           ||              ||             |",
        "  ||           ||              ||             |",
        "[Start] ===  [Room 5]       [Room 8]       [Boss]  ",
        "  ||                            |       ",
        "  ||         [Room 4]           |              ",
        "  ||            ||              |         ",
        "[Room 2] === [Room 3] === [Secret Room] ",
    };
 
    cout << BLUE << "\n--- Dungeon Map ---\n" << RESET;
    for (const string& line : map) {
        cout << line << endl;
    }
    cout << BLUE << "-------------------\n" << RESET;
    cout << BLUE << "\nYou are currently in: " << RED << currentRoom->description << RESET << endl;
}

