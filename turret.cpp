#include "turret.hpp"

void Turret::updateBullet()
{
    bullet.move();
}

void Turret::resetBullet()
{
    bullet = Bullet(this->x, this->y, bullet.getDirection());
}

int Turret::getBulletDirection()
{
    return this->bullet.getDirection();
}

bool Turret::isBulletColliding(SingleBlockEntity entity)
{
    return bullet.isColliding(entity);
}