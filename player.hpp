#ifndef PLAYER
#define PLAYER

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
        int xAfterMove(int keyPressed);
        int yAfterMove(int keyPressed);
        void move(int keyPressed);
        void removeHealth(int hpsToBeRemoved);
        void addHealth(int hpsToBeAdded);
        void removePoints(int pointsToBeRemoved);
        void addPoints(int pointsToBeAdded);
};

#endif