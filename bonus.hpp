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
        Bonus(int x, int y, char bonusType, int bonusEffect);
        void use(Player *player); //If health bonus adds bonusEffect to health, if point bonus adds bonusEffect to points
};

#endif