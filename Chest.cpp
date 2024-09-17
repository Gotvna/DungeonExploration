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

void Chest::openChest()
{
    std::cout << "You opened a chest!" << std::endl;
    getLoot();
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
                std::cout << "You found a chest with 1000 health!" << std::endl;
                break;
            case 1:
                attackDamage = 1000;
                std::cout << "You found a chest with 1000 attack damage!" << std::endl;
                break;
            case 2:
                defense = 1000;
                std::cout << "You found a chest with 1000 defense!" << std::endl;
                break;
            case 3:
                mana = 1000;
                std::cout << "You found a chest with 1000 mana!" << std::endl;
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
            std::cout << "You found a chest with 100 health!" << std::endl;
            break;
        case 1:
            attackDamage = 100;
            std::cout << "You found a chest with 100 attack damage!" << std::endl;
            break;
        case 2:
            defense = 100;
            std::cout << "You found a chest with 100 defense!" << std::endl;
            break;
        case 3:
            mana = 100;
            std::cout << "You found a chest with 100 mana!" << std::endl;
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
            std::cout << "You found a chest with 10 health!" << std::endl;
            break;
        case 1:
            attackDamage = 10;
            std::cout << "You found a chest with 10 attack damage!" << std::endl;
            break;
        case 2:
            defense = 10;
            std::cout << "You found a chest with 10 defense!" << std::endl;
            break;
        case 3:
            mana = 10;
            std::cout << "You found a chest with 10 mana!" << std::endl;
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
            std::cout << "You found a chest with 1 health!" << std::endl;
            break;
        case 1:
            attackDamage = 1;
            std::cout << "You found a chest with 1 attack damage!" << std::endl;
            break;
        case 2:
            defense = 1;
            std::cout << "You found a chest with 1 defense!" << std::endl;
            break;
        case 3:
            mana = 1;
            std::cout << "You found a chest with 1 mana!" << std::endl;
            break;
        }
    }

}

void Chest::setLoot(int health, int attackDamage, int defense, int mana)
{
    this->health = health;
    this->attackDamage = attackDamage;
    this->defense = defense;
    this->mana = mana;
}
