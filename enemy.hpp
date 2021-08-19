#ifndef ENEMY
#define ENEMY
#include "level.hpp"

class Enemy : public Bullet
{
    public:
        Enemy(int x, int y, int damage, int direction, char symbol);
        void hitPlayer();
        void reverseDir();

};

#endif