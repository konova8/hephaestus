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
#define MIN_DAMAGE 10
#define MAX_DAMAGE 100
#define MAX_HEALTHBONUS 50
#define MIN_HEALTHBONUS 5
#define MIN_POINTSBONUS 10
#define MIN_BULLET_UPDATE 3
#define MIN_ENEMY_UPDATE 2

class Level
{
    protected:
        int index;
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
        bool needsDraw;
        char spaces[100];
        int randomInRange(int min, int max);
        void initializeEntitiesLists();
        void drawBorders();
        void setPlatforms();
        bool entityGenerationCheck(bool allEntities, int remainingPlatforms, int entitiesSpawned, int entitiesToBeSpawned, int chance);
        void setEntities();
        int findTurretIndex(Player *player);
        int findEnemyIndex(Player *player);
    public:
        Level(int index = 1);
        int getWidth();
        int getHeight();
        void drawLevel(Player player);
        void updateLevel();
        void playerUpdate(Player *player, int keyPressed);
        int isPlayerAtBorder(Player player); //Returns -1 if player is at bottom left border, 1 if player is at bottom right border, 0 if it is not at any border
        int getIndex();
        
};

#endif