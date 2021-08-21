#ifndef ENEMY
#define ENEMY
#include "bullet.hpp"
#include "player.hpp"

class Enemy : public Bullet
{
    public:
        using Bullet::Bullet; //Tells Enemy to use the Bullet::Bullet constructor without making changes to it
        void hitPlayer(Player *player); //Removes this->damage points from player health and kills it (use Bullet::hitPlayer for the former)
        void reverseDirection(); //Reverses the direction (1 = right, -1 = left)
};

#endif