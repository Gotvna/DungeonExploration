#include "Golem.h"

Golem::Golem()
{
    health = this->getMaxHealth();
}

Golem::~Golem()
{
}

void Golem::immuneDamage(int damage)
{
    if (rand() % 100 < 10)
    {
        return;
    }
}

void Golem::move()
{
    return;
}

void Golem::die()
{
    health = 0;
    printf("Golem died\n");
    character->increaseExperience(3);
    character->increaseAttackDamage(rand() % 10 + 1);
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

int Golem::getDefense()
{
    return 10;
}

int Golem::getMana()
{
    return 0;
}

char Golem::getIcon()
{
    return 'G';
}
