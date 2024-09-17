#include "Chest.h"


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

void Chest::getLoot()
{
    int random = rand() % 1000 + 1;
    if (random == 1000)
    {
        int randomStat = rand() % 4;
        switch (randomStat)
        {
            case 0:
                health = 1000;
                break;
            case 1:
                attackDamage = 1000;
                break;
            case 2:
                defense = 1000;
                break;
            case 3:
                mana = 1000;
                break;
        }

    }
    else if (random >= 990)
    {
        int randomStat = rand() % 4;
        switch (randomStat)
        {
        case 0:
            health = 100;
            break;
        case 1:
            attackDamage = 100;
            break;
        case 2:
            defense = 100;
            break;
        case 3:
            mana = 100;
            break;
        }
    }
    else if (random >= 900)
    {
        int randomStat = rand() % 4;
        switch (randomStat)
        {
        case 0:
            health = 10;
            break;
        case 1:
            attackDamage = 10;
            break;
        case 2:
            defense = 10;
            break;
        case 3:
            mana = 10;
            break;
        }
    }
    else
    {
        int randomStat = rand() % 4;
        switch (randomStat)
        {
        case 0:
            health = 1;
            break;
        case 1:
            attackDamage = 1;
            break;
        case 2:
            defense = 1;
            break;
        case 3:
            mana = 1;
            break;
        }
    }

}
