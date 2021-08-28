#include "enemy.hpp"

void Enemy::hitPlayer(Player *player)
{
    Bullet::hitPlayer(player);
}

void Enemy::reverseDirection(){
    this->direction = -(this->direction);
}