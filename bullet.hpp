#ifndef BULLET
#define BULLET

class Bullet {
    protected:
        int x;
        int y;
        int damage;
        int direction;
        char symbol;
    public:
        Bullet(int x, int y, int damage, int direction, char symbol);
        void move();
        void hitPlayer();
        void print();
        
};

#endif