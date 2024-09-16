#pragma once
#include "Entity.h"
#include "Character.h"

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
        virtual char getIcon();

        Character* character;
};
