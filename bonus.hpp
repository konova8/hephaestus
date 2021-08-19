#ifndef BONUS
#define BONUS
#include "level.hpp"

class Bonus
{
    protected:
        char symbol;
        char bonusType;
        int x;
        int y;
    Bonus(Level currentLevel);
    void remove();
};

#endif