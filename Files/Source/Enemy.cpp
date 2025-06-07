#include "../Headers/Enemy.h"
#include "../Headers/Player.h"
#include <cstdlib>
#include <iostream>

Enemy::Enemy(const std::string& n, int h, int a1, int a2, const std::string& texturePath)
    : Entity(n, h), attack1(a1), attack2(a2) {
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Error loading enemy texture: " << texturePath << std::endl;
    }
    if (!hurtTexture.loadFromFile("../assets/hurt.png")) {
        std::cerr << "Error loading hurt texture!" << std::endl;
    }
    sprite.setTexture(texture);

    if (name == "Bartholmew" || name == "Tyrian the Imp" || name == "Orcus the Bloodforged") {
        sprite.setTextureRect(sf::IntRect(0, 0, 8, 8));
    } else {
        sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
    }

    this->isHurt = false;
    this->animationSpeed = 0.2f;
    this->currentFrame = 0;
    this->frameWidth = 8;
    this->frameHeight = 8;

    sprite.setScale(15.0f, 15.0f); 
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
    sprite.setPosition(500.f, 450.f);
    originalPosition = sprite.getPosition();
}

void Enemy::attack(Entity& target) {
    int dmg = (rand() % 2 == 0) ? attack1 : attack2;
    std::cout << RED << name << " attacks for " << dmg << " damage!" << RESET << std::endl;
    target.takeDamage(dmg);
}

sf::Sprite& Enemy::getSprite() {
    return sprite;
}

void Enemy::triggerHurtEffect() {
    if (!isHurt) {
        isHurt = true;
        hurtClock.restart();
    }
}

void Enemy::update() {
    if (isHurt) {
        if (hurtClock.getElapsedTime().asSeconds() < hurtDuration) {
            sprite.setTexture(hurtTexture);
            float offsetX = (rand() % 9) - 4;
            float offsetY = (rand() % 9) - 4;
            sprite.setPosition(originalPosition.x + offsetX, originalPosition.y + offsetY);
        } else {
            isHurt = false;
            sprite.setTexture(texture);
            sprite.setPosition(originalPosition);
        }
    } else {
        if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
            currentFrame = (currentFrame + 1) % 2;
            int frameX = currentFrame * frameWidth;
            sprite.setTextureRect(sf::IntRect(frameX, 0, frameWidth, frameHeight));
            animationClock.restart();
        }
    }
}