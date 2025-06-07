#ifndef GAME_HPP
#define GAME_HPP

#include "Dungeon.h"
#include "Player.h"
#include "GameGUI.hpp"

class Game {
private:
    // Game objects members of the Game class
    GameGUI gui;
    Dungeon dungeon;
    Player player;

    // Game state management
    enum class GameState {
        StartScreen,
        RulesScreen,
        Playing,
        Victory,
        GameOver
    };
    GameState currentState;

    void processEvents();
    void update(sf::Keyboard::Key key);
    void render();

public:
    Game();
    void run();
};

#endif