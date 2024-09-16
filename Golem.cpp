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
    character->getMaxHealth();
}

int Golem::getMaxHealth()
{
    return 10;
}

int Golem::getMovementPoint()
{
    return 0;
}

int Golem::getAttackDamage()
{
    return 1;
}

char Golem::getIcon()
{
    return 'G';
}
