#pragma once
#include "Game/Map/Entity.h"

class Ghost : public Entity
{
    public:
        Ghost();
        ~Ghost();
    public:
        virtual void update();
        virtual void die();
        virtual int getMaxHealth();
        virtual int getMovementPoint();
        virtual int getAttackDamage();
        virtual int getDefense();
        virtual char getIcon();
};
