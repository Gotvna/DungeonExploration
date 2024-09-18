#include "Entity.h"


int Entity::attack(Entity* target)
{
    return target->takeDamage(this->getAttackDamage());
}

int Entity::takeDamage(int damage)
{
    if (rand() / (float)RAND_MAX < getBlockChance())
    {
        return 0;
    }

    float reductionPercentage = this->getDefense() / 100.0f;
    int effectiveDamage = static_cast<int>(damage * (1.0f - reductionPercentage));

    health -= effectiveDamage;

    if (health <= 0)
    {
        die();
    }

    return effectiveDamage;
}

int Entity::takeDamageIgnoreDefense(int damage)
{
    health -= damage;

    if (health <= 0)
    {
        die();
    }

    return damage;
}
