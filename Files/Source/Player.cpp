#include "../Headers/Player.h"

Player::Player() : hp(200), stamina(100), equippedWeapon("Bow") {
    inventory.push_back("Arrow");
}

void Player::takeDamage(int dmg) {
    hp -= dmg;
    if (hp < 0) hp = 0;
    cout << RED << "You took " << dmg << " damage! HP: " << hp << RESET << endl;
}

void Player::restoreHealth(int amount) {
    hp += amount;
    if (hp > 150) hp = 150;
    cout << GREEN << "You healed " << amount << " HP! HP: " << hp << RESET << endl;
}

void Player::addItem(string item) {
    inventory.push_back(item);
            cout << YELLOW << "Picked up: " << item << RESET << endl;
}

bool Player::hasItem(string item) {
    for (auto &i : inventory) {
        if (i == item) return true;
    }
    return false;
}

void Player::displayStats() {
    cout << GREEN << "HP: " << hp << " | Stamina: " << stamina << " | Weapon: " << equippedWeapon << RESET << endl;
}

void Player::viewInventory() {
    cout << BLUE << "\n--- Inventory ---" << RESET << endl;
    if (inventory.empty()) {
        cout << YELLOW << "Your inventory is empty!" << RESET << endl;
    } else {
        for (const string &item : inventory) {
            cout << YELLOW << "- " << item << RESET << endl;
        }
    }
}

bool Player::isAlive() {
    return hp > 0;
}

    
                     
          
            
       
      
    