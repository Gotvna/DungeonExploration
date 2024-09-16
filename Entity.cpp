#include "Entity.h"


void Entity::attack(Entity* target)
{
    target->takeDamage(this->AP);
}

void Entity::takeDamage(int damage)
{
    health -= damage;
    if (health <= 0)
    {
        die();
    }
}
