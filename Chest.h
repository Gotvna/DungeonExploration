#pragma once
#include <stdlib.h>

class Chest
{
public:
    Chest();
    ~Chest();

    void getLoot();
private:
    int health;
    int attackDamage;
    int defense;
    int mana;
};
