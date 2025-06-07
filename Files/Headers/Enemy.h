#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp> 
#include <SFML/System/Clock.hpp>
#include "Entity.h"

class Enemy : public Entity {
public:
    int attack1, attack2;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Texture hurtTexture;

    Enemy(const std::string& n, int h, int a1, int a2, const std::string& texturePath);

    void attack(Entity& target) override;
    sf::Sprite& getSprite();
    
    void update() override;
    void triggerHurtEffect();

private:
    sf::Clock animationClock;
    float animationSpeed;
    int currentFrame;
    int frameWidth;
    int frameHeight;

    bool isHurt;
    sf::Clock hurtClock;
    const float hurtDuration = 0.15f;
    sf::Vector2f originalPosition;
};

#endif