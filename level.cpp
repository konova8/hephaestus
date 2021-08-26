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
    //cout << "IE1" << endl;
    for(int i = 0; i < N_PLATFORMS; i++)
    {
        platforms[i] = NULL;
    }
    //cout << "IE2" << endl;
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
    //cout << "IE3" << endl;
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
    //cout << "SPBEG" << endl;
    int platformsToBuild = index > N_PLATFORMS ? N_PLATFORMS : index;
    int startingX = -1, y = this->height - 2, endingX = -1;
    //cout << "SP1, platformsToBuild: " << platformsToBuild << endl << "y: " << y << endl;
    for(int i = 0; i < platformsToBuild; i++)
    {
        if(i == 0)
        {
            startingX = randomInRange(5, width - 5);
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
        //cout << "CHOSEN STARTING X: " << startingX << " ENDINGX: " << endingX << endl;
        if(startingX < width / 2)
        {
            //cout << "SPI1" << endl;
            do
            {
                endingX = randomInRange(startingX, 35);
                //cout << "CHOSEN ENDING X1: " << endingX << endl;
            }
            while(endingX == startingX);
        }
        else
        {
            //cout << "SPI2" << endl;
            do
            {
                endingX = randomInRange(5, startingX);
                //cout << "CHOSEN ENDING X2: " << endingX << endl;
            }
            while(endingX == startingX);
        }
        platforms[i] = new Platform(startingX, endingX, y, '=');
        //std::cout << "---------------\nSTARTINGX: " << platforms[i]->getStartingPointX() << "\nENDINGX: " << platforms[i]->getEndingPointX() << "\nY: " << platforms[i]->getY() << "\n---------------" << std::endl;
        y -= 2;
    }
    //cout << platforms[0]->getY() << endl;
    //cout << "SPEND" << endl;
}

void Level::setEntities(int index)
{
    //cout << "SEBEG" << endl;
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
    //cout << "SE1: allTurrets: " << allTurrets << endl << "allEnemies: " << allEnemies << endl << "allBonuses: " << allBonuses << endl;
    //cout << "SE2: turretsTBB: " << turretsToBeBuilt << endl << "enemiesTBS: " << enemiesToBeSpawned << endl << "bonusesTBS: " << bonusesToBeSpawned << endl << "currentPlatforms: " << currentPlatforms << endl << "enemiesDamage: " << enemiesDamage << endl; 
    for(int i = 0; i < currentPlatforms; i++)
    {
        //cout << "NNNNNNNNNNNNNNNNNNNN\n<<<<<<<<<<<<<<<<<<<<<\ni: " << i << endl << "currentPlatforms: " << currentPlatforms << endl << "currentPlatforms - i: " << currentPlatforms - i << endl << "<<<<<<<<<<<<<<<<<<<<<" << endl;
        //if(all turrets should be built and I have the same number of platforms as turrets) or if(all turrets should be built but the number of platforms allows for the current platform not to have a turret and random chance) or if(not all turrets should be built and therefore the turrets to be built equals the number of platforms) and in all these cases IF the turrets already built are less than the total to be built then build turret at current platform level
        if(((allTurrets && currentPlatforms - i <= turretsToBeBuilt) || (allTurrets && currentPlatforms - i > turretsToBeBuilt && randomInRange(1, 10) > 7 || !allTurrets)) && turretsBuilt < turretsToBeBuilt)
        {
            if(randomInRange(1, 10) > 5)
            {
                //cout << "GENERATING NEW TURRET SX" << endl;
                turrets[turretIndex] = new Turret(1, platforms[i]->getY() - 1, true, '>');
            }
            else
            {
                //cout << "GENERATING NEW TURRET DX" << endl;
                turrets[turretIndex] = new Turret(this->width - 1, platforms[i]->getY() - 1, true, '<');
            }
            turretIndex++;
            turretsBuilt++;
            //cout << "NEW TURERT COUNTS{ turretsTBB: " << turretsToBeBuilt << " turretsBuilt: " << turretsBuilt << endl;
        }
        if(((allEnemies && currentPlatforms - i <= enemiesToBeSpawned) || (allEnemies && currentPlatforms - i > enemiesToBeSpawned && randomInRange(1, 10) > 3 || !allEnemies)) && enemiesSpawned < enemiesToBeSpawned)
        {
            //cout << "GENERATING NEW ENEMY" << endl;
            int enemiesDirection = randomInRange(1, 10) > 5 ? 1 : -1;
            enemies[enemyIndex] = new Enemy(randomInRange(platforms[i]->getStartingPointX(), platforms[i]->getEndingPointX()), platforms[i]->getY() - 1, enemiesDamage, enemiesDirection, '@');
            enemyIndex++;
            enemiesSpawned++;
            //cout << "NEW ENEMY COUNTS{ enemiesTBS: " << enemiesToBeSpawned << " enemiesSpawned: " << enemiesSpawned << endl;
        }
        if(((allBonuses && currentPlatforms - i <= bonusesToBeSpawned) || (allBonuses && currentPlatforms - i > bonusesToBeSpawned && randomInRange(1, 10) > 8 || !allBonuses)) && bonusesSpawned < bonusesToBeSpawned)
        {
            char bonusType = randomInRange(1, 10) > 8 ? 'h' : 'p';
            //cout << "BONUSTYPE: " << bonusType << endl;
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
        //cout << "||||||||||||||||||||||||" << endl;
    }
    //cout << "SEEND" << endl;
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
    //cout << "DL1" << endl;
    for(int i = 0; i < width + 1; i++)
    {
        strcat(spaces, " ");
    }
    printw("%sPoints: %d\n%sHealth: %d", spaces, player.getPoints(), spaces, player.getHealth());
    drawBorders(index);
    //cout << "DL2" << endl;
    for(int i = 0; i < N_PLATFORMS && platforms[i] != NULL; i++)
    {
        platforms[i]->print();
    }
    //cout << "DL3" << endl;
    for(int i = 0; i < N_TURRETS && turrets[i] != NULL; i++)
    {
        turrets[i]->print();
    }
    //cout << "DL4" << endl;
    for(int i = 0; i < N_ENEMIES && enemies[i] != NULL; i++)
    {
        enemies[i]->print();
    }
    //cout << "DL5" << endl;
    for(int i = 0; i < N_BONUSES && bonuses[i] != NULL; i++)
    {
        bonuses[i]->print();
    }
    //cout << "DL6" << endl;
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
        }
        turretsUpdate = true;
    }
    if(enemiesUpdate.updateCounter % enemiesUpdate.updateCounter == 0)
    {
        int correspondingPlatformIndex;
        for(int i = 0; i < N_ENEMIES && enemies[i] != NULL; i++)
        {
            correspondingPlatformIndex = 0;
            while(correspondingPlatformIndex < N_PLATFORMS && platforms[i] != NULL && enemies[i]->getY() != platforms[correspondingPlatformIndex]->getY() + 1) //finds enemy's corresponding platform, possible function
            {
                correspondingPlatformIndex++;
            }
            if(platforms[correspondingPlatformIndex]->getStartingPointX() >= enemies[i]->getX() || platforms[correspondingPlatformIndex]->getEndingPointX() <= enemies[i]->getX())
            {
                enemies[i]->reverseDirection();
            }
            else
            {
                enemies[i]->move();
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

void Level::playerUpdate(Player *player, int keyPressed, int index)
{
    bool changedPlatform = false; //Useful for enemy kill
    //determine what platform the player is on
    int currentPlatforms = index > N_PLATFORMS ? N_PLATFORMS : index;
    int heightIndex = this->height - 1, platformIndex = -1;
    while(player->getY() != heightIndex)
    {
        heightIndex += 2;
        platformIndex++;
    } //CREATE PLATFORMON(SINGLEBLOCKENTITY ENTITY) FUNC
    if((keyPressed == 'w' || keyPressed == 'W' || keyPressed == KEY_UP) && platformIndex < currentPlatforms) //Useless to check for upper platforms if player is at the top
    {
        if(player->getX() >= platforms[platformIndex + 1]->getStartingPointX() && player->getX() <= platforms[platformIndex + 1]->getEndingPointX())
        {
            player->move(keyPressed);
            player->move(keyPressed);
            changedPlatform = true;
        }
    }
    else if((keyPressed == 's' || keyPressed == 'S' || keyPressed == KEY_DOWN) && platformIndex > 0) //Useless to check for platforms under player if player is not on a platform
    {
        if((player->getX() >= platforms[platformIndex - 1]->getStartingPointX() && player->getX() <= platforms[platformIndex - 1]->getEndingPointX()))
        {
            player->move(keyPressed);
            player->move(keyPressed);
            changedPlatform = true;
        }
    }

    //check if move legal
    bool sideMoveIsLegal = true; //(not legal => player will not move to the left or right) <=> legal checks for right and left moves at border
    int playerXAfterMove = player->getXAfterMove(keyPressed);
    if(platformIndex != -1 && (playerXAfterMove == width || playerXAfterMove == 0 || platforms[platformIndex]->getStartingPointX() > playerXAfterMove || platforms[platformIndex]->getEndingPointX() < playerXAfterMove)) //Checks if player is on a platform (therefore subject to possible bullet collisions) and if the move will result in not moving, which is true only if the player is trying to get off the platform without using KEY_DOWN/s/S or if it is at a map border //REMEMBER TO CREATE NEW BOOL FUNCS FOR BOTH BORDER AND PLATFORM CONDITIONS (ALREADY DECLARED)
    {
        sideMoveIsLegal = false;
    }

    //Handles cases of bullet collision
    int turretIndex = 0;
    int currentBulletDirection;
    while(turretIndex < N_TURRETS && turrets[turretIndex] != NULL)
    {
        currentBulletDirection = turrets[turretIndex]->getBulletDirection();
        if(turrets[turretIndex]->isBulletColliding(*player))
        {
            if((currentBulletDirection == 1 && keyPressed != 'd') || (currentBulletDirection == -1 && keyPressed != 'a') || !sideMoveIsLegal)
            {
                player->deactivate();
            }
        }
        turretIndex++;
    }

    //Handles cases of enemy collision
    int enemyIndex = 0;
    int currentEnemyDirection;
    while(enemyIndex < N_ENEMIES && enemies[enemyIndex] != NULL)
    {
        currentEnemyDirection = enemies[enemyIndex]->getDirection();
        if(enemies[enemyIndex]->isColliding(*player))
        {
            if(((currentEnemyDirection == 1 && keyPressed != 'd') || (currentEnemyDirection == -1 && keyPressed != 'a') || !sideMoveIsLegal) && !changedPlatform)
            {
                player->deactivate();
            }
            else if(changedPlatform)
            {
                enemies[enemyIndex]->deactivate();
            }
        }
    }
    
    if(sideMoveIsLegal && keyPressed == 'd')
    {
        player->move('d');
    }
    else if(sideMoveIsLegal && keyPressed == 'a')
    {
        player->move('a');
    }
}