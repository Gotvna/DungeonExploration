#pragma once
#include "Entity.h"

class Ghost : public Entity
{
    public:
        Ghost();
        ~Ghost();
    public:
        virtual void move();
        virtual void die();
        virtual int getMaxHealth();
        virtual int getMovementPoint();
        virtual int getAttackDamage();
        virtual int getDefense();
        virtual int getMana();
        virtual char getIcon();
};
