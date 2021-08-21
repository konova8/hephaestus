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
        SingleBlockEntity(int x = -1, int y = -1, bool exists = true, char symbol = ' ');
        void move(int moveX, int moveY);
        bool getExistence();
        void deactivate();
        void print();
};

#endif
