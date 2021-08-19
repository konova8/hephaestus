#ifndef TURRET
#define TURRET
#include "bullet.hpp"

class Turret
{
    protected:
        int x;
        int y;
        Bullet bullet;
    public:
        Turret();
        void updateBullet();
        void resetBullet();
};

#endif