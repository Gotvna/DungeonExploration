#pragma once
#include "Entity.h"

class Character : public Entity
{
    public:
        Character();
        ~Character();
    public:
        virtual void move();
        virtual void die();
        virtual int getHealth();
        virtual int getMP();
        virtual int getAP();
        virtual char getIcon();
};
