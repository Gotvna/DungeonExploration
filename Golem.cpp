#include "Golem.h"

#include "Map.h"
#include "Character.h"

Golem::Golem()
{
    health = this->getMaxHealth();
}

Golem::~Golem()
{
}

bool Golem::immuneDamage(int damage)
{
    if (rand() % 100 < 10)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Golem::move()
{
    return;
}

void Golem::die()
{
    health = 0;
    
    Character *p = Map::getInstance().getPlayer();
    p->increaseExperience(3);
    p->increaseAttackDamage(rand() % 10 + 1);
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
