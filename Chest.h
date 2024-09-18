#pragma once
#include "Object.h"

class Chest : public Object
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

private:
    int health;
    int attackDamage;
    int defense;
    int mana;

};
