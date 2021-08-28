#include "enemy.hpp"

void Enemy::hitPlayer(Player *player)
{
    if(movedSinceLastHit == true)
    {
        Bullet::hitPlayer(player);
        movedSinceLastHit = false;
    }
}

void Enemy::move()
{
    Bullet::move();
    if(!movedSinceLastHit)
    {
        movedSinceLastHit = true;
    }
}

void Enemy::reverseDirection(){
    this->direction = -(this->direction);
}
