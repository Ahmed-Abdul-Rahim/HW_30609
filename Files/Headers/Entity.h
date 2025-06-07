#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity {
public:
    std::string name;
    int hp;

    Entity(const std::string& n, int h);
    virtual ~Entity() = default;

    void takeDamage(int dmg);
    bool isAlive() const;

    virtual void attack(Entity& target) = 0;
    virtual void update();
};

#endif