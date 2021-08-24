#ifndef BONUS
#define BONUS
#include "singleBlockEntity.hpp"
#include "player.hpp"

class Bonus : public SingleBlockEntity
{
    protected:
        char bonusType; //h or p, h = health bonus, p = points bonus
        int bonusEffect;
    public:
        Bonus(int x, int y, char bonusType, int bonusEffect); //Constructor, if in doubt look at Bullet::Bullet and/or university slides
        void use(Player *player); //If health bonus add bonusEffect to health, if point bonus add bonusEffect to points
        
};

#endif