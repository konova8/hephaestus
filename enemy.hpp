#ifndef ENEMY
#define ENEMY
#include "bullet.hpp"
#include "player.hpp"

class Enemy : public Bullet
{
    protected:
        bool movedSinceLastHit = true;
    public:
        using Bullet::Bullet; //Tells Enemy to use the Bullet::Bullet constructor without making changes to it
        void hitPlayer(Player *player); //Removes this->damage points from player health and suicides (use Bullet::hitPlayer for the former)
        void move();
        void reverseDirection(); //Reverses the direction (1 = right, -1 = left)
};

#endif
