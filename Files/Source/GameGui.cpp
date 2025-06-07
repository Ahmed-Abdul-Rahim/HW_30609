#include "../headers/GameGUI.hpp"
#include <sstream>
#include <algorithm>

GameGUI::GameGUI(int width, int height) : playerHP(0), playerStamina(0), lastKey(sf::Keyboard::Unknown),
                                        currentEnemySprite(nullptr) {
    window.create(sf::VideoMode(width, height), "Dungeon Escape - GUI Edition");

    if (!font.loadFromFile("../assets/LEMONMILK-Medium.ttf")) {
        throw std::runtime_error("Failed to load font!");
    }

    // Main Game Text Initialization 
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
    
    //   Text Initialization 
    menuTitleText.setFont(font);
    menuTitleText.setString("Dungeon Escape");
    menuTitleText.setCharacterSize(50);
    menuTitleText.setFillColor(sf::Color::White);
    sf::FloatRect titleBounds = menuTitleText.getLocalBounds();
    menuTitleText.setOrigin(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f);
    menuTitleText.setPosition(width / 2.f, 250.f);

    menuPromptText.setFont(font);
    menuPromptText.setString("Press Enter to Continue");
    menuPromptText.setCharacterSize(24);
    menuPromptText.setFillColor(sf::Color::Yellow);
    sf::FloatRect promptBounds = menuPromptText.getLocalBounds();
    menuPromptText.setOrigin(promptBounds.left + promptBounds.width / 2.f, promptBounds.top + promptBounds.height / 2.f);
    menuPromptText.setPosition(width / 2.f, 450.f);

    rulesTitleText.setFont(font);
    rulesTitleText.setString("Game Rules");
    rulesTitleText.setCharacterSize(40);
    rulesTitleText.setFillColor(sf::Color::White);
    sf::FloatRect rulesTitleBounds = rulesTitleText.getLocalBounds();
    rulesTitleText.setOrigin(rulesTitleBounds.left + rulesTitleBounds.width / 2.f, rulesTitleBounds.top + rulesTitleBounds.height / 2.f);
    rulesTitleText.setPosition(width / 2.f, 100.f);

    rulesBodyText.setFont(font);
    rulesBodyText.setString(
        "- Goal: Find and defeat the final boss, Bartholmew, to escape.\n\n"
        "- Movement: Use W, A, S, D keys to move between rooms.\n\n"
        "- Backtrack: Press B to return to the last room you visited.\n\n"
        "- Actions: Use number keys [1], [2] for choices in combat and traps.\n\n"
        "- Combat: Enter the sequence of WASD keys shown to attack.\n\n"
        "- Inventory: Press U to open the item menu, then a number to use an item.\n\n"
        "- Stamina: Every move costs stamina. Don't let it run out!"
    );
    rulesBodyText.setCharacterSize(20);
    rulesBodyText.setFillColor(sf::Color::Cyan);
    sf::FloatRect rulesBodyBounds = rulesBodyText.getLocalBounds();
    rulesBodyText.setOrigin(rulesBodyBounds.left + rulesBodyBounds.width / 2.f, rulesBodyBounds.top + rulesBodyBounds.height / 2.f);
    rulesBodyText.setPosition(width / 2.f, 300.f);


    gameOverText.setFont(font);
    gameOverText.setString("You Have Been Defeated");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    sf::FloatRect gameOverBounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(gameOverBounds.left + gameOverBounds.width / 2.f, gameOverBounds.top + gameOverBounds.height / 2.f);
    gameOverText.setPosition(width / 2.f, height / 2.f);

    victoryText.setFont(font);
    victoryText.setString("You have Escaped!\n\nCongratulations!");
    victoryText.setCharacterSize(50);
    victoryText.setFillColor(sf::Color::Green);
    sf::FloatRect victoryBounds = victoryText.getLocalBounds();
    victoryText.setOrigin(victoryBounds.left + victoryBounds.width / 2.f, victoryBounds.top + victoryBounds.height / 2.f);
    victoryText.setPosition(width / 2.f, height / 2.f - 50.f);
}

void GameGUI::drawStartScreen() {
    window.clear(sf::Color::Black);
    window.draw(menuTitleText);

    menuPromptText.setString("Press Enter to Start");
    sf::FloatRect promptBounds = menuPromptText.getLocalBounds();
    menuPromptText.setOrigin(promptBounds.left + promptBounds.width / 2.f, promptBounds.top + promptBounds.height / 2.f);
    menuPromptText.setPosition(window.getSize().x / 2.f, 350.f);
    window.draw(menuPromptText);

    window.display();
}

void GameGUI::drawRulesScreen() {
    window.clear(sf::Color::Black);
    window.draw(rulesTitleText);
    window.draw(rulesBodyText);

    menuPromptText.setString("Press Enter to Begin");
    sf::FloatRect promptBounds = menuPromptText.getLocalBounds();
    menuPromptText.setOrigin(promptBounds.left + promptBounds.width / 2.f, promptBounds.top + promptBounds.height / 2.f);
    menuPromptText.setPosition(window.getSize().x / 2.f, 500.f);
    window.draw(menuPromptText);
    
    window.display();
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
    std::sort(inventory.begin(), inventory.end());
}

void GameGUI::pushMessage(const std::string& msg) {
    messages.push_back(msg);
    if (messages.size() > 4) messages.erase(messages.begin());
}

void GameGUI::clearMessages() {
    messages.clear();
}

sf::Keyboard::Key GameGUI::getLastKeyPressed() {
    sf::Keyboard::Key key = lastKey;
    lastKey = sf::Keyboard::Unknown;
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

void GameGUI::setEnemySprite(sf::Sprite* enemySpr) {
    currentEnemySprite = enemySpr;
}

void GameGUI::clearEnemySprite() {
    currentEnemySprite = nullptr;
}

void GameGUI::render() {
    window.clear(sf::Color::Black);

    titleText.setString(" Room Info:");
    titleText.setPosition(20, 10);

    descText.setString(" Desc: " + roomDescription +
                       "\n Sound: " + roomSound +
                       "\n Smell: " + roomSmell);
    descText.setPosition(20, 50);

    std::stringstream ssStats;
    ssStats << " HP: " << playerHP
            << "    Stamina: " << playerStamina
            << "    Weapon: " << equippedWeapon;
    statsText.setString(ssStats.str());
    statsText.setPosition(20, window.getSize().y - 60);

    invText.setString(" Inventory:\n" + vectorToString(inventory, "\n"));
    invText.setPosition(window.getSize().x - 300, 20);

    msgBox.setString(" Messages:\n" + vectorToString(messages, "\n"));
    sf::FloatRect msgBounds = msgBox.getLocalBounds();
    msgBox.setOrigin(msgBounds.width / 2.f, 0);
    msgBox.setPosition(window.getSize().x / 2.f, 180);

    if (currentEnemySprite) {
        window.draw(*currentEnemySprite);
    }

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

void GameGUI::drawGameOverScreen() {
    window.clear(sf::Color::Black);
    window.draw(gameOverText);

    menuPromptText.setString("Press Escape to Exit");
    sf::FloatRect promptBounds = menuPromptText.getLocalBounds();
    menuPromptText.setOrigin(promptBounds.left + promptBounds.width / 2.f, promptBounds.top + promptBounds.height / 2.f);
    menuPromptText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f + 80.f);
    window.draw(menuPromptText);

    window.display();
}

void GameGUI::drawVictoryScreen() {
    window.clear(sf::Color::Black);
    window.draw(victoryText);

    menuPromptText.setString("Press Escape to Exit");
    sf::FloatRect promptBounds = menuPromptText.getLocalBounds();
    menuPromptText.setOrigin(promptBounds.left + promptBounds.width / 2.f, promptBounds.top + promptBounds.height / 2.f);
    menuPromptText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f + 100.f);
    window.draw(menuPromptText);

    window.display();
}

void GameGUI::close() {
    window.close();
}

