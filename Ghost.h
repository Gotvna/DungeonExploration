#pragma once
#include "Entity.h"
#include "Character.h"

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
        virtual char getIcon();

        Character* character;
};
