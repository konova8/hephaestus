#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include "level.hpp"

using namespace std;

struct mapNode {
    int index = 0;
    mapNode *prev = NULL;
    Level currentLevel; //Assign to initLevel(int index) 
    mapNode *next = NULL;
};

int main() {

}