#include "level.hpp"
#include <cstdlib>
#include <ncurses.h>
#include <string.h>

using namespace std;

Level::Level(int index)
{
    this->width = 40;
    this->height = 15;
    this->turretsUpdate.updateTime = 20 - index < MIN_BULLET_UPDATE ? MIN_BULLET_UPDATE : 20 - index;
    this->enemiesUpdate.updateTime = 20 - index < MIN_ENEMY_UPDATE ? MIN_ENEMY_UPDATE : 20 - index;
    this->needsDraw = true;
    for(int i = 0; i < width + 1; i++) //Creates the space needed to print statistics based on the level width
    {
        strcat(this->spaces, " ");
    }
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
            mvaddch(i, 0, 'E');
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
        //If i == 0, then the x starting point of the platform can be everywhere
        if(i == 0)
        {
            startingX = randomInRange(10, width - 10);
        }
        /* If i != 0, then the x starting point of the platform must be
        /* between the x starting and ending point of the last platform built
        /* This allows for the player to be on a platform and always be able to reach the
        /* one under and on top of it
        */
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
        //If the x starting point is in the left part of the level, the ending point will be to its right
        if(startingX < width / 2)
        {
            do
            {
                endingX = randomInRange(startingX, this->width - 5 - minimumLength) + minimumLength;
            }
            while(endingX == startingX);
        }
        //If the x starting point is in the right part of the level, the ending point will be to its left
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

bool Level::entityGenerationCheck(bool allEntities, int remainingPlatforms, int entitiesSpawned, int entitiesToBeSpawned, int chance)
{
    /* The entities generation is designed in a way that makes the entities
    /* able to spawn on every platform (with only one entity of each type per platform max)
    /* but with different probabilities, the following conditions allow to do what was
    /* just explained
    /* 
    /* 
    /* Entity generation check conditions
    /*
    /* (allEntities && remainingPlatforms <= entitiesToBeSpawned)
    /* If this condition is
    /* true then all entities should be built and the number of platforms doesn't
    /* allow for one entity not to be spawned in the current one. If it were to allow
    /* it, then the final number of entities spawned would be less than the number of
    /* entities to be spawned.
    /*
    /* (allEntities && remainingPlatforms > entitiesToBeSpawned && randomInRange(1, 10) > chance || !allEntities)
    /* If this condition is true, then we have two cases:
    /* 1) !allEntities --> If not all entities should be built, then the condition is true and the entity will be built,
    /*    because in every level where this condition is true the number of platforms is equal to the number of that type
    /*    of entities to be spawned, which means that every platform should have one entity of that type on itself.
    /* 2) allEntities && remainingPlatforms > entitiesToBeSpawned && randomInRange(1, 10) > chance
    /*    If this condition is true, then the max number of entities should be built but the current number
    /*    of remaining platforms allows for the current platform not to have a entity of that type on itself.
    /*    randomInRange(1, 10) > chance is used to generate randomness in the levels and not make all entities
    /*    spawn at the top platforms
    /* 
    /* In all of these cases, another condition must be satisfied: entitiesSpawned < entitiesToBeSpawned, which is self explanatory.
    /* 
    */
    bool generate = false;
    if(((allEntities && remainingPlatforms <= entitiesToBeSpawned) || (allEntities && remainingPlatforms > entitiesToBeSpawned && randomInRange(1, 10) > chance || !allEntities)) && entitiesSpawned < entitiesToBeSpawned)
    {
        generate = true;
    }
    return generate;

}

void Level::setEntities(int index)
{
    int turretsBuilt = 0, enemiesSpawned = 0, bonusesSpawned = 0;
    int turretIndex = 0, enemyIndex = 0, bonusIndex = 0;

    bool allTurrets = index > N_TURRETS; //Indicates if all the possible turrets should be built
    bool allEnemies = index > N_ENEMIES; //Indicates if all the possible enemies should be spawned
    bool allBonuses = index > N_BONUSES; //Indicates if all the possible bonuses should be spawned

    int turretsToBeBuilt = allTurrets ? N_TURRETS : index; //Indicates the number of turrets to build
    int enemiesToBeSpawned = allEnemies ? N_ENEMIES : index; //Indicates the number of enemies to spawn
    int bonusesToBeSpawned = allBonuses ? N_BONUSES : index; //Indicates the number of bonuses to spawn
    int currentPlatforms = index > N_PLATFORMS ? N_PLATFORMS : index; //Indicates number of platforms in the current level

    //Indicates the damage each enemy should be assigned in the current level
    int enemiesDamage = MIN_DAMAGE > index ? MIN_DAMAGE : (MAX_DAMAGE < index ? MAX_DAMAGE : index);
    
    //For each platform, each entity will have a chance to spawn (therefore, there will always be at most only one entity of each type on a platform)
    for(int i = 0; i < currentPlatforms; i++)
    {
        if(entityGenerationCheck(allTurrets, currentPlatforms - i, turretsBuilt, turretsToBeBuilt, 7))
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
        if(entityGenerationCheck(allEnemies, currentPlatforms - i, enemiesSpawned, enemiesToBeSpawned, 3))
        {
            int enemiesDirection = randomInRange(1, 10) > 5 ? 1 : -1;
            enemies[enemyIndex] = new Enemy(randomInRange(platforms[i]->getStartingPointX(), platforms[i]->getEndingPointX()), platforms[i]->getY() - 1, enemiesDirection, enemiesDamage, '@');
            enemyIndex++;
            enemiesSpawned++;
        }
        if(entityGenerationCheck(allBonuses, currentPlatforms - i, bonusesSpawned, bonusesToBeSpawned, 8))
        {
            char bonusType = randomInRange(1, 10) > 2 ? 'p' : 'h';
            int bonusEffect;
            if(bonusType == 'h')
            {
                bonusEffect = index > MAX_HEALTHBONUS ? MAX_HEALTHBONUS : (index < MIN_HEALTHBONUS ? MIN_HEALTHBONUS : index);
            }
            else
            {
                bonusEffect = index / 3 < MIN_POINTSBONUS ? MIN_POINTSBONUS : index / 3;
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
    if(needsDraw)
    {
        clear();
        printw("%sPoints: %d\n%sHealth: %d\n%sLevel: %d", this->spaces, player.getPoints(), this->spaces, player.getHealth(), this->spaces, index);
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
        for(int i = 0; i < N_TURRETS && turrets[i] != NULL; i++)
        {
            //Doesn't check for existence because turrets can't be destroyed
            turrets[i]->printBullet();
            turrets[i]->print();
        }
        player.print();
        needsDraw = false;
    }
}

void Level::updateLevel()
{
    bool turretsUpdated = false, enemiesUpdated = false;
    
    //Update bullets
    if(turretsUpdate.updateCounter % turretsUpdate.updateTime == 0)
    {
        for(int i = 0; i < N_TURRETS && turrets[i] != NULL; i++)
        {
            turrets[i]->updateBullet();

            //If the bullet is at its border, then reset it
            if((turrets[i]->getBulletX() == 0 && turrets[i]->getBulletDirection() == -1) || (turrets[i]->getBulletX() == this->width && turrets[i]->getBulletDirection() == 1))
            {
                turrets[i]->resetBullet();
            }
        }
        turretsUpdated = true;
    }
    if(enemiesUpdate.updateCounter % enemiesUpdate.updateTime == 0)
    {
        int correspondingPlatformIndex;
        for(int i = 0; i < N_ENEMIES && enemies[i] != NULL; i++)
        {
            //Only update enemy if it has not been killed
            if(enemies[i]->getExistence())
            {
                correspondingPlatformIndex = 0;
                
                //Find index of the platform the enemy is on
                while(correspondingPlatformIndex < N_PLATFORMS && platforms[correspondingPlatformIndex] != NULL && enemies[i]->getY() != platforms[correspondingPlatformIndex]->getY() - 1)
                {
                    correspondingPlatformIndex++;
                }

                //Reverse the direction of the enemy if it is going out of the platform
                if(platforms[correspondingPlatformIndex]->getStartingPointX() > enemies[i]->getXAfterMove() || platforms[correspondingPlatformIndex]->getEndingPointX() < enemies[i]->getXAfterMove())
                {
                    enemies[i]->reverseDirection();
                }
                //Otherwise move the enemy
                else
                {
                    enemies[i]->move();
                }
            }
        }
        enemiesUpdated = true;
    }

    //Time control
    if(turretsUpdated)
    {
        turretsUpdate.updateCounter = 1;
    }
    else
    {
        turretsUpdate.updateCounter++;
    }
    if(enemiesUpdated)
    {
        enemiesUpdate.updateCounter = 1;
    }
    else
    {
        enemiesUpdate.updateCounter++;
    }

    //If the enemies or the bullets were updated, a redraw is needed
    if(enemiesUpdated || turretsUpdated)
    {
        this->needsDraw = true;
    }
    else
    {
        this->needsDraw = false;
    }
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
    }
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
    bool sideMove = keyPressed == ERR ? false : true; //If nothing is pressed then there is no move, so the move is not a side move.
    bool changedPlatform = false; //Needed to determine when to kill an enemy.

    //Determine what platform the player is on.
    int currentPlatforms = index > N_PLATFORMS ? N_PLATFORMS : index;
    int heightIndex = this->height - 1, platformIndex = -1;
    while(player->getY() != heightIndex)
    {
        heightIndex -= 2;
        platformIndex++;
    }

    //Handle and perform vertical moves
    if(keyPressed == 'w' && platformIndex + 1 < currentPlatforms) //Useless to check for upper platforms if player is at the top
    {
        //Check if the block at the top of the player belongs to the platform at the top of the player. If it does, perform the move.
        if(player->getX() >= platforms[platformIndex + 1]->getStartingPointX() && player->getX() <= platforms[platformIndex + 1]->getEndingPointX())
        {
            player->move(keyPressed);
            player->move(keyPressed);
            changedPlatform = true;
            needsDraw = true;
        }
        sideMove = false;
    }
    else if(keyPressed == 's' && platformIndex > -1) //Useless to check for platforms under player if player is not on the ground
    {
        bool allowedDownMove = false;

        //If at first platform, the player can always go down
        if(platformIndex == 0)
        {
            allowedDownMove = true;
        }

        //Otherwise, check if the block under the player belongs to the platform under the player.
        else if((player->getX() >= platforms[platformIndex - 1]->getStartingPointX() && player->getX() <= platforms[platformIndex - 1]->getEndingPointX()))
        {
            allowedDownMove = true;
        }

        //If the move is allowed, perform it
        if(allowedDownMove)
        {
            player->move(keyPressed);
            player->move(keyPressed);
            changedPlatform = true;
            needsDraw = true;
        }
        sideMove = false;
    }

    //Check if side move is legal
    bool platformSideMoveLegal = true; //Not legal => player will not move to the left or right
    int playerXAfterMove = player->getXAfterMove(keyPressed);

    if(platformIndex != -1 && //If the player is on the ground, don't check for legality of platform side move, next conditions assume the player is on a platform
    (playerXAfterMove == width || //If the x after the move is the width, the move is illegal
    playerXAfterMove == 0 || //If the x after the move is 0, the move is illegal
    platforms[platformIndex]->getStartingPointX() > playerXAfterMove //If the x after the move is not on the platform, the move is illegal
    || platforms[platformIndex]->getEndingPointX() < playerXAfterMove)) //If the x after the move is not on the platform, the move is illegal
    {
        platformSideMoveLegal = false;
    }

    int currentBulletDirection;

    /* A value of -1 of turretIndex indicates there is no turret at the current y of the player
    /*
    /* If platformIndex before a up/down move is -1 and the platform has not changed
    /* then the player is on the ground, therefore there can not be a turret at its current y
    /*
    /* Otherwise, find the turret index of the turret at the y of the player and assign it
    /* to turretIndex
    /* 
    /* enemyIndex assignment is completely analogous.
    */
    int turretIndex = (platformIndex == -1 && !changedPlatform) ? -1 : findTurretIndex(player);
    
    /* First bullet collision check
    /*
    /* This collision check is for the case where a bullet
    /* is colliding with the player, but the player's side
    /* side move has not been performed yet, provided
    /* the move was actually a side move, in the other case,
    /* if the move was a up/down move, then it has already
    /* been performed
    /*
    /* There are therefore two cases, the first one being
    /* the player has made a side move, that has not yet been
    /* performed, that allows him to escape the bullet
    /*
    /* In the other case the move goes in the opposite
    /* direction of the bullet, making the two entities
    /* collide
    /*
    /* The first collision check for the enemies
    /* is completely analogous
    */
    if(turretIndex != -1)
    {
        currentBulletDirection = turrets[turretIndex]->getBulletDirection();
        if(turrets[turretIndex]->isBulletColliding(*player))
        {
            if((currentBulletDirection == 1 && keyPressed != 'd') || (currentBulletDirection == -1 && keyPressed != 'a') || !platformSideMoveLegal)
            {
                turrets[turretIndex]->hitPlayer(player);
                turrets[turretIndex]->resetBullet();
                needsDraw = true;
            }
        }
    }

    int currentEnemyDirection;
    int enemyIndex = (platformIndex == -1 && !changedPlatform) ? -1 : findEnemyIndex(player);

    //First enemy collision check
    if(enemyIndex != -1)
    {
        currentEnemyDirection = enemies[enemyIndex]->getDirection();
        if(enemies[enemyIndex]->getExistence() && enemies[enemyIndex]->isColliding(*player))
        {
            if(((currentEnemyDirection == 1 && keyPressed != 'd') || (currentEnemyDirection == -1 && keyPressed != 'a') || !platformSideMoveLegal) && !changedPlatform)
            {
                enemies[enemyIndex]->hitPlayer(player);
                needsDraw = true;
            }
            else if(changedPlatform)
            {
                enemies[enemyIndex]->deactivate();
                int toDivideBy = index < 5 ? 1 : (index > 100 ? 4 : 2);
                player->pointsChange((index * 5) / toDivideBy);
                needsDraw = true;
            }
        }
    }

    //Perform player side move
    if(platformSideMoveLegal && keyPressed == 'd')
    {
        player->move('d');
        needsDraw = true;
    }
    else if(platformSideMoveLegal && keyPressed == 'a')
    {
        player->move('a');
        needsDraw = true;
    }

    /* Second bullet collision check
    /*
    /* The second bullet collision check allows to check
    /* for the case where the bullet and the player are
    /* colliding after the player has performed a side move
    /*
    /* It's a simple matter of checking if the x and the y of
    /* the two entities are the same.
    /* 
    /* The second enemy collision check is completely analogous
    */
    if(turretIndex != -1)
    {
        currentBulletDirection = turrets[turretIndex]->getBulletDirection();
        if(turrets[turretIndex]->isBulletColliding(*player))
        {
            turrets[turretIndex]->hitPlayer(player);
            turrets[turretIndex]->resetBullet();
            needsDraw = true;
        }
    }

    //Second enemy collision check
    if(enemyIndex != -1)
    {
        currentEnemyDirection = enemies[enemyIndex]->getDirection();
        if(enemies[enemyIndex]->getExistence() && enemies[enemyIndex]->isColliding(*player))
        {
            enemies[enemyIndex]->hitPlayer(player);
            needsDraw = true;
        }
    }

    //Bonus check
    int bonusIndex = 0;
    while(bonusIndex < N_BONUSES && bonuses[bonusIndex] != NULL && !(platformIndex == -1 && !changedPlatform))
    {
        if(bonuses[bonusIndex]->getExistence() && bonuses[bonusIndex]->isColliding(*player))
        {
            bonuses[bonusIndex]->use(player);
            needsDraw = true;
        }
        bonusIndex++;
    }
}

int Level::isPlayerAtBorder(Player player)
{
    int result = 0;
    if(player.getY() == height - 1)
    {
        if(player.getX() == 0)
        {
            result = -1;
        }
        else if(player.getX() == width)
        {
            result = 1;
        }
    }
    return result;
}
