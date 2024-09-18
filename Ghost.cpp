#include "Ghost.h"

#include "Map.h"
#include "Character.h"

Ghost::Ghost()
{
    health = this->getMaxHealth();
}

Ghost::~Ghost()
{
}

void Ghost::update()
{
}

void Ghost::die()
{
    health = 0;

    Character* p = Map::getInstance().getPlayer();
    p->increaseExperience(1);
    p->fillHealth();
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
