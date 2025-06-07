#include "../Headers/Player.h"

Player::Player() : Entity("Player", 200), stamina(100), equippedWeapon("Bow") {
    inventory.push_back("Arrow");
}

void Player::attack(Entity& target) {

}

void Player::update() {

}

void Player::restoreHealth(int amount) {
    hp += amount;
    if (hp > 200) hp = 200;
    std::cout << GREEN << "You healed " << amount << " HP! HP: " << hp << RESET << std::endl;
}

void Player::addItem(std::string item) {
    inventory.push_back(item);
    std::cout << YELLOW << "Picked up: " << item << RESET << std::endl;
}

bool Player::hasItem(std::string item) {
    for (auto &i : inventory) {
        if (i == item) return true;
    }
    return false;
}

void Player::displayStats() {
    std::cout << GREEN << "HP: " << hp << " | Stamina: " << stamina << " | Weapon: " << equippedWeapon << RESET << std::endl;
}

void Player::viewInventory() {
    std::cout << BLUE << "\n--- Inventory ---" << RESET << std::endl;
    if (inventory.empty()) {
        std::cout << YELLOW << "Your inventory is empty!" << RESET << std::endl;
    } else {
        for (const std::string &item : inventory) {
            std::cout << YELLOW << "- " << item << RESET << std::endl;
        }
    }
}