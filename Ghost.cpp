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
    character->increaseExperience(1);
    character->fillHealth();
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

int Ghost::getDefense()
{
    return 5;
}

int Ghost::getMana()
{
    return 0;
}

char Ghost::getIcon()
{
    return 'S';
}
