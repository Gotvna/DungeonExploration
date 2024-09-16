#pragma once
#include <string>

class Entity
{
    protected:
        int health;
        int AP;
        int MP;
        std::string name[20];
        std::string icon;
    protected:
        void attack(Entity* target);
        void specialAbility();
        void takeDamage(int damage);

        virtual void move();
        virtual void die() = 0;

        virtual int getHealth() = 0;
        virtual int getMP() = 0;
        virtual int getAP() = 0;
        virtual char getIcon() = 0;
};
