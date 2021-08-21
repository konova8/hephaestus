#include <ncurses.h>
#include "singleBlockEntity.hpp"

SingleBlockEntity::SingleBlockEntity(int x, int y, bool exists, char symbol)
{
    this->x = x;
    this->y = y;
    this->exists = exists;
    this->symbol = symbol;
}

void SingleBlockEntity::move(int moveX, int moveY)
{
    this->x += moveX;
    this->y += moveY;
}

bool SingleBlockEntity::getExistence()
{
    return this->exists;
}

void SingleBlockEntity::deactivate()
{
    this->exists = false;
}

void SingleBlockEntity::print()
{
    mvaddch(this->y, this->x, this->symbol);
}
