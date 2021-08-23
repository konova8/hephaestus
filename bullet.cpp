#include "bullet.hpp"

Bullet::Bullet(int x, int y, int damage, int direction, char symbol) : SingleBlockEntity(x, y, symbol)
{
    this->damage = damage;
    this->direction = direction;
}

int Bullet::getDirection()
{
    return this->direction;
}
