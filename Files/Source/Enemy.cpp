#include "../Headers/Enemy.h"
#include "../Headers/Player.h"
#include <cstdlib> // for rand()

Enemy::Enemy(const std::string& n, int h, int a1, int a2)
    : name(n), hp(h), attack1(a1), attack2(a2) {}

void Enemy::attack(Player& player) {
    int dmg = (rand() % 2 == 0) ? attack1 : attack2;
    std::cout << RED << name << " attacks for " << dmg << " damage!" << RESET << std::endl;
    player.takeDamage(dmg);
}

bool Enemy::isAlive() const {
    return hp > 0;
}

void Enemy::takeDamage(int dmg) {
    hp -= dmg;
    if (hp < 0) hp = 0;
}
