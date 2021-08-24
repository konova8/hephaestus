#include "bullet.hpp"

Bullet::Bullet(int x, int y, int direction, int damage, char symbol) : SingleBlockEntity(x, y, symbol)
{
    this->damage = damage;
    this->direction = direction; // 1 DX, -1 SX, non usare altri valori
}

int Bullet::getDirection()
{
    return this->direction;
}

void Bullet::hitPlayer(Player *player)
{
    player->healthChange(this->damage);
}

void Bullet::move()
{
    SingleBlockEntity::move(this->direction, 0);
}