#include "Chest.h"
#include <stdlib.h>
#include <iostream>

Chest::Chest()
{
    health = 0;
    attackDamage = 0;
    defense = 0;
    mana = 0;
}

Chest::~Chest()
{
}

Chest::Loot Chest::getLoot()
{
    int random = rand() % 1000 + 1;
    Loot randomStat = (Loot) (rand() % 4);

    if (random == 1000)
    {
        switch (randomStat)
        {
        case HEALTH:  health       = 1000; break;
        case ATTACK:  attackDamage = 1000; break;
        case DEFENSE: defense      = 1000; break;
        case MANA:    mana         = 1000; break;
        }

    }
    else if (random >= 990)
    {
        switch (randomStat)
        {
        case HEALTH:  health       = 100; break;
        case ATTACK:  attackDamage = 100; break;
        case DEFENSE: defense      = 100; break;
        case MANA:    mana         = 100; break;
        }
    }
    else if (random >= 900)
    {
        switch (randomStat)
        {
        case HEALTH:  health       = 10; break;
        case ATTACK:  attackDamage = 10; break;
        case DEFENSE: defense      = 10; break;
        case MANA:    mana         = 10; break;
        }
    }
    else
    {
        switch (randomStat)
        {
        case HEALTH:  health       = 1; break;
        case ATTACK:  attackDamage = 1; break;
        case DEFENSE: defense      = 1; break;
        case MANA:    mana         = 1; break;
        }
    }

    return randomStat;
}
