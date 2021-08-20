#ifndef PLAYER
#define PLAYER
#include "singleBlockEntity.hpp"

class Player : public SingleBlockEntity
{
    protected:
        int health;
        int points;
    public:
        Player(int x, int y, char symbol, int health = 100, int points = 0);
        int getXAfterMove(int keyPressed);
        int getYAfterMove(int keyPressed);
        void keyMove(int keyPressed);
        void removeHealth(int hpsToBeRemoved);
        void addHealth(int hpsToBeAdded);
        void removePoints(int pointsToBeRemoved);
        void addPoints(int pointsToBeAdded);
        int getHealth();
        int getPoints();
};

#endif