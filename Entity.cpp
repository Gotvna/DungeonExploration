#include "Entity.h"


int Entity::attack(Entity* target)
{
    return target->takeDamage(this->getAttackDamage());
}

int Entity::takeDamage(int damage)
{
    int actualDamage = damage - (this->getDefense() / 100.0f);
    health -= actualDamage;

    if (health <= 0)
    {
        die();
    }

    return actualDamage;
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
