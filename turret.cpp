#include "turret.hpp"

Turret::Turret(int x, int y, bool exists, char symbol) : SingleBlockEntity(x, y, exists, symbol)
{
    int bulletDirection;
    if(this->x == 1)
    {
        bulletDirection = 1;
    }
    else
    {
        bulletDirection = -1;
    }
    bullet = new Bullet(x, y, bulletDirection, 10, '*');
}

void Turret::updateBullet()
{
    bullet->move();
}

void Turret::resetBullet()
{
    int blocksToMove = this->x - bullet->getX();
    bullet->move(blocksToMove, 0);
}

int Turret::getBulletDirection()
{
    return this->bullet->getDirection();
}

bool Turret::isBulletColliding(SingleBlockEntity entity)
{
    return bullet->isColliding(entity);
}

void Turret::printBullet()
{
    bullet->print();
}
