#pragma once
#include <string>

class Entity
{
friend class GameManager;
friend class Map;

    protected:
        int health;
        std::string name;

        int posX;
        int posY;
    public:
        int attack(Entity* target);
        int takeDamage(int damage);
        int takeDamageIgnoreDefense(int damage);

        virtual void update() = 0;
        virtual void die() = 0;

        virtual int getMaxHealth() = 0;
        virtual int getMovementPoint() = 0;
        virtual int getAttackDamage() = 0;
        virtual int getDefense() = 0;
        virtual int getMana() = 0;
        virtual char getIcon() = 0;

        virtual float getBlockChance() { return 0.0f; }

        virtual void specialAttack(Entity* target) {}

        inline void setName(const std::string& name) { this->name = name; }

    inline bool isDead() const { return health <= 0; }

    inline int getPosX() const { return posX; }
    inline int getPosY() const { return posY; }
};
