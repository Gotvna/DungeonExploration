#pragma once
#include "Entity.h"
#include "Character.h"

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
        virtual int getDefense();
        virtual int getMana();
        virtual char getIcon();

        Character* character;
};
