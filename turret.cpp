#include "turret.hpp"

void Turret::updateBullet()
{
    bullet.move();
}

void Turret::resetBullet()
{
    bullet = Bullet(this->x, this->y, bullet.getDirection());
}