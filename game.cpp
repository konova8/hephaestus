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
    Level level;
    mapNode *next;
    mapNode(int index, mapNode *previousNode = NULL)
    {
        this->index = index;
        this->prev = previousNode;
        this->level = Level(index);
        this->next = NULL;
    }
};

mapNode *newNode(mapNode *currentNode)
{
    mapNode *newNode = new mapNode(currentNode->index + 1, currentNode);
    return newNode;
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
    Player player(1, currentNode->level.getHeight() - 1, '$');
    system("setterm -cursor off"); //Removes console cursor
    initscr();
    noecho(); //Prevents the console form printing typed keys
    nodelay(stdscr, true); //Makes getch() non blocking
    keypad(stdscr, TRUE); //Allows use of arrow keys
    int k;
    int playerAtBorder;
    while(k != 'q' && player.getHealth() > 0)
    {
        clear();
        currentNode->level.drawLevel(player, currentNode->index);
        k = convertMove(getch());
        currentNode->level.updateLevel();
        currentNode->level.playerUpdate(&player, k, currentNode->index);
        if(k == 'd' || k == 'a')
        {
            playerAtBorder = currentNode->level.isPlayerAtBorder(player);
            if(playerAtBorder == 1)
            {
                if(currentNode->next == NULL)
                {
                    currentNode->next = newNode(currentNode);
                }
                currentNode = currentNode->next;
                movePlayerTo('s', &player, currentNode->level);
            }
            else if(playerAtBorder == -1)
            {
                if(currentNode->index == 1)
                {
                    k = 'q';
                }
                else
                {
                    currentNode = currentNode->prev;
                    movePlayerTo('e', &player, currentNode->level);
                }
            }
        }
        sleepMs(33);
    }
    endwin();
    system("setterm -cursor on"); //Removes console cursor
}
