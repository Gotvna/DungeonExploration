#include "Character.h"

Character::Character()
{
    health = getMaxHealth();
    MP = getMP();
    AP = getAP();
    icon = getIcon();
}

Character::~Character()
{
}


void Character::move()
{
}

void Character::specialAttack(Entity* target)
{
}

void Character::die()
{
    health = 0;
}

int Character::getMaxHealth()
{
    return 5;
}

int Character::getMP()
{
    return 5;
}

int Character::getAP()
{
    return 2;
}

char Character::getIcon()
{
    return '@';
}
