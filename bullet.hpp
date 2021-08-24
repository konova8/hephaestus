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
        Bullet(int x = -1, int y = -1, int damage = 10, int direction = 1, char symbol = '*');
        void hitPlayer(Player *player); //Removes this->damage health from Player
        int getDirection();
        void move();
};

#endif