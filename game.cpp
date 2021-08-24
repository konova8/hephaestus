#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include "level.hpp"
#include "player.hpp"
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
    Level myLevel(2);
    Player myPlayer(15, 15, '$');
    initscr();
    getch();
    endwin();
}
