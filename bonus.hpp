#ifndef BONUS
#define BONUS
#include "singleBlockEntity.hpp"

class Bonus : public SingleBlockEntity
{
    protected:
        char bonusType; //h or p
    public:
        Bonus();
        Bonus(int x, int y, char symbol, char bonusType);
        
};

#endif