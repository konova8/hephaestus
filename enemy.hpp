#ifndef ENEMY
#define ENEMY
#include "bullet.hpp"

class Enemy : public Bullet
{
    protected:
        bool alive;
    public:
        Enemy(int x, int y, int damage, int direction, char symbol, bool alive);
        void hitPlayer();
        void reverseDirection();
        bool isAlive();
        int getX();

};

#endif