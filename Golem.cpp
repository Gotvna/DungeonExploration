#include "Golem.h"

Golem::Golem()
{
    health = this->getMaxHealth();
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
