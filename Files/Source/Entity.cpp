#include "../Headers/Entity.h"

Entity::Entity(const std::string& n, int h) : name(n), hp(h) {}

void Entity::takeDamage(int dmg) {
    hp -= dmg;
    if (hp < 0) hp = 0;
}

bool Entity::isAlive() const {
    return hp > 0;
}

void Entity::update() {

}