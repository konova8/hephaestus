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
