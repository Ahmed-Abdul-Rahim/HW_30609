#include "../Headers/Dungeon.h"
#include "../Source/Map.cpp"
#include "../Source/rules.cpp"
#include <ctime>
#include <thread>
#include <chrono>

int main() {
    std::srand(std::time(0));
    Player player;
    Dungeon dungeon;
    GameGUI gui(1000, 800);
    dungeon.setGUI(&gui);
    rules();

    gui.pushMessage("Game started! Use keys to interact.");
    gui.setRoomInfo(dungeon.currentRoom->description, dungeon.currentRoom->sound, dungeon.currentRoom->smell);
    gui.setPlayerStats(player.hp, player.stamina, player.equippedWeapon);
    gui.setInventory(player.inventory);

    while (gui.isWindowOpen() && player.isAlive() && player.stamina > 0 &&
           dungeon.bossRoom->enemy && dungeon.bossRoom->enemy->isAlive()) {

        gui.handleInput();
        sf::Keyboard::Key key = gui.getLastKeyPressed();

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
            case sf::Keyboard::I:
                gui.pushMessage(" Inventory:");
                for (const std::string& item : player.inventory)
                    gui.pushMessage("- " + item);
                break;
            case sf::Keyboard::H:
                gui.pushMessage(" Status:");
                gui.pushMessage("HP: " + std::to_string(player.hp) +
                                " | Stamina: " + std::to_string(player.stamina) +
                                " | Weapon: " + player.equippedWeapon);
                break;
            case sf::Keyboard::M:
                gui.pushMessage(" Map hint:");
                displayMap(dungeon.currentRoom.get());
                break;
            case sf::Keyboard::U:
                dungeon.useItem(player);
                break;
            case sf::Keyboard::Escape:
                gui.pushMessage(" Exiting game...");
                std::this_thread::sleep_for(std::chrono::milliseconds(800));
                return 0;
            default:
                break;
        }


        // Refresh GUI
        gui.setRoomInfo(dungeon.currentRoom->description, dungeon.currentRoom->sound, dungeon.currentRoom->smell);
        gui.setPlayerStats(player.hp, player.stamina, player.equippedWeapon);
        gui.setInventory(player.inventory);
        gui.render();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if (player.isAlive() && dungeon.bossRoom->enemy && !dungeon.bossRoom->enemy->isAlive()) {
        dungeon.displayVictoryScreen();
        gui.pushMessage(" YOU ESCAPED THE DUNGEON ALIVE!");
        gui.pushMessage(" CONGRATULATIONS, YOU WIN!");
        while (gui.isWindowOpen()) {
            gui.handleInput();
            gui.render();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    return 0;
}
