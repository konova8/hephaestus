#ifndef PLAYER
#define PLAYER
#include "singleBlockEntity.hpp"
#include <ncurses.h>

class Player : public SingleBlockEntity
{
    protected:
        int maxHealth;
        int health;
        int points;
    public:
        Player(int x, int y, char symbol, int health = 100, int points = 0);
        int getXAfterMove(int keyPressed); //Returns the x after the move corresponding to the key pressed
        void move(int keyPressed); //Moves based on the key pressed
        using SingleBlockEntity::move;
        void pointsChange(int change);
        void healthChange(int change);
        int getHealth(); 
        int getPoints();
};

#endif