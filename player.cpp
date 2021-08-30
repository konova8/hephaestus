#include "player.hpp"

Player::Player(int x, int y, char symbol, int health, int points) : SingleBlockEntity(x, y, true, symbol)
{
    this->health = health;
    this->points = points;
    this->maxHealth = 100;
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
    if (keyPressed == 'd')
    {
        SingleBlockEntity::move(1, 0);
    }
    else if (keyPressed == 'a')
    {  
        SingleBlockEntity::move(-1, 0);
    }
    else if (keyPressed == 'w')
    {
        SingleBlockEntity::move(0, -1);
    }
    else if (keyPressed == 's')
    {
        SingleBlockEntity::move(0, 1);
    }
}

int Player::getXAfterMove(int keyPressed){
    int xAfterMove = 0;
    if (keyPressed == 'd')
    {
        xAfterMove = SingleBlockEntity::getX() + 1;
    }
    else if (keyPressed == 'a')
    { 
        xAfterMove = SingleBlockEntity::getX() - 1;
    }
    return xAfterMove;
}

void Player::healthChange(int change){
    if(this->health + change > maxHealth)
    {
        this->health = maxHealth;
    }
    else
    {
        this->health += change;
    }
}

void Player::pointsChange(int change){
    this->points += change;
}
