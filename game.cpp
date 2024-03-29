#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>
#include "player.hpp"
#include "level.hpp"

using namespace std;

struct mapNode {
    mapNode *prev;
    Level *level;
    mapNode *next;
};

void initNode(mapNode *node, int index, mapNode *previousNode = NULL, mapNode *nextNode = NULL)
{
    node->prev = previousNode;
    node->level = new Level(index);
    node->next = nextNode;
}

mapNode *newNode(mapNode *currentNode, int direction)
{
    mapNode *newNode = new mapNode;
    if(direction == 1)
    {
        initNode(newNode, currentNode->level->getIndex() + 1, currentNode);
    }
    else if(direction == -1)
    {
        initNode(newNode, currentNode->level->getIndex() - 1, NULL, currentNode);
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
        case (int)'w':
        case (int)'W':
        case KEY_UP:
            newKeyPressed = (int)'w';
            break;
        case (int)'s':
        case (int)'S':
        case KEY_DOWN:
            newKeyPressed = (int)'s';
            break;
        case (int)'d':
        case (int)'D':
        case KEY_RIGHT:
            newKeyPressed = (int)'d';
            break;
        case (int)'a':
        case (int)'A':
        case KEY_LEFT:
            newKeyPressed = (int)'a';
            break;
        case (int)'q':
        case (int)'Q':
            newKeyPressed = (int)'q';
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
    mapNode *currentNode = new mapNode;
    initNode(currentNode, 1);
    Player player(1, currentNode->level->getHeight() - 1, '$');
    system("setterm -cursor off"); //Removes console cursor
    initscr();
    noecho(); //Prevents the console form printing typed keys
    nodelay(stdscr, true); //Makes getch() non blocking
    keypad(stdscr, TRUE); //Allows use of arrow keys
    int key;
    int playerAtBorder;
    while(key != (int)'q' && player.getHealth() > 0)
    {
        currentNode->level->drawLevel(player);
        key = convertMove(getch());
        currentNode->level->updateLevel();
        currentNode->level->playerUpdate(&player, key);

        //If move is a side move, check if player is at end/start of level, and if it is, move it to the next/previous level
        if(key == (int)'d' || key == (int)'a')
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
                    key = (int)'q';
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
    key = ERR;
    clear();
    nodelay(stdscr, false);
    printw("Game over\nFinal points: %d\nPress q to exit", player.getPoints());
    while(key != (int)'q')
    {
        key = getch();
    }
    echo();
    system("setterm -cursor on"); //Activates console cursor
    endwin();
    while(currentNode->level->getIndex() != 1)
    {
        currentNode = currentNode->prev;
    }
    mapNode *tmp = currentNode;
    while(currentNode != NULL)
    {
        tmp = currentNode->next;
        currentNode->level->destroy();
        delete currentNode->level;
        delete currentNode;
        currentNode = tmp;
    }
}
