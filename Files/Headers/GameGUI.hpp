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

    bool isWindowOpen() const;
    sf::Keyboard::Key getLastKeyPressed();

    void handleInput();
    void render();
    std::string vectorToString(const std::vector<std::string>& vec, const std::string& separator);
    void centerText(sf::Text& text, float y);


private:
    sf::RenderWindow window;
    sf::Font font;

    // Updated info
    std::string roomDescription, roomSound, roomSmell;
    int playerHP, playerStamina;
    std::string equippedWeapon;
    std::vector<std::string> inventory;
    std::vector<std::string> messages;

    // UI Elements
    sf::Text titleText;
    sf::Text descText;
    sf::Text statsText;
    sf::Text invText;
    sf::Text msgBox;

    sf::Keyboard::Key lastKey;
};

#endif
