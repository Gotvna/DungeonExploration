#pragma once
#include "Entity.h"

class Golem : public Entity
{
    public:
        Golem();
        ~Golem();
    public:

        virtual void update();
        virtual void die();
        virtual int getMaxHealth();
        virtual int getMovementPoint();
        virtual int getAttackDamage();
        virtual int getDefense();
        virtual int getMana();
        virtual char getIcon();

        virtual float getBlockChance() override;
};
