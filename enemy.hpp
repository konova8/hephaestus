#ifndef ENEMY
#define ENEMY
#include "bullet.hpp"
#include "player.hpp"

class Enemy : public Bullet
{
    protected:
        bool movedSinceLastHit = true;
    public:
        using Bullet::Bullet;
        void hitPlayer(Player *player); //Removes this->damage points from player health
        void move();
        void reverseDirection(); //Reverses the direction (1 = right, -1 = left)
};

#endif
