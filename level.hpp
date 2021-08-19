#ifndef LEVEL
#define LEVEL
#include "player.hpp"
#include "bonus.hpp"
#include "enemy.hpp"
#include "turret.hpp"
#include "platform.hpp"
#define N_PLATFORMS 6 
#define N_ENEMIES 4
#define N_TURRETS 3
#define N_BONUSES 2

class Level
{
    protected:
        Platform *platforms[N_PLATFORMS];
        Enemy *enemies[N_ENEMIES];
        Turret *turrets[N_TURRETS];
        Bonus *bonuses[N_BONUSES];
        int updateCounter;
        int turretUpdateTime;
        int enemiesUpdateTime;
        int width;
        int height;
        void isMoveLegal(Player player, int keyPressed);
        void isAlive(int x, int y);
    public:
        Level(int index);
        void drawLevel();
        void updateLevel();
        void exitLevel();
        
};

#endif