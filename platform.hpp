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
        bool isPositionOnPlatform(int x, int y);
};

#endif