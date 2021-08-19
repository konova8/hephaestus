#ifndef ENEMY
#define ENEMY
#include "bullet.hpp"

class Enemy : public Bullet
{
    protected:
        bool alive;
    public:
        Enemy(int x, int y, int damage, int direction, char symbol);
        void hitPlayer();
        void reverseDirection();
        bool isAlive();

};

#endif