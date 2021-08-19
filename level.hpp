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
        bool isPlayerMoveLegal(Player player, int keyPressed);
        bool isEnemyMoveLegal(Enemy *enemy);
        void isAlive(int x, int y);
        void drawBorders();
        void setPlatforms(int index);
        void setTurrets(int index);
        void setEnemies(int index);
        void setBonuses(int index);
    public:
        Level(int index);
        void drawLevel();
        void updateLevel();
        void exitLevel();
        bool isPlayerUnderPlatform(Player player);
        int height;
        
};

#endif