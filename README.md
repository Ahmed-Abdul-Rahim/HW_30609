# C++ SFML Dungeon Crawler

<p align="center">
  <img src="https://via.placeholder.com/600x300.png/000000/FFFFFF?text=Dungeon+Crawler+Gameplay" alt="Gameplay Screenshot"/>
</p>

This project is a 2D dungeon crawler game developed in C++ using the SFML library for graphics and input handling. It serves as a demonstration of core object-oriented programming principles, custom data structures, and modern C++ features. The player navigates a series of rooms, fights monsters, avoids traps, and collects items with the ultimate goal of defeating the final boss.

---

### **Table of Contents**
- [Project File Structure](#project-file-structure)
- [Key Features](#key-features)
- [How to Build and Run](#how-to-build-and-run)
- [How to Play](#how-to-play)
- [Gameplay Walkthrough](#gameplay-walkthrough)
- [Tips for Success](#tips-for-success)

---

## Project File Structure

Below is an overview of the project's directory structure, with links to each file in the repository.

```
/
├── Files/
│   ├── Headers/
│   │   ├── [CustomQueue.h](Files/Headers/CustomQueue.h)
│   │   ├── [CustomStack.h](Files/Headers/CustomStack.h)
│   │   ├── [Dungeon.h](Files/Headers/Dungeon.h)
│   │   ├── [Enemy.h](Files/Headers/Enemy.h)
│   │   ├── [Entity.h](Files/Headers/Entity.h)
│   │   ├── [Game.hpp](Files/Headers/Game.hpp)
│   │   ├── [GameGUI.hpp](Files/Headers/GameGUI.hpp)
│   │   ├── [Player.h](Files/Headers/Player.h)
│   │   └── [Room.h](Files/Headers/Room.h)
│   ├── Source/
│   │   ├── [Dungeon.cpp](Files/Source/Dungeon.cpp)
│   │   ├── [Enemy.cpp](Files/Source/Enemy.cpp)
│   │   ├── [Entity.cpp](Files/Source/Entity.cpp)
│   │   ├── [Game.cpp](Files/Source/Game.cpp)
│   │   ├── [GameGui.cpp](Files/Source/GameGui.cpp)
│   │   ├── [Player.cpp](Files/Source/Player.cpp)
│   │   └── [Room.cpp](Files/Source/Room.cpp)
│   └── main/
│       └── [Main.cpp](Files/main/Main.cpp)
├── .vscode/
│   └── [tasks.json](.vscode/tasks.json)
├── assets/
│   └── (Images and Fonts)
└── README.md
```

---

## Key Features

### Gameplay
* **State-Driven Menus:** The game features a full menu system, including a start screen, rules screen, victory screen, and game over screen, all managed by the central [Game engine](Files/Source/Game.cpp).
* **Interactive Combat:** A turn-based combat system with a Quick Time Event (QTE) mechanic where the player must match a sequence of keys to attack successfully.
* **Enemy Variety:** Multiple enemy types (Imp, Skeleton, Boss) with scaling difficulty and unique sprite animations.
* **Dungeon Exploration:** A multi-room dungeon connected in a non-linear fashion, encouraging exploration.
* **Player Progression:** The player can find and use items, such as potions and equipment, to aid their journey.
* **Traps & Puzzles:** Rooms can contain traps that require player decisions to overcome, and progression is gated by finding keys.

### Technical
* **Object-Oriented Design:** The codebase is built on a solid OOP foundation. An abstract [`Entity`](Files/Headers/Entity.h) class defines a common interface for the [`Player`](Files/Headers/Player.h) and [`Enemy`](Files/Headers/Enemy.h) classes, which inherit from it. Polymorphism is used for functions like `attack()` and `update()`.
* **Custom Data Structures:**
    * A custom **[`Stack`](Files/Headers/CustomStack.h)** is implemented to provide a "backtrack" feature, allowing the player to undo their last move.
    * A custom **[`Queue`](Files/Headers/CustomQueue.h)** is used to manage enemy encounters. Fleeing from an enemy places it in a queue, forcing the player to defeat it before proceeding to the next major fight.
* **Modern C++ Features:**
    * **[Lambdas](Files/Source/Dungeon.cpp):** The item usage system is powered by a `std::map` that links item names to lambda functions, creating a flexible and scalable way to define item effects.
    * **STL Containers:** Extensive use of `std::vector` for inventories, `std::string` for descriptions, and `std::map` for the item system.
    * **Smart Pointers:** `std::shared_ptr` is used to manage the memory for `Room` and `Enemy` objects, preventing memory leaks.
* **SFML Graphics:** All rendering, from the player and enemy sprites to the user interface, is handled using the [`GameGUI`](Files/Headers/GameGUI.hpp) class.

---

## How to Build and Run

### Prerequisites
* A C++ compiler that supports C++17 (e.g., g++).
* The **SFML** library (version 2.5 or higher) installed and correctly linked.

### Method 1: Using Visual Studio Code (Recommended)

1.  Create a folder named `.vscode` in the root directory of your project if it does not already exist.
2.  Inside the `.vscode` folder, create a new file named [`tasks.json`](.vscode/tasks.json).
3.  Paste the content from the `tasks.json` file in this repository into your new file.
4.  With [`Main.cpp`](Files/main/Main.cpp) as the active file, you can now build the project by pressing **`Ctrl+Shift+B`**. This will create the executable `DungeonGame.exe` in your project's root folder.

### Method 2: Using the Command Line (Manual)
Navigate to your project's root directory in the terminal and compile all the `.cpp` source files together using the following command:

```bash
g++ Files/Source/*.cpp Files/main/Main.cpp -o DungeonGame.exe -lsfml-graphics -lsfml-window -lsfml-system
```

### Running the Game
After a successful build, run the executable from the terminal to start the game.

```bash
./DungeonGame.exe
```

---

## How to Play

* **Move:** Use the **W, A, S, D** keys to move North, West, South, and East.
* **Backtrack:** Press **B** to return to the last room you visited.
* **Use Item:** Press **U** to open the item menu, then press the corresponding number key to use an item.
* **Make Choices:** Use the **Number Keys** (`1`, `2`, etc.) to select options during combat or when interacting with traps.
* **Menus:** Press **Enter** to advance through the start and rules screens.
* **Exit Game:** Press **Escape** at any time to close the game.

---

### MORE INFO

#### Gameplay Walkthrough

1.  Launch the game to see the start screen, then press **Enter** to view the rules. Press **Enter** again to begin.
2.  You will start in a central room. Use **W, A, S, D** to explore adjacent rooms.
3.  When you find an item, a prompt will appear. Press **Y** to add it to your inventory.
4.  If you enter a room with an enemy, combat will begin. You can choose to **Fight** or **Run**.
5.  If you choose to fight, a sequence of WASD keys will appear. Type the sequence correctly to damage the enemy.
6.  To use an item like a potion, press **U** to open the item menu, then press the number corresponding to the item you want to use.
7.  Keep an eye on your **HP** and **Stamina** displayed at the bottom of the screen. If either reaches zero, the game is over.
8.  Your goal is to find the keys and items necessary to reach and defeat the final boss.

#### Tips for Success

* **Watch Your Stamina:** Every move you make (North, South, East, West) consumes stamina. Running out of stamina means game over, so plan your route and don't explore needlessly.
* **Use Backtrack Strategically:** The backtrack feature (**B** key) is powerful for escaping a dangerous area, but remember that it still costs one stamina point.
* **Items Are Key:** Don't forget to use your items! Potions can be a lifesaver before a big fight, and some items are required to open new paths. Press **U** to see what you can use.
* **Read the Messages:** Pay close attention to the text in the message box at the top of the screen. It provides crucial information about traps, combat results, and story progression.
* **Consult the Map:** If you get lost or are unsure where to go next, refer to the **`map.png`** file provided with the game. It shows the complete layout of all the rooms and can help you find your way.
