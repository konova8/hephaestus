#ifndef TURRET
#define TURRET
#include "singleBlockEntity.hpp"
#include "bullet.hpp"
#include "player.hpp"

class Turret : public SingleBlockEntity
{
    protected:
        Bullet *bullet;
    public:
        Turret(int x, int y, bool exists, char symbol);
        void updateBullet(); //Moves the bullet
        void resetBullet(); //Brings the bullet back to the turret position
        int getBulletDirection();
        int getBulletX();
        bool isBulletColliding(SingleBlockEntity entity); //Checks if the bullet is colliding with an entity
        void printBullet();
        void hitPlayer(Player *player);
};

#endif