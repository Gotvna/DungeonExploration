#include "Ghost.h"

Ghost::Ghost()
{
    health = this->getMaxHealth();
}

Ghost::~Ghost()
{
}

void Ghost::move()
{
}

void Ghost::die()
{
    health = 0;
    character->increaseAttackDamage(1);
}

int Ghost::getMaxHealth()
{
    return 5;
}

int Ghost::getMovementPoint()
{
    return 5;
}

int Ghost::getAttackDamage()
{
    return 3;
}

char Ghost::getIcon()
{
    return 'S';
}
