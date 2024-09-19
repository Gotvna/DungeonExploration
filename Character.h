#pragma once
#include "Entity.h"
#include "Chest.h"

class Character : public Entity
{
public:
    int maxHealth;
    int attackDamage;
    int xp;
    int xpToLevelUp;
    int level;
    int maxMana;
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
    void fillMana() override;

    Chest::Loot openChest(Chest* chest);
    void levelUp();
    void specialAttack(Entity* target) override;

    inline int getMana() override { return mana; };

    virtual void update();
    virtual void die();
    virtual int getMaxHealth();
    virtual int getMovementPoint();
    virtual int getAttackDamage();
    virtual int getDefense();
    virtual int getMaxMana() override;
    virtual char getIcon();
};
