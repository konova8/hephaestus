#ifndef TURRET
#define TURRET
#include "singleBlockEntity.hpp"
#include "bullet.hpp"

class Turret : public SingleBlockEntity
{
    protected:
        Bullet bullet;
    public:
        using SingleBlockEntity::SingleBlockEntity;
        void updateBullet(); //Moves the bullet
        void resetBullet(); //Brings the bullet back to the turret position
};

#endif