// In GameGUI.hpp

#ifndef GAME_GUI_HPP
#define GAME_GUI_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class GameGUI {
public:
    GameGUI(int width = 800, int height = 600);
    void run();


    void setRoomInfo(const std::string& description, const std::string& sound, const std::string& smell);
    void setPlayerStats(int hp, int stamina, const std::string& equippedWeapon);
    void setInventory(const std::vector<std::string>& items);
    void pushMessage(const std::string& msg);
    void clearMessages();
    void setEnemySprite(sf::Sprite* enemySpr);
    void clearEnemySprite();
    bool isWindowOpen() const;
    sf::Keyboard::Key getLastKeyPressed();
    sf::RenderWindow& getWindow(); 
    

    void handleInput();
    void render(); // main game screen
    
    void drawStartScreen();
    void drawRulesScreen();
    void drawGameOverScreen();
    void drawVictoryScreen(); 
    void close();
private:
    sf::RenderWindow window;
    sf::Font font;


    sf::Text titleText;
    sf::Text descText;
    sf::Text statsText;
    sf::Text invText;
    sf::Text msgBox;
    
    // --- ADD THESE NEW TEXT OBJECTS FOR MENUS ---
    sf::Text menuTitleText;
    sf::Text menuPromptText;
    sf::Text rulesTitleText;
    sf::Text rulesBodyText;
    sf::Text gameOverText;
    sf::Text victoryText;


    // Updated info
    std::string roomDescription, roomSound, roomSmell;
    int playerHP, playerStamina;
    std::string equippedWeapon;
    std::vector<std::string> inventory;
    std::vector<std::string> messages;
    sf::Sprite* currentEnemySprite;

    sf::Keyboard::Key lastKey;
    std::string vectorToString(const std::vector<std::string>& vec, const std::string& separator);
};

#endif