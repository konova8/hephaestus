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
        SingleBlockEntity(int x = -1, int y = -1, bool exists = true, char symbol = '0');
        int getX();
        int getY();
        bool getExistence();
        int getXAfterMove(int xChange);
        int getYAfterMove(int yChange);
        bool isColliding(SingleBlockEntity entity, int xChange = 0, int yChange = 0);
        void print();
        void move(int moveX, int moveY);
        void deactivate();
};

#endif
