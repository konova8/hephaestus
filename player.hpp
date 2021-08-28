#ifndef PLAYER
#define PLAYER
#include "singleBlockEntity.hpp"
#include <ncurses.h>

class Player : public SingleBlockEntity
{
    protected:
        int health;
        int points;
    public:
        Player(int x, int y, char symbol, int health = 100, int points = 0);
        int getXAfterMove(int keyPressed); //Returns the x after the key pressed
        int getYAfterMove(int keyPressed); //Returns the y after the key pressed
        void move(int keyPressed); //Moves based on the key pressed, use SingleBlockEntity::move
        using SingleBlockEntity::move;
        void healthChange(int change); //Self explanatory
        void pointsChange(int change); //Self explanatory
        int getHealth(); 
        int getPoints();
};

#endif