#pragma once

class Chest
{
public:
    Chest();
    ~Chest();

    void openChest();

    void getLoot();
    void setLoot(int health, int attackDamage, int defense, int mana);

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
