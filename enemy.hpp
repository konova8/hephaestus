#ifndef ENEMY
#define ENEMY
#include "level.hpp"

class Enemy
{
    protected:
        int x;
        int y;
        int damage;
        char direction;
    public:
        Enemy(Level level);
        void move(Level level);
        void kill();
        void reverseDir();

};

#endif