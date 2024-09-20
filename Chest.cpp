#include "Chest.h"
#include <stdlib.h>
#include <iostream>

Chest::Chest()
{
    m_health = 0;
    m_attackDamage = 0;
    m_defense = 0;
    m_mana = 0;
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
        case HEALTH:  m_health       = 1000; break;
        case ATTACK:  m_attackDamage = 1000; break;
        case DEFENSE: m_defense      = 1000; break;
        case MANA:    m_mana         = 1000; break;
        }

    }
    else if (random >= 990)
    {
        switch (randomStat)
        {
        case HEALTH:  m_health       = 100; break;
        case ATTACK:  m_attackDamage = 100; break;
        case DEFENSE: m_defense      = 100; break;
        case MANA:    m_mana         = 100; break;
        }
    }
    else if (random >= 900)
    {
        switch (randomStat)
        {
        case HEALTH:  m_health       = 10; break;
        case ATTACK:  m_attackDamage = 10; break;
        case DEFENSE: m_defense      = 10; break;
        case MANA:    m_mana         = 10; break;
        }
    }
    else
    {
        switch (randomStat)
        {
        case HEALTH:  m_health       = 1; break;
        case ATTACK:  m_attackDamage = 1; break;
        case DEFENSE: m_defense      = 1; break;
        case MANA:    m_mana         = 1; break;
        }
    }

    return randomStat;
}
