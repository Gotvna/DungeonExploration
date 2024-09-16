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
        virtual int getMP();
        virtual int getAP();
        virtual char getIcon();
};
