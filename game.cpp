#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include "level.hpp"
#include "player.hpp"
#include <unistd.h>

using namespace std;

struct mapNode {
    mapNode *prev;
    Level *level;
    mapNode *next;
    mapNode(int index, mapNode *previousNode = NULL, mapNode *nextNode = NULL)
    {
        this->prev = previousNode;
        this->level = new Level(index);
        this->next = nextNode;
    }
};

mapNode *newNode(mapNode *currentNode, int direction)
{
    mapNode *newNode;
    if(direction == 1)
    {
        newNode = new mapNode(currentNode->level->getIndex() + 1, currentNode);
    }
    else if(direction == -1)
    {
        newNode = new mapNode(currentNode->level->getIndex() - 1, NULL, currentNode);
    }
    return newNode;
}

int convertMove(int keyPressed)
{
    int newKeyPressed;
    switch(keyPressed)
    {
        default:
            newKeyPressed = ERR;
            break;
        case 'w':
        case 'W':
        case KEY_UP:
            newKeyPressed = 'w';
            break;
        case 's':
        case 'S':
        case KEY_DOWN:
            newKeyPressed = 's';
            break;
        case 'd':
        case 'D':
        case KEY_RIGHT:
            newKeyPressed = 'd';
            break;
        case 'a':
        case 'A':
        case KEY_LEFT:
            newKeyPressed = 'a';
            break;
        case 'q':
        case 'Q':
            newKeyPressed = 'q';
    }
    return newKeyPressed;
}

void movePlayerTo(char whereTo, Player *player, Level level) //whereTo = 's' => move player to start, whereTo = 'e' => move player to end
{
    int toMoveY = 0;
    int toMoveX = 0;
    if(whereTo == 's')
    {
        toMoveY = player->getY() == level.getHeight() - 1 ? 0 : (level.getHeight() - player->getY());
        toMoveX = player->getX() == 1 ? 0 : (1 - player->getX());
    }
    else if(whereTo == 'e')
    {
        toMoveY = player->getY() == level.getHeight() - 1 ? 0 : (level.getHeight() - player->getY());
        toMoveX = player->getX() == level.getWidth() - 1 ? 0 : ((level.getWidth() - 1 ) - player->getX());
    }
    player->move(toMoveX, toMoveY);
}

void sleepMs(int microseconds)
{
    usleep(microseconds * 1000);
}

int main() {
    srand(time(0));
    mapNode *currentNode = new mapNode(1);
    Player player(1, currentNode->level->getHeight() - 1, '$');
    system("setterm -cursor off"); //Removes console cursor
    initscr();
    noecho(); //Prevents the console form printing typed keys
    nodelay(stdscr, true); //Makes getch() non blocking
    keypad(stdscr, TRUE); //Allows use of arrow keys
    int k;
    int playerAtBorder;
    while(k != 'q' && player.getHealth() > 0)
    {
        currentNode->level->drawLevel(player);
        k = convertMove(getch());
        currentNode->level->updateLevel();
        currentNode->level->playerUpdate(&player, k);
        if(k == 'd' || k == 'a')
        {
            playerAtBorder = currentNode->level->isPlayerAtBorder(player);
            if(playerAtBorder == 1)
            {
                if(currentNode->next == NULL)
                {
                    currentNode->next = newNode(currentNode, 1);
                }
                currentNode = currentNode->next;
                movePlayerTo('s', &player, *currentNode->level);
            }
            else if(playerAtBorder == -1)
            {
                if(currentNode->level->getIndex() == 1)
                {
                    k = 'q';
                }
                else
                {
                    if(currentNode->prev == NULL)
                    {
                        currentNode->prev = newNode(currentNode, -1);
                    }
                    currentNode = currentNode->prev;
                    movePlayerTo('e', &player, *currentNode->level);
                }
            }
        }
        sleepMs(33);
    }
    echo();
    system("setterm -cursor on"); //Removes console cursor
    endwin();
}
