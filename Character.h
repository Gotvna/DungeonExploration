#pragma once
#include "Entity.h"

class Character : public Entity
{
private:
    int attackDamage;
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
        virtual char getIcon();
};
