#include "Entity.h"
#include "Golem.h"


int Entity::attack(Entity* target)
{
    if (dynamic_cast<Golem*>(target))
    {
        if (dynamic_cast<Golem*>(target)->immuneDamage(this->getAttackDamage()))
        {
			return 0;
		}
	}
    else return target->takeDamage(this->getAttackDamage());
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
