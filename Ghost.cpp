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
}

int Ghost::getMaxHealth()
{
    return 5;
}

int Ghost::getMP()
{
    return 5;
}

int Ghost::getAP()
{
    return 3;
}

char Ghost::getIcon()
{
    return 'S';
}
