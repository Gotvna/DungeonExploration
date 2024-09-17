#pragma once
#include "Entity.h"

class Character : public Entity
{
public:
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
    int increaseHealth(int amount);
    int increaseAttackDamage(int amount);
    int increaseMana(int amount);
    int increaseDefense(int amount);
    int increaseExperience(int amount);
    int getExperience();

    void fillHealth();

    void openChest();
    void levelUp();
    void specialAttack(Entity* target);

    virtual void move();
    virtual void die();
    virtual int getMaxHealth();
    virtual int getMovementPoint();
    virtual int getAttackDamage();
    virtual int getDefense();
    virtual int getMana();
    virtual char getIcon();
};
