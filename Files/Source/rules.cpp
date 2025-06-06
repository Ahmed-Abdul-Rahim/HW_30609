#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[1;33m"
#define ORANGE  "\033[1;38;5;208m"  
#define RESET "\033[0m"

#include <iostream>
using namespace std;
void rules() {
    /*
    Rules for the game that will appear at the start so players know the goal
    */
    cout << GREEN << "\nThis is a text-based game, type your answers into the terminal.\n\n";
    
    cout << GREEN << "Type number on to the move u want to take or action you want to perfrom.\n"<< RESET;
    cout << GREEN << "e.g., 'n' for 'north' or '1'.\n\n"<< RESET;
    
    cout << GREEN << "The goal is to defeat the Master Boss in the Boss Room.\n\n"<< RESET;
    
    cout << GREEN << "There are required items to gain access to the Boss Room.\n"<< RESET;
    cout << GREEN << "You should have the Boss room Key to defeat the Boss!\n"<< RESET;
    cout << GREEN << "...but the armor won't be a bad choice to have either.\n\n"<< RESET;
    cout << ORANGE << "You have a maximum of 100 moves and some traps decrease your stamina so be weary.\n\n"<< RESET;
}