#include "player.hpp"

Player::Player(int x, int y, char symbol, int health, int points)
{
    this->x = x;
    this->y = y;
    this->health = health;
    this->points = points;
    this->exists = true;
    this->symbol = symbol;
}

int Player::getHealth()
{
    return this->health;
}

int Player::getPoints()
{
    return this->points;
}

void Player::move(int keyPressed){
    if (keyPressed == 'a' || keyPressed == 'A' || keyPressed == KEY_LEFT){
        SingleBlockEntity::move(-1, 0);
    }
    else if (keyPressed == 's' || keyPressed == 'S' || keyPressed == KEY_DOWN){
        SingleBlockEntity::move(0, -1);
    }
    if (keyPressed == 'W' || keyPressed == 'w' || keyPressed == KEY_UP){
        SingleBlockEntity::move(0, 1);
    }
    if (keyPressed == 'd' || keyPressed == 'D' || keyPressed == KEY_RIGHT){
        SingleBlockEntity::move(1, 0);
    }
}