#pragma once

class Chest
{
    friend class Map;

public:
    Chest();
    ~Chest();

    void openChest();

    void getLoot();

    int getHealth() { return health; }
    int getAttackDamage() { return attackDamage; }
    int getDefense() { return defense; }
    int getMana() { return mana; }

    inline int getPosX() const { return posX; }
    inline int getPosY() const { return posY; }

private:
    int health;
    int attackDamage;
    int defense;
    int mana;

    int posX;
    int posY;
};
