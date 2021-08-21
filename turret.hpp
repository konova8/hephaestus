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
        void updateBullet(int xLeft, int xRight); //Moves bullet to appropriate direction (determined based on this->x, turrets with this->x = xLeft are on the left, this->x = xRight are on the right, use SingleBlockEntity::move)
        void resetBullet(); //Brings the bullet back to the turret position
};

#endif