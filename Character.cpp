#include "Character.h"

Character::Character()
{
    health = this->getMaxHealth();
    attackDamage = getAP();
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
    return attackDamage;
}

char Character::getIcon()
{
    return '@';
}
