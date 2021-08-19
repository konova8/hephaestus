#include "level.hpp"
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

void Level::setPlatforms(int index)
{

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
