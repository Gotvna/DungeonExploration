#include "Entity.h"


int Entity::attack(Entity* target)
{
    if (getBlockChance() <= 0.1f)
    {
		return 0;
	}
    return target->takeDamage(this->getAttackDamage());
}

int Entity::takeDamage(int damage)
{
    float reductionPercentage = this->getDefense() / 100.0f;
    int effectiveDamage = static_cast<int>(damage * (1.0f - reductionPercentage));

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
