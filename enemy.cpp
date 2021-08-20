#include "enemy.hpp"

Enemy::Enemy(int x, int y, int damage, int direction, char symbol, bool alive)
{
    this->x = x;
    this->y = y;
    this->damage = damage;
    this->direction = direction;
    this->symbol = symbol;
    this->alive = alive;
}

bool Enemy::isAlive() { return this->alive; }

int Enemy::getX() { return this->x; }
