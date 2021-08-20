#ifndef SINGLEBLOCKENTITY
#define SINGLEBLOCKENTITY

class SingleBlockEntity
{
    protected:
        int x;
        int y;
        bool exists;
        char symbol;
    public:
        SingleBlockEntity();
        SingleBlockEntity(int x, int y, bool exists, char symbol);
        void move(int moveX, int moveY);
        bool getExistence();
        void deactivate();
        void print();
};

#endif
