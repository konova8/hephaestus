#include "level.hpp"
#include <iostream> //Testing purposes, will remove later
#include <cstdlib>
#include <ncurses.h>
#include <string.h>

using namespace std;

Level::Level(int index)
{
    this->width = 40;
    this->height = 15;
    turretsUpdate.updateTime = 20 - index < MIN_BULLET_UPDATE ? MIN_BULLET_UPDATE : index - 20;
    enemiesUpdate.updateTime = 20 - index < MIN_ENEMY_UPDATE ? MIN_ENEMY_UPDATE : index - 20;
    initializeEntitiesLists();
    setPlatforms(index);
    setEntities(index);
}

int Level::randomInRange(int min, int max)
{
    if(max < min)
    {
        int tmp = max;
        max = min;
        min = tmp;
    }
    return (rand() % (max - min + 1) + min);
}

void Level::initializeEntitiesLists()
{
    for(int i = 0; i < N_PLATFORMS; i++)
    {
        platforms[i] = NULL;
    }
    for(int i = 0; i < N_TURRETS; i++)
    {
        turrets[i] = NULL;
    }
    for(int i = 0; i < N_ENEMIES; i++)
    {
        enemies[i] = NULL;
    }
    for(int i = 0; i < N_BONUSES; i++)
    {
        bonuses[i] = NULL;
    }
}

void Level::drawBorders(int index)
{
    for(int i = 1; i < this->width; i++)
    {
        mvaddch(0, i, '-');
        mvaddch(this->height, i, '-');
    }
    for(int i = 0; i <= this->height; i++)
    {
        if(i == this->height - 1 && index != 1)
        {
            mvaddch(i, 0, '[');
            mvaddch(i, this->width, ']');
        }
        else if(i == this->height - 1)
        {
            mvaddch(i, 0, '|');
            mvaddch(i, this->width, ']');
        }
        else
        {
            mvaddch(i, 0, '|');
            mvaddch(i, this->width, '|');
        }
    }
}

void Level::setPlatforms(int index)
{
    int platformsToBuild = index > N_PLATFORMS ? N_PLATFORMS : index;
    int startingX = -1, y = this->height - 2, endingX = -1, minimumLength = 5;
    for(int i = 0; i < platformsToBuild; i++)
    {
        if(i == 0)
        {
            startingX = randomInRange(10, width - 10);
        }
        else
        {
            if(endingX < startingX)
            {
                startingX = randomInRange(0, startingX - endingX) + endingX;
            }
            else
            {
                startingX = randomInRange(0, endingX - startingX) + startingX;
            }
        }
        if(startingX < width / 2)
        {
            do
            {
                endingX = randomInRange(startingX, this->width - 5 - minimumLength) + minimumLength;
            }
            while(endingX == startingX);
        }
        else
        {
            do
            {
                endingX = randomInRange(5 + minimumLength, startingX) - minimumLength;
            }
            while(endingX == startingX);
        }
        platforms[i] = new Platform(startingX, endingX, y, '=');
        y -= 2;
    }
}

void Level::setEntities(int index)
{
    bool allTurrets = index > N_TURRETS;
    bool allEnemies = index > N_ENEMIES;
    bool allBonuses = index > N_BONUSES;
    int turretsBuilt = 0, enemiesSpawned = 0, bonusesSpawned = 0;
    int turretsToBeBuilt = allTurrets ? N_TURRETS : index;
    int enemiesToBeSpawned = allEnemies ? N_ENEMIES : index;
    int bonusesToBeSpawned = allBonuses ? N_BONUSES : index;
    int currentPlatforms = index > N_PLATFORMS ? N_PLATFORMS : index;
    int turretIndex = 0, enemyIndex = 0, bonusIndex = 0;
    int enemiesDamage = MIN_DAMAGE > index ? MIN_DAMAGE : (MAX_DAMAGE < index ? MAX_DAMAGE : index);
    for(int i = 0; i < currentPlatforms; i++)
    {
        //if(all turrets should be built and I have the same number of platforms as turrets) or if(all turrets should be built but the number of platforms allows for the current platform not to have a turret and random chance) or if(not all turrets should be built and therefore the turrets to be built equals the number of platforms) and in all these cases IF the turrets already built are less than the total to be built then build turret at current platform level
        if(((allTurrets && currentPlatforms - i <= turretsToBeBuilt) || (allTurrets && currentPlatforms - i > turretsToBeBuilt && randomInRange(1, 10) > 7 || !allTurrets)) && turretsBuilt < turretsToBeBuilt)
        {
            if(randomInRange(1, 10) > 5)
            {
                turrets[turretIndex] = new Turret(1, platforms[i]->getY() - 1, true, '>');
            }
            else
            {
                turrets[turretIndex] = new Turret(this->width - 1, platforms[i]->getY() - 1, true, '<');
            }
            turretIndex++;
            turretsBuilt++;
        }
        if(((allEnemies && currentPlatforms - i <= enemiesToBeSpawned) || (allEnemies && currentPlatforms - i > enemiesToBeSpawned && randomInRange(1, 10) > 3 || !allEnemies)) && enemiesSpawned < enemiesToBeSpawned)
        {
            int enemiesDirection = randomInRange(1, 10) > 5 ? 1 : -1;
            enemies[enemyIndex] = new Enemy(randomInRange(platforms[i]->getStartingPointX(), platforms[i]->getEndingPointX()), platforms[i]->getY() - 1, enemiesDirection, enemiesDamage, '@');
            enemyIndex++;
            enemiesSpawned++;
        }
        if(((allBonuses && currentPlatforms - i <= bonusesToBeSpawned) || (allBonuses && currentPlatforms - i > bonusesToBeSpawned && randomInRange(1, 10) > 8 || !allBonuses)) && bonusesSpawned < bonusesToBeSpawned)
        {
            char bonusType = randomInRange(1, 10) > 8 ? 'h' : 'p';
            int bonusEffect;
            if(bonusType == 'h')
            {
                bonusEffect = index > MAX_HEALTHBONUS ? MAX_HEALTHBONUS : index;
            }
            else
            {
                bonusEffect = index / 3;
            }
            bonuses[bonusIndex] = new Bonus(randomInRange(platforms[i]->getStartingPointX(), platforms[i]->getEndingPointX()), platforms[i]->getY() - 1, bonusType, bonusEffect);
            bonusIndex++;
            bonusesSpawned++;
        }
    }
}

int Level::getWidth()
{
    return this->width;
}

int Level::getHeight()
{
    return this->height;
}

void Level::drawLevel(Player player, int index)
{
    char spaces[100] = "";
    for(int i = 0; i < width + 1; i++)
    {
        strcat(spaces, " ");
    }
    printw("%sPoints: %d\n%sHealth: %d", spaces, player.getPoints(), spaces, player.getHealth());
    drawBorders(index);
    for(int i = 0; i < N_PLATFORMS && platforms[i] != NULL; i++)
    {
        platforms[i]->print();
    }
    for(int i = 0; i < N_BONUSES && bonuses[i] != NULL; i++)
    {
        if(bonuses[i]->getExistence())
        {
            bonuses[i]->print();
        }
    }
    for(int i = 0; i < N_ENEMIES && enemies[i] != NULL; i++)
    {
        if(enemies[i]->getExistence())
        {
            enemies[i]->print();
        }
    }
    for(int i = 0; i < N_TURRETS && turrets[i] != NULL; i++) //Doesn't check for existence because turrets can't be destroyed
    {
        turrets[i]->printBullet();
        turrets[i]->print();
    }
    player.print();
}

void Level::updateLevel()
{
    bool turretsUpdated = false, enemiesUpdated = false;
    if(turretsUpdate.updateCounter % turretsUpdate.updateTime == 0)
    {
        for(int i = 0; i < N_TURRETS && turrets[i] != NULL; i++)
        {
            turrets[i]->updateBullet();
            if((turrets[i]->getBulletX() == 0 && turrets[i]->getBulletDirection() == -1) || (turrets[i]->getBulletX() == this->width && turrets[i]->getBulletDirection() == 1))
            {
                turrets[i]->resetBullet();
            }
        }
        turretsUpdated = true;
    }
    if(enemiesUpdate.updateCounter % enemiesUpdate.updateCounter == 0)
    {
        int correspondingPlatformIndex;
        for(int i = 0; i < N_ENEMIES && enemies[i] != NULL; i++)
        {
            if(enemies[i]->getExistence())
            {
                correspondingPlatformIndex = 0;
                while(correspondingPlatformIndex < N_PLATFORMS && platforms[correspondingPlatformIndex] != NULL && enemies[i]->getY() != platforms[correspondingPlatformIndex]->getY() - 1) //finds enemy's corresponding platform, possible function
                {
                    correspondingPlatformIndex++;
                }
                if(platforms[correspondingPlatformIndex]->getStartingPointX() > enemies[i]->getXAfterMove() || platforms[correspondingPlatformIndex]->getEndingPointX() < enemies[i]->getXAfterMove())
                {
                    enemies[i]->reverseDirection();
                }
                else
                {
                    enemies[i]->move();
                }
            }
        }
        enemiesUpdated = true;
    }
    if(turretsUpdated)
    {
        turretsUpdate.updateCounter = 0;
    }
    else
    {
        turretsUpdate.updateCounter++;
    }
    if(enemiesUpdated)
    {
        enemiesUpdate.updateCounter = 0;
    }
    else
    {
        enemiesUpdate.updateCounter++;
    }
}

int Level::isPlayerAtBorder()
{

}

void Level::exitLevel(int index)
{
    for(int i = 0; i < N_TURRETS && turrets[i] != NULL; i++)
    {
        turrets[i]->resetBullet();
    }
}

int Level::findTurretIndex(Player *player)
{
    int turretIndex = 0;
    bool turretPresent = false;
    while(turretIndex < N_TURRETS && turrets[turretIndex] != NULL && !turretPresent)
    {
        if(turrets[turretIndex]->getY() == player->getY())
        {
            turretPresent = true;
        }
        if(!turretPresent)
        {
            turretIndex++;
        }
    } //FINDTURRETINDEX FUNC
    int index = turretPresent ? turretIndex : -1;
    return index;
}

int Level::findEnemyIndex(Player *player)
{
    bool enemyPresent = false;
    int enemyIndex = 0;
    while(enemyIndex < N_ENEMIES && enemies[enemyIndex] != NULL && !enemyPresent)
    {
        if(enemies[enemyIndex]->getY() == player->getY())
        {
            enemyPresent = true;
        }
        if(!enemyPresent)
        {
            enemyIndex++;
        }
    }
    int index = enemyPresent ? enemyIndex : -1;
    return index;
}

void Level::playerUpdate(Player *player, int keyPressed, int index)
{
    bool sideMove = keyPressed == ERR ? false : true; //if nothing is pressed then there is no move, so the move is not a side move
    bool changedPlatform = false; //Useful for enemy kill

    //determine what platform the player is on
    int currentPlatforms = index > N_PLATFORMS ? N_PLATFORMS : index;
    int heightIndex = this->height - 1, platformIndex = -1;
    while(player->getY() != heightIndex)
    {
        heightIndex -= 2;
        platformIndex++;
    }

    //Handle vertical moves
    if(keyPressed == 'w' && platformIndex + 1 < currentPlatforms) //Useless to check for upper platforms if player is at the top (platformIndex + 1 because platformIndex starts from 0)
    {
        if(player->getX() >= platforms[platformIndex + 1]->getStartingPointX() && player->getX() <= platforms[platformIndex + 1]->getEndingPointX())
        {
            player->move(keyPressed);
            player->move(keyPressed);
            changedPlatform = true;
        }
        sideMove = false;
    }
    else if(keyPressed == 's' && platformIndex > -1) //Useless to check for platforms under player if player is not on a platform (platformIndex > -1 because platformIndex starts indicating that some surface exists under the player from the value 0 on)
    {
        bool allowedDownMove = false;
        if(platformIndex == 0) //If at first platform, player can always go down
        {
            allowedDownMove = true;
        }
        else if((player->getX() >= platforms[platformIndex - 1]->getStartingPointX() && player->getX() <= platforms[platformIndex - 1]->getEndingPointX()))
        {
            allowedDownMove = true;
        }
        if(allowedDownMove)
        {
            player->move(keyPressed);
            player->move(keyPressed);
            changedPlatform = true;
        }
        sideMove = false;
    }

    //Check if side move is legal
    bool sideMoveIsLegal = true; //Not legal => player will not move to the left or right
    int playerXAfterMove = player->getXAfterMove(keyPressed);
    if(platformIndex != -1 && (playerXAfterMove == width || playerXAfterMove == 0 || platforms[platformIndex]->getStartingPointX() > playerXAfterMove || platforms[platformIndex]->getEndingPointX() < playerXAfterMove)) //Checks if player is on a platform (therefore subject to possible bullet/enemy collisions) and if the move will result in not moving, which is true only if the player is trying to get off the platform without using KEY_DOWN/s/S or if it is at a map border
    {
        sideMoveIsLegal = false;
    }

    int currentBulletDirection;
    int turretIndex = (platformIndex == -1 && !changedPlatform) ? -1 : findTurretIndex(player); //Condition
    
    //First bullet collision check
    if(turretIndex != -1)
    {
        currentBulletDirection = turrets[turretIndex]->getBulletDirection();
        if(turrets[turretIndex]->isBulletColliding(*player))
        {
            if((currentBulletDirection == 1 && keyPressed != 'd') || (currentBulletDirection == -1 && keyPressed != 'a') || !sideMoveIsLegal)
            {
                turrets[turretIndex]->hitPlayer(player);
                turrets[turretIndex]->resetBullet();
            }
        }
    }

    //Check what sideMove will change
    int xChange = sideMove ? (sideMoveIsLegal ? (abs(player->getX() - player->getXAfterMove(keyPressed))) : 0) : 0; //If the move is not a side move then there will be no change in the x coordinate of the player

    int currentEnemyDirection;
    int enemyIndex = (platformIndex == -1 && !changedPlatform) ? -1 : findEnemyIndex(player);

    //First enemy collision check
    if(enemyIndex != -1)
    {
        currentEnemyDirection = enemies[enemyIndex]->getDirection();
        if(enemies[enemyIndex]->getExistence() && enemies[enemyIndex]->isColliding(*player))
        {
            if(((currentEnemyDirection == 1 && keyPressed != 'd') || (currentEnemyDirection == -1 && keyPressed != 'a') || !sideMoveIsLegal) && !changedPlatform)
            {
                enemies[enemyIndex]->hitPlayer(player);
            }
            else if(changedPlatform)
            {
                enemies[enemyIndex]->deactivate();
            }
        }
    }
    
    //Player move
    if(sideMoveIsLegal && keyPressed == 'd')
    {
        player->move('d');
    }
    else if(sideMoveIsLegal && keyPressed == 'a')
    {
        player->move('a');
    }

    //Second bullet collision check
    if(turretIndex != -1)
    {
        currentBulletDirection = turrets[turretIndex]->getBulletDirection();
        if(turrets[turretIndex]->isBulletColliding(*player))
        {
            turrets[turretIndex]->hitPlayer(player);
            turrets[turretIndex]->resetBullet();
        }
    }

    //Second enemy collision check
    if(enemyIndex != -1)
    {
        currentEnemyDirection = enemies[enemyIndex]->getDirection();
        if(enemies[enemyIndex]->getExistence() && enemies[enemyIndex]->isColliding(*player))
        {
            enemies[enemyIndex]->hitPlayer(player);
        }
    }

    //Bonus check
    int bonusIndex = 0;
    while(bonusIndex < N_BONUSES && bonuses[bonusIndex] != NULL && !(platformIndex == -1 && !changedPlatform))
    {
        if(bonuses[bonusIndex]->getExistence() && bonuses[bonusIndex]->isColliding(*player))
        {
            bonuses[bonusIndex]->use(player);
        }
        bonusIndex++;
    }
}
