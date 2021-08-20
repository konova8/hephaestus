#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include "level.hpp"
#include "enemy.hpp"
#include <unistd.h>

using namespace std;

struct mapNode {
    int index;
    mapNode *prev = NULL;
    Level currentLevel = index; //??????????????????
    mapNode *next = NULL;
    mapNode(int Index)
    {
        index = Index;
        currentLevel = Index; //??????????????????
    }
};

int main() {
    
}