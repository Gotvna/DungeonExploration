#include "Character.h"

Character::Character()
{
    health = this->getMaxHealth();
    attackDamage = getAttackDamage();
    defense = getDefense();
    mana = getMana();
    xp = getExperience();
    xpToLevelUp = 10;
    xp = xpToLevelUp;
    level = 1;
}

Character::~Character()
{
}


void Character::move()
{
}

void Character::specialAttack(Entity* target)
{
    if (getMana() < 10)
    {
        return;
    }
    target->takeDamage(target->getDefense(), attackDamage * 2);
    getMana() - 10;
}

int Character::increaseAttackDamage(int amount)
{
    return attackDamage + amount;
}

int Character::increaseDefense(int amount)
{
    return 0;
}

int Character::increaseExperience(int amount)
{
    return xp + amount;
}

int Character::increaseHealth(int amount)
{
    return health + amount;
}

int Character::increaseMana(int amount)
{
    return mana + amount;
}

int Character::getLevel()
{
    if (xp >= xpToLevelUp)
    {
        level++;
        xp = 0;
        xpToLevelUp = xpToLevelUp + (xpToLevelUp * 0.1);
    }

    if (level++)
    {
        int random = rand() % 4;
        switch (random)
        {
        case 0:
            increaseAttackDamage(rand() % 3 + 1);
            break;
        case 1:
            increaseHealth(rand() % 3 + 1 * 5);
            break;
        case 2:
            increaseDefense(rand() % 3 + 1);
            break;
        case 3:
            increaseMana(rand() % 3 + 1 * 5);
            break;
        }
    }

    return level;
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
    return 5;
}

int Character::getDefense()
{
    return 5;
}

int Character::getExperience()
{
    return 0;
}

int Character::getMana()
{
    return 25;
}

char Character::getIcon()
{
    return '@';
}
