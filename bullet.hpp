#ifndef BULLET
#define BULLET
#include "singleBlockEntity.hpp"

class Bullet : public SingleBlockEntity
{
    protected:
        int damage;
        int direction;
    public:
        Bullet();
        Bullet(int x, int y, int damage, int direction, char symbol);
        void hitPlayer();
};

#endif