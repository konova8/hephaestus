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
        struct updateData
        {
            int updateCounter;
            int updateTime;
            updateData(int updateTime = 15)
            {
                this->updateCounter = 0;
                this->updateTime = updateTime;
            }
        };
        Platform *platforms[N_PLATFORMS];
        Enemy *enemies[N_ENEMIES];
        Turret *turrets[N_TURRETS];
        Bonus *bonuses[N_BONUSES];
        updateData turretsUpdate;
        updateData enemiesUpdate;
        int width;
        int height;
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
        void playerUpdate(Player *player, int move);
        bool isPlayerUnderPlatform(Player player);
        int isPlayerAtBorder(); //Returns -1 if player is at left border, 1 if player is at right border, 0 if it is not at any border
        
};

#endif