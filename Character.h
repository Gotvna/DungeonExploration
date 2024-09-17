#pragma once
#include "Entity.h"

class Character : public Entity
{
private:
    int attackDamage;
    int xp;
    int xpToLevelUp;
    int level;
    int mana;
    int defense;

public:
    Character();
    ~Character();
public:
    void specialAttack(Entity* target);
    int increaseHealth(int amount);
    int increaseAttackDamage(int amount);
    int increaseMana(int amount);
    int increaseDefense(int amount);
    int increaseExperience(int amount);
    int getLevel();
    int getExperience();

    void openChest();

    virtual void move();
    virtual void die();
    virtual int getMaxHealth();
    virtual int getMovementPoint();
    virtual int getAttackDamage();
    virtual int getDefense();
    virtual int getMana();
    virtual char getIcon();
};
