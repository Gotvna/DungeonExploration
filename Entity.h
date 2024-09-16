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
        void takeDamage(int damage);

        virtual void move() = 0;
        virtual void die() = 0;

        virtual int getMaxHealth() = 0;
        virtual int getMP() = 0;
        virtual int getAP() = 0;
        virtual std::string getIcon() = 0;
};
