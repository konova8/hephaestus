#include "bullet.hpp"

Bullet::Bullet()
{
    this->x = 0;
    this->y = 0;
    this->damage = 10;
    this->direction = 1;
    this->symbol = '*';
}


Bullet::Bullet(int x, int y, int damage, int, char symbol)
{
    this->x = x;
    this->y = y;
    this->damage = damage;
    this->direction = direction;
    this->symbol = symbol;
}