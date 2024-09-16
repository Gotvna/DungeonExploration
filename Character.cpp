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

int Character::increaseAttackDamage(int amount)
{
    int finalAttackDamage = attackDamage + amount;
    return finalAttackDamage;
}

void Character::die()
{
    health = 0;
}

int Character::getMaxHealth()
{
    return 5;
}

int Character::getMovementPoint()
{
    return 5;
}

int Character::getAttackDamage()
{
    return attackDamage;
}

char Character::getIcon()
{
    return '@';
}
