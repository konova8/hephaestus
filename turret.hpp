#ifndef TURRET
#define TURRET
#include "singleBlockEntity.hpp"
#include "bullet.hpp"

class Turret : public SingleBlockEntity
{
    protected:
        Bullet bullet;
    public:
        Turret(bool exists);
        void updateBullet();
        void resetBullet();
};

#endif