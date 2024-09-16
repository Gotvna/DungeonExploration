#include "Golem.h"

Golem::Golem()
{
    health = getMaxHealth();
    MP = getMP();
    AP = getAP();
    icon = getIcon();
}

Golem::~Golem()
{
}

void Golem::move()
{
}

void Golem::die()
{
    health = 0;
}

int Golem::getMaxHealth()
{
    return 10;
}

int Golem::getMP()
{
    return 0;
}

int Golem::getAP()
{
    return 1;
}

char Golem::getIcon()
{
    return 'G';
}
