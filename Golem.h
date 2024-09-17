#pragma once
#include "Entity.h"
#include "Character.h"

class Golem : public Entity
{
    public:
        Golem();
        ~Golem();
    public:

        void immuneDamage(int damage);

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
