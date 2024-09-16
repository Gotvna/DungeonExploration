#include "Reaper.h"

Reaper::Reaper()
{
    health = this->getMaxHealth();
}

Reaper::~Reaper()
{
}

void Reaper::move()
{
}

void Reaper::die()
{
    health = 0;
    character->increaseExperience(2);
}

int Reaper::getMaxHealth()
{
    return 2;
}

int Reaper::getMovementPoint()
{
    return 6;
}

int Reaper::getAttackDamage()
{
    return 3;
}

int Reaper::getDefense()
{
    return 1;
}

int Reaper::getMana()
{
    return 0;
}

char Reaper::getIcon()
{
    return 'F';
}
