#pragma once
#include "Entity.h"

class Reaper : public Entity
{
    public:
        Reaper();
        ~Reaper();
    public:
        virtual void move();
        virtual void die();
        virtual int getMaxHealth();
        virtual int getMovementPoint();
        virtual int getAttackDamage();
        virtual char getIcon();
};
