#include "platform.hpp"
#include <ncurses.h>

Platform::Platform(int startingPointX, int endingPointX, int y, char symbol)
{
    this->startingPointX = startingPointX;
    this->endingPointX = endingPointX;
    this->y = y;
    this->symbol = symbol;
    if (this->startingPointX >= this->endingPointX){
        int tmp = this->startingPointX;
        this->startingPointX = this->endingPointX;
        this->endingPointX = tmp;
    }
}

int Platform::getStartingPointX(){
    return this->startingPointX;
}

int Platform::getEndingPointX(){
    return this->endingPointX;
}

int Platform::getY(){
    return this->y;
}

void Platform::print()
{
    for(int i = this->startingPointX; i <= this->endingPointX; i++)
    {
        mvaddch(this->y, i, this->symbol);
    }
}