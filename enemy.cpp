#include "enemy.hpp"

void Enemy::hitPlayer(Player *player)
{
    Bullet::hitPlayer(player);
    SingleBlockEntity::deactivate();
}

void Enemy::reverseDirection(){
    this->direction = -(this->direction);
}