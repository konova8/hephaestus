#ifndef PLAYER
#define PLAYER
#include "level.hpp"

class Player
{
    protected:
        bool alive;
        int x;
        int y;
        int health;
        int points;
    public:
        Player(int x, int y);
        void move(int keyPressed, Level level);
        void removeHealth(int hpsToBeRemoved);
        void addHealth(int hpsToBeAdded);
        void removePoints(int pointsToBeRemoved);
        void addPoints(int pointsToBeAdded);
        bool isPlayerUnderPlatform(Level level);
};

#endif