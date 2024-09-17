#pragma once
#include "Map.h"

class Chest
{
public:
    Chest();
    ~Chest();

    void openChest();

    void getLoot();

    int getHealth() { return health; }
    int getAttackDamage() { return attackDamage; }
    int getDefense() { return defense; }
    int getMana() { return mana; }

    Map* map;

private:
    int health;
    int attackDamage;
    int defense;
    int mana;
};
