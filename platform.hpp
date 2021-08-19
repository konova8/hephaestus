#ifndef PLATFORM
#define PLATFORM

class Platform
{
    protected:
        int startingPointX;
        int endingPointX;
        int y;
    public:
        Platform(int startingPointX, int endingPointX, int y, char symbol);
        char symbol;
};

#endif