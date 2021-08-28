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
#define MAX_POINTBONUS 100
#define MIN_BULLET_UPDATE 3
#define MIN_ENEMY_UPDATE 2

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
        int randomInRange(int min, int max);
        void initializeEntitiesLists();
        bool isPlayerMoveLegal(Player player, int keyPressed);
        bool isPlayerGoingOutMap(int keyPressed);
        bool isPlayerGoingOutPlatform(int keyPressed);
        void drawBorders(int index);
        void setPlatforms(int index);
        void setEntities(int index);
        int findTurretIndex(Player *player);
        int findEnemyIndex(Player *player);
        bool checkEnemyCollisions1(Player *player, bool sideMoveIsLegal, bool changedPlatform, int enemyIndex, int keyPressed);
        bool checkEnemyCollisions2(Player *player, int enemyIndex);
        bool checkBulletCollisions2(Player player, int xChange, int correspondingTurretIndex);
    public:
        Level(int index = 1);
        int getWidth();
        int getHeight();
        void drawLevel(Player player, int index);
        void updateLevel();
        int isAtBottomBorder(); //Returns 1 if player is at right bottom border, 0 if it is not at a bottom border, -1 if it is at the left bottom border
        void exitLevel(int index);
        void playerUpdate(Player *player, int keyPressed, int index);
        int isPlayerAtBorder(Player player); //Returns -1 if player is at left border, 1 if player is at right border, 0 if it is not at any border
        
};

#endif