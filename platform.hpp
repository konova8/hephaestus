#ifndef PLATFORM
#define PLATFORM

class Platform
{
    protected:
        int startingPointX;
        int endingPointX;
        char symbol;
        int y;
    public:
        Platform(int startingPointX, int endingPointX, int y, char symbol);
        bool isEntityUnderPlatform(int entityY); //Returns true if y is one single block under the platform
        int getStartingPointX();
        int getEndingPointX();
        int getY();
        void print();
};

#endif