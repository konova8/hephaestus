#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include "level.hpp"
#include "player.hpp"
#include <unistd.h>

using namespace std;

struct mapNode {
    int index;
    mapNode *prev;
    Level currentLevel;
    mapNode *next;
    mapNode(int index, mapNode *previousNode = NULL)
    {
        this->index = index;
        this->prev = previousNode;
        this->currentLevel = Level(index);
        this->next = NULL;
    }
};

mapNode *newNode(mapNode *currentNode)
{
    mapNode *newNode = new mapNode(currentNode->index + 1, currentNode);
    return newNode;
}

void printProps(mapNode *m) //Testing purposes, will be removed before merge
{
    cout << "---------\nINDEX: " << m->index << "\tPREV: " << m->prev << "\tNEXT: " << m->next << "\n---------" << endl;
}

int convertMove(int keyPressed)
{
    int newKeyPressed;
    if(keyPressed == 'w' || keyPressed == 'W' || keyPressed == KEY_UP)
    {
        newKeyPressed = 'w';
    }
    else if(keyPressed == 's' || keyPressed == 'S' || keyPressed == KEY_DOWN)
    {
        newKeyPressed = 's';
    }
    else if(keyPressed == 'd' || keyPressed == 'd' || keyPressed == KEY_RIGHT)
    {
        newKeyPressed = 'd';
    }
    else if(keyPressed == 'a' || keyPressed == 'A' || keyPressed == KEY_LEFT)
    {
        newKeyPressed = 'a';
    }
    else if(keyPressed == 'q' || keyPressed == 'Q')
    {
        newKeyPressed = 'q';
    }
    else
    {
        newKeyPressed = ERR;
    }
    return newKeyPressed;
}

int main() {
    Level myLevel(2);
    Player myPlayer(15, 15, '$');
    initscr();
    getch();
    endwin();
}
