#include "level.hpp"
#include <iostream> //Testing purposes, will remove later
#include <cstdlib>
#include <ncurses.h>
#include <string.h>

Level::Level(int index)
{
    this->width = 40;
    this->height = 15;
    turretsUpdate.updateTime = 20 - index < MIN_UPDATE ? MIN_UPDATE : index - 20;
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
    return rand() % (max - min + 1) + min;
}

void Level::initializeEntitiesLists()
{
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
        if(i == this->height - 1 && index != 0)
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
    int startingX, y = height - 1, endingX;
    for(int i = 0; i < platformsToBuild; i++)
    {
        if(i == 0)
        {
            startingX = randomInRange(5, width - 1);
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
            endingX = randomInRange(startingX, 35);
        }
        else
        {
            endingX = randomInRange(5, startingX);
        }
        y -= 2;
        //platforms[i] = new Platform(startingX, endingX, y, '=');
        //std::cout << "---------------\nSTARTINGX: " << startingX << "\nENDINGX: " << endingX << "\nY: " << y << std::endl;
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
    int enemiesDamage = MIN_DAMAGE > index ? MIN_DAMAGE : (MAX_DAMAGE < index ? MAX_DAMAGE : index);
    for(int i = 0; i < currentPlatforms; i++)
    {
        //if(all turrets should be built and I have the same number of platforms as turrets) or if(all turrets should be built but the number of platforms allows for the current platform not to have a turret and random chance) or if(not all turrets should be built and therefore the turrets to be built equals the number of platforms) then build turret at current platform level
        if((allTurrets && currentPlatforms - i <= turretsToBeBuilt) || (allTurrets && currentPlatforms - i > turretsToBeBuilt && randomInRange(1, 10) > 7 || !allTurrets))
        {
            if(randomInRange(1, 5) > 5)
            {
                //turrets[turretsBuilt] = new Turret(1, platforms[i]->getY(), true, '>');
            }
            else
            {
                //turrets[turretsBuilt] = new Turret(this->width - 1, platforms[i]->getY(), true, '<');
            }
            turretsToBeBuilt--;
            turretsBuilt++;
        }
        if((allEnemies && currentPlatforms - i <= enemiesToBeSpawned) || (allEnemies && currentPlatforms - i > enemiesToBeSpawned && randomInRange(1, 10) > 3 || !allEnemies))
        {
            int enemiesDirection = randomInRange(1, 10) > 5 ? 1 : -1;
            //enemies[enemiesSpawned] = new Enemy(randomInRange(platforms[i]->getStartingPointX(), platforms[i]->getEndingPointX()), platforms[i]->getY(), enemiesDamage, enemiesDirection);
            enemiesToBeSpawned--;
            enemiesSpawned++;
        }
        if((allBonuses && currentPlatforms - i <= bonusesToBeSpawned) || (allBonuses && currentPlatforms - i > bonusesToBeSpawned && randomInRange(1, 10) > 8 || !allBonuses))
        {
            char bonusType = randomInRange(1, 10) > 8 ? 'h' : 'p';
            int bonusEffect;
            if(bonusType = 'h')
            {
                bonusEffect = index > MAX_HEALTHBONUS ? MAX_HEALTHBONUS : index;
            }
            else
            {
                bonusEffect = index / 3;
            }
            //bonuses[bonusesSpawned] = new Bonus(randomInRange(platforms[i]->getStartingX(), platforms[i]->getEndingX()), platofrms[i]->getY(), bonusType, bonusEffect);
        }
    }
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
    // for(int i = 0; i < N_PLATFORMS && platforms[i] != NULL; i++)
    // {
    //     //platforms[i]->print();
    // }
    // for(int i = 0; i < N_TURRETS && turrets[i] != NULL; i++)
    // {
    //     turrets[i]->print();
    // }
    // for(int i = 0; i < N_ENEMIES; i++)
    // {
    //     enemies[i]->print();
    // }
    // for(int i = 0; N_BONUSES; i++)
    // {
    //     bonuses[i]->print();
    // }
    // player.print();
}

void Level::updateLevel()
{
    for(int i = 0; i < N_TURRETS && turrets[i] != NULL; i++)
    {
        //turrets[i]->updateBullet(1, width - 1);
    }
}