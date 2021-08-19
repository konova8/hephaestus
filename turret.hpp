#ifndef TURRET
#define TURRET
#include "bullet.hpp"

class Turret
{
    protected:
        int x;
        int y;
        bool status;
        Bullet bullet;
    public:
        Turret(bool exists);
        void updateBullet();
        void resetBullet();
        bool getStatus();
};

#endif