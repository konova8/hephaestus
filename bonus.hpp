#ifndef BONUS
#define BONUS

class Bonus
{
    protected:
        char symbol;
        char bonusType;
        int x;
        int y;
        bool used;
    public:
        Bonus(int x, int y, char symbol, char bonusType);
        bool isUsed();
        void use();
};

#endif