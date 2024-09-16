#include "Entity.h"


void Entity::attack(Entity* target)
{
    target->takeDamage(target->getDefense(), this->getAttackDamage());
}

void Entity::takeDamage(int defense, int damage)
{
    health = damage - (defense / 100);
    if (health <= 0)
    {
        die();
    }
}
