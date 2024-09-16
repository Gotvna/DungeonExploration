#pragma once
#include "Entity.h"

class Golem : public Entity
{
    public:
        Golem();
        ~Golem();
    public:
        virtual void move();
        virtual void die();
        virtual int getMaxHealth();
        virtual int getMP();
        virtual int getAP();
        virtual std::string getIcon();
};
