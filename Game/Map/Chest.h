#pragma once
#include "Object.h"

class Chest : public Object
{
public:
    enum Loot
    {
        HEALTH,
        ATTACK,
        DEFENSE,
        MANA
    };

    Chest();
    ~Chest();

    Loot getLoot();

    int getHealth() { return m_health; }
    int getAttackDamage() { return m_attackDamage; }
    int getDefense() { return m_defense; }
    int getMaxMana() { return m_mana; }

private:
    int m_health;
    int m_attackDamage;
    int m_defense;
    int m_mana;

};
