#pragma once
#include <string>

class Entity
{
friend class Map;

    protected:
        int health;
        std::string name;

        int posX;
        int posY;
    public:
        void attack(Entity* target);
        void takeDamage(int defense, int damage);

        virtual void move() = 0;
        virtual void die() = 0;

        virtual int getMaxHealth() = 0;
        virtual int getMovementPoint() = 0;
        virtual int getAttackDamage() = 0;
        virtual int getDefense() = 0;
        virtual int getMana() = 0;
        virtual char getIcon() = 0;
};
