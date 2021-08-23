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
    bool check = false;
    int platform_y = getY();
    if (platform_y - entit_y == 1){
        check = true;
    }
    return check;
}