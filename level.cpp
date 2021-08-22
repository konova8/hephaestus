#include "level.hpp"
#include <iostream> //Testing purposes, will remove later
#include <cstdlib>
#include <ncurses.h>

Level::Level(int index)
{
    this->width = 40;
    this->height = 15;
    setPlatforms(index);
    setTurrets(index);
    setEnemies(index);
    setBonuses(index);
}

int Level::randomInRange(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

void Level::setPlatforms(int index)
{
    int platformsToBuild = index > N_PLATFORMS ? N_PLATFORMS : index;
    int startingX, y = height - 1, endingX, direction;
    for(int i = 0; i < platformsToBuild; i++)
    {
        if(i == 0)
        {
            startingX = randomInRange(5, width - 1);
        }
        else
        {
            std::cout << abs(endingX - startingX + 1) << std::endl;
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
        platforms[i] = new Platform(startingX, endingX, y, '=');
        //std::cout << "---------------\nSTARTINGX: " << startingX << "\nENDINGX: " << endingX << "\nY: " << y << std::endl;
    }
}

void Level::setTurrets(int index)
{
    
}

void Level::setEnemies(int index)
{
    
}

void Level::setBonuses(int index)
{
    
}
