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
        virtual int getMP();
        virtual int getAP();
        virtual std::string getIcon();
};
