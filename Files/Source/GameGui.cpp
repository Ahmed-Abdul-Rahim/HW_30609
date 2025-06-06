#include "../headers/GameGUI.hpp"
#include <sstream>

GameGUI::GameGUI(int width, int height) : playerHP(0), playerStamina(0), lastKey(sf::Keyboard::Unknown) {
    window.create(sf::VideoMode(width, height), "Dungeon Escape - GUI Edition");

    if (!font.loadFromFile("../assets/LEMONMILK-Medium.ttf")) {
        throw std::runtime_error("Failed to load font!");
    }

    titleText.setFont(font);
    titleText.setCharacterSize(28);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(20, 10);

    descText.setFont(font);
    descText.setCharacterSize(18);
    descText.setFillColor(sf::Color::Cyan);
    descText.setPosition(20, 60);

    statsText.setFont(font);
    statsText.setCharacterSize(18);
    statsText.setFillColor(sf::Color::Green);
    statsText.setPosition(20, 140);

    invText.setFont(font);
    invText.setCharacterSize(18);
    invText.setFillColor(sf::Color::Yellow);
    invText.setPosition(20, 180);

    msgBox.setFont(font);
    msgBox.setCharacterSize(18);
    msgBox.setFillColor(sf::Color::White);
    msgBox.setPosition(20, 300);
}

bool GameGUI::isWindowOpen() const {
    return window.isOpen();
}

void GameGUI::setRoomInfo(const std::string& desc, const std::string& sound, const std::string& smell) {
    roomDescription = desc;
    roomSound = sound;
    roomSmell = smell;
}

void GameGUI::setPlayerStats(int hp, int stamina, const std::string& equippedWeapon) {
    playerHP = hp;
    playerStamina = stamina;
    this->equippedWeapon = equippedWeapon;
}

void GameGUI::setInventory(const std::vector<std::string>& items) {
    inventory = items;
}

void GameGUI::pushMessage(const std::string& msg) {
    messages.push_back(msg);
    if (messages.size() > 4) messages.erase(messages.begin()); // Keep last 4
}

void GameGUI::clearMessages() {
    messages.clear();
}

sf::Keyboard::Key GameGUI::getLastKeyPressed() {
    sf::Keyboard::Key key = lastKey;
    lastKey = sf::Keyboard::Unknown;  // reset
    return key;
}

void GameGUI::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed) {
            lastKey = event.key.code;
        }
    }
}

std::string GameGUI::vectorToString(const std::vector<std::string>& vec, const std::string& separator) {
    std::stringstream ss;
    for (const auto& item : vec) {
        ss << "- " << item << separator;
    }
    return ss.str();
}

void GameGUI::centerText(sf::Text& text, float y) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.f, 0);
    text.setPosition(window.getSize().x / 2.f, y);
}

void GameGUI::render() {
    window.clear(sf::Color::Black);

    // --- Room Info (Top Left) ---
    titleText.setString(" Room Info:");
    titleText.setPosition(20, 10);

    descText.setString(" Desc: " + roomDescription + 
                       "\n Sound: " + roomSound + 
                       "\n Smell: " + roomSmell);
    descText.setPosition(20, 50);

    // --- Player Stats (Bottom Left) ---
    std::stringstream ssStats;
    ssStats << " HP: " << playerHP 
            << "    Stamina: " << playerStamina 
            << "    Weapon: " << equippedWeapon;
    statsText.setString(ssStats.str());
    statsText.setPosition(20, window.getSize().y - 60);

    // --- Inventory (Top Right) ---
    invText.setString(" Inventory:\n" + vectorToString(inventory, "\n"));
    invText.setPosition(window.getSize().x - 300, 20); // top-right spacing

    // --- Messages (Centered Top-Middle-ish) ---
    msgBox.setString(" Messages:\n" + vectorToString(messages, "\n"));
    sf::FloatRect msgBounds = msgBox.getLocalBounds();
    msgBox.setOrigin(msgBounds.width / 2.f, 0);  // center horizontally
    msgBox.setPosition(window.getSize().x / 2.f, 180); // slightly below top-middle

    // Draw all text
    window.draw(titleText);
    window.draw(descText);
    window.draw(statsText);
    window.draw(invText);
    window.draw(msgBox);

    window.display();
}

void GameGUI::run() {
    while (window.isOpen()) {
        handleInput();
        render();
    }
}
