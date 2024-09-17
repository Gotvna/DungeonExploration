#include "Entity.h"


void Entity::attack(Entity* target)
{
    target->takeDamage(target->getDefense(), this->getAttackDamage());
}

void Entity::takeDamage(int damage, int defense)
{
    int effectiveDamage = damage - (defense / 100);
    if (effectiveDamage < 0) {
        effectiveDamage = 0;
    }

    health -= effectiveDamage;

    if (health <= 0)
    {
        die();
    }

}
