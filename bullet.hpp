#ifndef BULLET
#define BULLET
#include "singleBlockEntity.hpp"
#include "player.hpp"

class Bullet : public SingleBlockEntity
{
    protected:
        int damage;
        int direction;
    public:
        Bullet(int x = -1, int y = -1, int direction = 1, int damage = 10, char symbol = '*');
        void hitPlayer(Player *player); //Removes this->damage health points from player
        int getDirection();
        int getXAfterMove();
        using SingleBlockEntity::move;
        void move(); //moves x of bullet to the this->direction by one single block
};

#endif