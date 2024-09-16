#include "Ghost.h"

Ghost::Ghost()
{
    health = getMaxHealth();
    MP = getMP();
    AP = getAP();
    icon = getIcon();
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
