#ifndef TURRET
#define TURRET
#include "singleBlockEntity.hpp"
#include "bullet.hpp"

class Turret : public SingleBlockEntity
{
    protected:
        Bullet *bullet;
    public:
        Turret(int x, int y, bool exists, char symbol);
        void updateBullet(); //Moves the bullet
        void resetBullet(); //Brings the bullet back to the turret position
        int getBulletDirection();
        bool isBulletColliding(SingleBlockEntity entity);
        void printBullet();
};

#endif