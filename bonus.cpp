#include "bonus.hpp"

Bonus::Bonus(int x, int y, char bonusType, int bonusEffect) : SingleBlockEntity(x, y)
{
    this->bonusType = bonusType;
    this->bonusEffect = bonusEffect;
    if (bonusType == 'h')
    {
        this->symbol = 'H';
    }
    else if (bonusType == 'p')
    {
        this->symbol = 'P';
    }
}

void Bonus::use(Player *player)
{
    if (bonusType == 'h')
    {
        player->healthChange(bonusEffect);
    }
    else if (bonusType == 'p')
    {
        player->pointsChange(bonusEffect);
    }
    SingleBlockEntity::deactivate();
}