#include <ncurses.h>
#include "singleBlockEntity.hpp"

SingleBlockEntity::SingleBlockEntity(int x, int y, bool exists, char symbol)
{
    this->x = x;
    this->y = y;
    this->exists = exists;
    this->symbol = symbol;
}

int SingleBlockEntity::getX()
{
    return this->x;
}

int SingleBlockEntity::getY()
{
    return this->y;
}

bool SingleBlockEntity::getExistence()
{
    return this->exists;
}

void SingleBlockEntity::print()
{
    mvaddch(this->y, this->x, this->symbol);
}

void SingleBlockEntity::move(int moveX, int moveY)
{
    this->x += moveX;
    this->y += moveY;
}

void SingleBlockEntity::deactivate()
{
    this->exists = false;
}
