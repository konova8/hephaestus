#include "platform.hpp"

int Platform::getStartingPointX(){
    return(this->startingPointX);
}

int Platform::getEndingPointX(){
    return(this->endingPointX);
}

int Platform::getY(){
    return(this->y);
}

bool Platform::isEntityUnderPlatform(int entit_y){
    return (getY() - 1 == entit_y);
}