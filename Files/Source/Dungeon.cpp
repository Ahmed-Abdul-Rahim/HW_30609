#include "../Headers/Dungeon.h"
#include <cstdlib>
#include <algorithm>
#include <thread>
#include <chrono>


Dungeon::Dungeon() {
    startRoom = std::make_shared<Room>("Starting Room", "You hear distant dripping water.", "The air smells damp.");
    auto room1 = std::make_shared<Room>("Room 1 (Find Key)", "Crackling fire echoes.", "You smell burnt wood.");
    auto room2 = std::make_shared<Room>("Room 2 (Water Challenge)", "Faint splashing sounds.", "A strong scent of mold.");
    auto room3 = std::make_shared<Room>("Room 3 Mini-Boss 1 (Tyrion the Imps layer) Room 3 ", "Growls echo around.", "The room reeks of sweat.");
    auto room4 = std::make_shared<Room>("Room 4 (Find Key 2) Room 4 ", "Silence fills the air.", "A faint scent of parchment.");
    auto room5 = std::make_shared<Room>("Room 5", "A distant humming sound.", "You catch a whiff of something sweet.");
    auto room6 = std::make_shared<Room>("Room 6 (Vines Challenge)", "Leaves rustle.", "A fresh earthy scent.");
    auto room7 = std::make_shared<Room>("Room 7 Home of The orcs", "A deep growl echoes. Room 7 ", "The air stinks of blood.");
    auto room8 = std::make_shared<Room>("Room 8 (Find Secret Room Key)", "Soft whispers surround you.", "The air carries an old, musty smell.");
    auto room9 = std::make_shared<Room>("Boss key ", "A deep rumbling fills the chamber. Room 9", "You smell burning embers.");
    bossRoom = std::make_shared<Room>("Final Boss Room (Bartholmew)", "A deep rumbling fills the chamber.", "You smell burning embers.");
    auto secret_room = std::make_shared<Room>("Secret Room", "secrets lie here.", "trolls feet");

    // Connecting Rooms
    startRoom->north = room1;
    startRoom->south = room2;
    startRoom->east = room5;
    room1->south = startRoom;
    room2->north = startRoom;
    room2->east = room3;
    room3->west = room2;
    room3->east = secret_room;
    room3->north = room4;
    room4->south = room3;
    room5->west = startRoom;
    room5->north = room6;
    room6->south = room5;
    room6->east = room7;
    room7->west = room6;
    room7->south = room8;
    room7->east = room9;
    room8->north = room7;
    room9->west = room7;
    room9->south = bossRoom;
    secret_room->north = room8;
    secret_room->west = room3;

    // Items
    room1->item = "Shadowfang Key ....maybe room 5";
    room2->item = "Potion of Copeium...(100% Health)";
    room4->item = "Kings Sigil...room6";
    room6->item = " you thot";
    room7->item = "Coin ";
    room8->item = "Forbideen Secret Key...theres a secret roommmm";
    room9->item = "THE ALPHA BOSS KEY...opens the Boss Room...duh";
    secret_room->item = "OmegaBlade & Sigma Armor";

    // Enemies
    room3->enemy = std::make_shared<Enemy>("Tyrian the Imp", 50, 5, 10);
    room7->enemy = std::make_shared<Enemy>("Orcus the Bloodforged", 100, 10, 15);
    bossRoom->enemy = std::make_shared<Enemy>("Bartholmew", 300, 20, 55);

    // Traps & Challenges
    room1->fireTrap = true;
    room2->waterChallenge = true;
    room6->vineTrap = true;

    currentRoom = startRoom;
}


void Dungeon::combat(Player& player, std::shared_ptr<Enemy> enemy) {
    std::string intro = "\n BATTLE START: " + enemy->name + " appears!";
    cout << RED << intro << RESET << endl;
    if (gui) gui->pushMessage(intro);

    cout << "\n[1] Fight  [2] Run\n> ";
    if (gui) gui->pushMessage("[1] Fight  [2] Run");
    gui->render();

    // Wait for 1 or 2 key input
    sf::Keyboard::Key choiceKey;
    while (true) {
        gui->handleInput();
        choiceKey = gui->getLastKeyPressed();
        if (choiceKey == sf::Keyboard::Num1 || choiceKey == sf::Keyboard::Num2)
            break;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    if (choiceKey == sf::Keyboard::Num2) {
        string runMsg = "You attempt to run...";
        cout << YELLOW << runMsg << RESET << endl;
        if (gui) gui->pushMessage(runMsg);

        int escapeChance = rand() % 100;
        if (escapeChance < 70) {
            string escape = "🏃 You successfully ran away!";
            cout << GREEN << escape << RESET << endl;
            if (gui) gui->pushMessage(escape);
            gui->render();
            return;
        } else {
            int failDamage = rand() % 10 + 10;
            player.takeDamage(failDamage);
            if (gui) gui->setPlayerStats(player.hp, player.stamina, player.equippedWeapon);
            string fail = " You failed to escape and took " + std::to_string(failDamage) + " damage!";
            cout << RED << fail << RESET << endl;
            if (gui) gui->pushMessage(fail);
        }
    }

    while (player.isAlive() && enemy->isAlive()) {
        cout << YELLOW << "Press A/S/D to attack: (A=slash, S=stab, D=strike)\n> " << RESET;
        if (gui) gui->pushMessage("Press A/S/D: slash, stab, or strike");
        gui->render();

        // Wait for attack key input
        sf::Keyboard::Key atkKey;
        while (true) {
            gui->handleInput();
            atkKey = gui->getLastKeyPressed();
            if (atkKey == sf::Keyboard::A || atkKey == sf::Keyboard::S || atkKey == sf::Keyboard::D)
                break;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        std::string attackInput;
        if (atkKey == sf::Keyboard::A) attackInput = "slash";
        else if (atkKey == sf::Keyboard::S) attackInput = "stab";
        else attackInput = "strike";

        int damage = rand() % 40 + 5;
        enemy->takeDamage(damage);
        string dmgMsg = "You " + attackInput + " and deal " + std::to_string(damage) + " damage!";
        cout << GREEN << dmgMsg << RESET << endl;
        if (gui) gui->pushMessage(dmgMsg);

        string enemyHP = enemy->name + " HP: " + std::to_string(enemy->hp);
        cout << RED << enemyHP << RESET << endl;
        if (gui) gui->pushMessage(enemyHP);

        if (enemy->isAlive()) {
            enemy->attack(player);
            if (gui) gui->setPlayerStats(player.hp, player.stamina, player.equippedWeapon);
        }

        gui->render();
    }

    string result = player.isAlive()
        ? " You defeated " + enemy->name + "!"
        : " You have been defeated by " + enemy->name + "!";
    cout << (player.isAlive() ? GREEN : RED) << result << RESET << endl;
    if (gui) {
        gui->pushMessage(result);
        gui->render();
    }
}


void Dungeon::enterRoom(Player& player, std::shared_ptr<Room> room) {
    if (!room) {
        cout << RED << "You can't go that way!" << RESET << endl;
        if (gui) gui->pushMessage(" You can't go that way!");
        return;
    }

    currentRoom = room;

    // Key Restrictions
    if (room == startRoom->east && !player.hasItem("Shadowfang Key ....maybe room 5")) {
        cout << RED << "The door to Room 5 is locked. You need the Shadowfang Key to enter!" << RESET << endl;
        if (gui) gui->pushMessage(" Room 5 is locked! You need the Shadowfang Key.");
        return;
    }
    if (room == startRoom->south->east->east && !player.hasItem("Forbideen Secret Key...theres a secret roommmm")) {
        cout << RED << "The entrance to the Secret Room is sealed by magic. You need the Forbidden Secret Key!" << RESET << endl;
        if (gui) gui->pushMessage(" A magical barrier blocks you. You need the Forbidden Secret Key!");
        return;
    }
    if (room == startRoom->east->north && !player.hasItem("Kings Sigil...room6")) {
        cout << RED << "The gate to Room 6 is blocked. Only those holding the King's Sigil may enter!" << RESET << endl;
        if (gui) gui->pushMessage(" You need the King's Sigil to enter Room 6!");
        return;
    }
    if (room == startRoom->east->north->east->east->south && !player.hasItem("THE ALPHA BOSS KEY...opens the Boss Room...duh")) {
        cout << RED << "The Boss Room remains shut. You must wield the ALPHA BOSS KEY to enter!" << RESET << endl;
        if (gui) gui->pushMessage(" Boss Room is locked! Bring the ALPHA BOSS KEY.");
        return;
    }

    // Room description
    cout << BLUE << "\n[ " << room->description << " ]" << RESET << endl;
    cout << YELLOW << "Sound: " << room->sound << "\nSmell: " << room->smell << RESET << endl;

    if (gui) {
        gui->setRoomInfo(room->description, room->sound, room->smell);
        gui->setPlayerStats(player.hp, player.stamina, player.equippedWeapon);
        gui->setInventory(player.inventory);
        gui->pushMessage(" Entered a new room.");
    }

    // Traps
    if (room->fireTrap || room->vineTrap || room->waterChallenge) {
        handleTraps(player, room);
    }

    // Combat
    if (room->enemy && room->enemy->isAlive()) {
        cout << RED << "An enemy appears: " << room->enemy->name << "!" << RESET << endl;
        if (gui) gui->pushMessage(" Enemy appears: " + room->enemy->name);
        enemyQueue.enqueue(room->enemy);
        combat(player, room->enemy);
    }

    // Item Pickup
    if (!room->item.empty()) {
        cout << GREEN << "You found an item: " << room->item << RESET << endl;
        if (gui) {
            gui->pushMessage(" You found an item: " + room->item);
            gui->pushMessage("Pick it up? (Y = Yes / N = No)");
            gui->render();
        }

        sf::Keyboard::Key pickKey;
        while (true) {
            gui->handleInput();
            pickKey = gui->getLastKeyPressed();
            if (pickKey == sf::Keyboard::Y || pickKey == sf::Keyboard::N)
                break;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        if (pickKey == sf::Keyboard::Y) {
            player.addItem(room->item);
            cout << GREEN << room->item << " has been added to your inventory!" << RESET << endl;
            if (gui) gui->pushMessage(" You picked up: " + room->item);
            room->item = "";
        } else {
            cout << RED << "You left the " << room->item << " behind....I hope it wasn't important..." << RESET << endl;
            if (gui) gui->pushMessage(" You ignored: " + room->item);
        }
    }
}


void Dungeon::useItem(Player& player) {
    if (player.inventory.empty()) {
        cout << RED << "Your inventory is empty! Nothing to use." << RESET << endl;
        if (gui) gui->pushMessage("Inventory empty! Nothing to use.");
        return;
    }

    // Show inventory
    string invMsg = "Inventory: ";
    for (const string& item : player.inventory) {
        invMsg += "[" + item + "] ";
    }

    cout << YELLOW << invMsg << RESET << endl;
    if (gui) gui->pushMessage(invMsg);

    string prompt = "Press: P = Use Potion, A = Use Armor, C = Cancel";
    cout << ORANGE << prompt << "\n> " << RESET;
    if (gui) gui->pushMessage(prompt);
    gui->render();

    sf::Keyboard::Key key;
    while (true) {
        gui->handleInput();
        key = gui->getLastKeyPressed();
        if (key == sf::Keyboard::P || key == sf::Keyboard::A || key == sf::Keyboard::C)
            break;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    // Cancel
    if (key == sf::Keyboard::C) {
        string cancelMsg = "You decided not to use any item.";
        cout << RED << cancelMsg << RESET << endl;
        if (gui) gui->pushMessage(cancelMsg);
        return;
    }

    // === Potion ===
    if (key == sf::Keyboard::P && player.hasItem("Potion of Copeium...(100% Health)")) {
        player.hp = 200;
        string msg = " You drank the Potion of Copeium! Your health is fully restored.";
        cout << GREEN << msg << RESET << endl;
        if (gui) gui->pushMessage(msg);

        auto it = std::find(player.inventory.begin(), player.inventory.end(), "Potion of Copeium...(100% Health)");
        if (it != player.inventory.end()) player.inventory.erase(it);
    }
    // === Armor ===
    else if (key == sf::Keyboard::A && player.hasItem("OmegaBlade & Sigma Armor")) {
        player.hp += 350;
        player.stamina += 50;
        string msg = " You equipped the Sigma Armor! Health and stamina increased.";
        cout << YELLOW << msg << RESET << endl;
        if (gui) gui->pushMessage(msg);

        auto it = std::find(player.inventory.begin(), player.inventory.end(), "OmegaBlade & Sigma Armor");
        if (it != player.inventory.end()) player.inventory.erase(it);
    }
    // === Invalid
    else {
        string failMsg = " You can't use that item or it's not in your inventory!";
        cout << RED << failMsg << RESET << endl;
        if (gui) gui->pushMessage(failMsg);
    }

    if (gui) {
        gui->setPlayerStats(player.hp, player.stamina, player.equippedWeapon);
        gui->setInventory(player.inventory);
        gui->render();
    }
}


void Dungeon::handleTraps(Player& player, std::shared_ptr<Room> room) {
    // === Fire Trap ===
    if (room->fireTrap && room == startRoom->north) {
        string intro = " A deadly fire trap is in this room! What will you do?";
        cout << RED << intro << RESET << endl;
        if (gui) gui->pushMessage(intro);

        gui->pushMessage("[1] Try to disarm (70%)");
        gui->pushMessage("[2] Run through (30 dmg)");
        gui->render();

        sf::Keyboard::Key key;
        while (true) {
            gui->handleInput();
            key = gui->getLastKeyPressed();
            if (key == sf::Keyboard::Num1 || key == sf::Keyboard::Num2) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        if (key == sf::Keyboard::Num1) {
            int success = rand() % 100;
            if (success < 70) {
                string msg = " You successfully disarmed the fire trap!";
                cout << GREEN << msg << RESET << endl;
                if (gui) gui->pushMessage(msg);
            } else {
                string msg = " You failed and took 20 damage!";
                cout << RED << msg << RESET << endl;
                player.takeDamage(20);
                if (gui) gui->pushMessage(msg);
            }
        } else {
            string msg = " You sprint through the flames and take 30 damage!";
            cout << RED << msg << RESET << endl;
            player.takeDamage(30);
            if (gui) gui->pushMessage(msg);
        }

        room->fireTrap = false;
    }

    // === Water Challenge ===
    if (room->waterChallenge && room == startRoom->south) {
        string intro = " The room is flooded! What will you do?";
        cout << BLUE << intro << RESET << endl;
        if (gui) gui->pushMessage(intro);

        gui->pushMessage("[1] Swim (20 stamina, 50% success)");
        gui->pushMessage("[2] Detour (10 HP)");
        gui->render();

        sf::Keyboard::Key key;
        while (true) {
            gui->handleInput();
            key = gui->getLastKeyPressed();
            if (key == sf::Keyboard::Num1 || key == sf::Keyboard::Num2) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        if (key == sf::Keyboard::Num1) {
            int success = rand() % 100;
            if (success < 50) {
                string msg = " You swim through safely!";
                cout << GREEN << msg << RESET << endl;
                player.stamina -= 20;
                if (gui) gui->pushMessage(msg);
            } else {
                string msg = " You struggle and take 15 damage!";
                cout << RED << msg << RESET << endl;
                player.takeDamage(15);
                if (gui) gui->pushMessage(msg);
            }
        } else {
            string msg = " You find another way but take 10 damage!";
            cout << YELLOW << msg << RESET << endl;
            player.takeDamage(10);
            if (gui) gui->pushMessage(msg);
        }

        room->waterChallenge = false;
    }

    // === Vine Trap ===
    if (room->vineTrap && room == startRoom->east->north) {
        string intro = " Vines block your path!";
        cout << GREEN << intro << RESET << endl;
        if (gui) gui->pushMessage(intro);

        gui->pushMessage("[1] Cut through with weapon");
        gui->pushMessage("[2] Push through (15 dmg)");
        gui->render();

        sf::Keyboard::Key key;
        while (true) {
            gui->handleInput();
            key = gui->getLastKeyPressed();
            if (key == sf::Keyboard::Num1 || key == sf::Keyboard::Num2) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        if (key == sf::Keyboard::Num1 && player.hasItem("OmegaBlade & Sigma Armor")) {
            string msg = " You slice through the vines effortlessly!";
            cout << GREEN << msg << RESET << endl;
            if (gui) gui->pushMessage(msg);
        } else if (key == sf::Keyboard::Num1) {
            string msg = " You have no weapon to cut the vines!";
            cout << RED << msg << RESET << endl;
            if (gui) gui->pushMessage(msg);
            gui->render();
            return;
        } else {
            string msg = " You push through and take 15 damage!";
            cout << RED << msg << RESET << endl;
            player.takeDamage(15);
            if (gui) gui->pushMessage(msg);
        }

        room->vineTrap = false;
    }

    // Final stat update
    if (gui) {
        gui->setPlayerStats(player.hp, player.stamina, player.equippedWeapon);
        gui->render();
    }
}


void Dungeon::displayVictoryScreen() {
    // Terminal output (unchanged)
    cout << "\033[1;33m🔥 YOU HAVE DEFEATED BARTHOLMEW, THE FINAL BOSS! 🔥\033[0m\n";
    cout << "\033[1;36m🏆 YOU ESCAPED THE DUNGEON ALIVE! 🏆\033[0m\n";
    cout << "\033[1;32m🎉 CONGRATULATIONS, YOU WIN! 🎉\033[0m\n\n\n";

    cout << "\033[1;31m██╗   ██╗██╗ ██████╗████████╗ ██████╗ ██████╗ ██╗   ██╗\033[0m\n";
    cout << "\033[1;33m██║   ██║██║██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗╚██╗ ██╔╝\033[0m\n";
    cout << "\033[1;32m██║   ██║██║██║        ██║   ██║   ██║██████╔╝ ╚████╔╝ \033[0m\n";
    cout << "\033[1;36m╚██╗ ██╔╝██║██║        ██║   ██║   ██║██╔══██╗  ╚██╔╝  \033[0m\n";
    cout << "\033[1;34m ╚████╔╝ ██║╚██████╗   ██║   ╚██████╔╝██║  ██║   ██║   \033[0m\n";
    cout << "\033[1;35m  ╚═══╝  ╚═╝ ╚═════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝   ╚═╝   \033[0m\n\n";

    cout << "\033[1;33m💀 NO LONGER A PRISONER OF THE DUNGEON! 💀\033[0m\n";
    cout << "\033[1;35m🌟 LEGENDS WILL TELL YOUR TALE FOR CENTURIES! 🌟\033[0m\n\n";

    // GUI output
    if (gui) {
        gui->clearMessages();
        gui->pushMessage("🔥 YOU DEFEATED BARTHOLMEW!");
        gui->pushMessage("🏆 YOU ESCAPED THE DUNGEON ALIVE!");
        gui->pushMessage("🎉 CONGRATULATIONS, YOU WIN!");
        gui->pushMessage("💀 NO LONGER A PRISONER!");
        gui->pushMessage("🌟 LEGENDS WILL TELL YOUR TALE!");
        gui->render();
    }
}









