#include "Entity.h"


int Entity::attack(Entity* target)
{
    return target->takeDamage(this->getAttackDamage());
}

int Entity::takeDamage(int damage)
{
    int effectiveDamage = damage - (this->getDefense() / 100.0f);
    if (effectiveDamage < 0) {
        effectiveDamage = 0;
    }

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
