#include "../Headers/Game.hpp"
#include <thread>
#include <chrono>

Game::Game() : gui(1000, 800), currentState(GameState::StartScreen) {
    // The constructor handles all initial setup
    dungeon.setGUI(&gui);
}

void Game::run() {
    while (gui.isWindowOpen()) {
        processEvents();
        // The main loop 
    }
}

void Game::processEvents() {
    gui.handleInput();
    sf::Keyboard::Key key = gui.getLastKeyPressed();

    if (key == sf::Keyboard::Escape) {
       gui.close();
    }
    
    update(key);
    render();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Game::update(sf::Keyboard::Key key) {
    switch (currentState) {
        case GameState::StartScreen:
            if (key == sf::Keyboard::Enter) {
                currentState = GameState::RulesScreen;
            }
            break;

        case GameState::RulesScreen:
            if (key == sf::Keyboard::Enter) {
                currentState = GameState::Playing;
                gui.pushMessage("Game started! Use keys to interact.");
                gui.setRoomInfo(dungeon.currentRoom->description, dungeon.currentRoom->sound, dungeon.currentRoom->smell);
            }
            break;

        case GameState::Playing:
            if (!player.isAlive() || player.stamina <= 0) {
                gui.pushMessage("You have been defeated! Game Over.");
                currentState = GameState::GameOver;
                break;
            }

            if (dungeon.bossRoom->enemy && !dungeon.bossRoom->enemy->isAlive()) {
                dungeon.displayVictoryScreen();
                currentState = GameState::Victory;
                break;
            }
            
            switch (key) {
                case sf::Keyboard::W:
                    dungeon.enterRoom(player, dungeon.currentRoom->north);
                    player.stamina--;
                    break;
                case sf::Keyboard::S:
                    dungeon.enterRoom(player, dungeon.currentRoom->south);
                    player.stamina--;
                    break;
                case sf::Keyboard::D:
                    dungeon.enterRoom(player, dungeon.currentRoom->east);
                    player.stamina--;
                    break;
                case sf::Keyboard::A:
                    dungeon.enterRoom(player, dungeon.currentRoom->west);
                    player.stamina--;
                    break;
                case sf::Keyboard::B:
                    dungeon.backtrack(player);
                    break;
                case sf::Keyboard::U:
                    dungeon.useItem(player);
                    break;
                default:
                    break;
            }
            
            if (dungeon.currentRoom->enemy && dungeon.currentRoom->enemy->isAlive()) {
                dungeon.currentRoom->enemy->update();
            } else if (!dungeon.enemyQueue.isEmpty()) {
                dungeon.enemyQueue.peek()->update();
            }
            
            gui.setPlayerStats(player.hp, player.stamina, player.equippedWeapon);
            gui.setInventory(player.inventory);
            break;

        case GameState::Victory:
        case GameState::GameOver:
    
            break;
    }
}

void Game::render() {
    switch (currentState) {
        case GameState::StartScreen:
            gui.drawStartScreen();
            break;
        case GameState::RulesScreen:
            gui.drawRulesScreen();
            break;
        case GameState::Playing:
            gui.render();
            break;
        case GameState::Victory:
            gui.drawVictoryScreen();
            break;
        case GameState::GameOver:
            gui.drawGameOverScreen();
            break;
    }
}