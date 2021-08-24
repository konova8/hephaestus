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
        Bullet(int x, int y, int damage, int direction, char symbol);
        void hitPlayer(Player *player); //Removes this->damage health from Player
        int getDirection();
        void move();
};

#endif