#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <iostream>
#include "Player.h"

class Enemy {
public:
    std::string name;
    int hp, attack1, attack2;

    Enemy(const std::string& n, int h, int a1, int a2);
    void attack(Player& player);
    bool isAlive() const;
    void takeDamage(int dmg);
};

#endif
