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
    //EVERYTHING HERE IS FOR TESTING AT THE MOMENT,  REAL MAIN WILL BE IMPLEMENTED LATER
    int testIndex = 1;
    srand(time(0));
    Level myLevel(testIndex);
    Player player(1, myLevel.getHeight() - 1, '$');
    // int a;
    // cin >> a;
    system("setterm -cursor off"); //Removes console cursor
    initscr();
    noecho(); //Prevents the console form printing typed keys
    //nodelay(stdscr, true); //Makes getch() non blocking
    keypad(stdscr, TRUE); //Allows use of arrow keys
    int k;
    while(k != 'q')
    {
        clear();
        myLevel.drawLevel(player, testIndex);
        k = getch();
        if(k == 'd')
        {
            myLevel = Level(testIndex + 1);
            testIndex++;
        }
        else if(k == 'a' && testIndex > 1)
        {
            myLevel = Level(testIndex - 1);
            testIndex--;
        }
    }
    endwin();
    system("setterm -cursor on"); //Removes console cursor
}
