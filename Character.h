#pragma once
#include "Entity.h"

class Character : public Entity
{
    public:
        Character();
        ~Character();
    public:
        void specialAttack(Entity* target);
        virtual void move();
        virtual void die();
        virtual int getMaxHealth();
        virtual int getMP();
        virtual int getAP();
        virtual std::string getIcon();
};
