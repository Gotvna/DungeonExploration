#include "Character.h"
#include "Chest.h"

Character::Character()
{
    maxHealth = 15;
    attackDamage = 5;
    defense = 5;
    maxMana = 25;
    mana = getMaxMana();

    health = getMaxHealth();
    xp = 0;
    xpToLevelUp = 10;
    level = 1;
}

Character::~Character() {}

void Character::update() {}

void Character::specialAttack(Entity* target)
{
    if (mana < 10)
    {
        printf("Pas assez de mana !\n");
        return;
    }
    target->takeDamage(attackDamage * 2);
    mana -= 20;
}

void Character::die()
{
    
}

int Character::increaseAttackDamage(int amount)
{
    attackDamage += amount;
    return attackDamage;
}

int Character::increaseDefense(int amount)
{
    defense += amount;
    return defense;
}

int Character::increaseExperience(int amount)
{
    xp += amount;
    if (xp >= xpToLevelUp)
    {
        levelUp();
    }
    return xp;
}

int Character::increaseHealth(int amount)
{
    maxHealth += amount;
    return maxHealth;
}

int Character::increaseMana(int amount)
{
    mana += amount;
    return mana;
}

void Character::fillHealth()
{
    health = maxHealth;
}

void Character::fillMana()
{
    increaseMana(2);
    if (mana > getMaxMana())
    {
        mana = getMaxMana();
    }
}

void Character::levelUp()
{
    level++;
    xp = 0;
    xpToLevelUp += 5;

    int random = rand() % 4;
    switch (random)
    {
    case 0:
        increaseAttackDamage(rand() % 3 + 1);
        printf("Votre attaque est maintenant de %d\n", attackDamage);
        break;
    case 1:
        increaseHealth((rand() % 3 + 1) * 5);
        fillHealth();
        printf("Votre santé est maintenant de %d\n", maxHealth);
        break;
    case 2:
        increaseDefense(rand() % 3 + 1);
        printf("Votre défense est maintenant de %d\n", defense);
        break;
    case 3:
        increaseMana((rand() % 3 + 1) * 5);
        printf("Votre mana est maintenant de %d\n", mana);
        break;
    }
}

int Character::getMaxHealth() { return maxHealth; }

int Character::getMovementPoint() { return 5; }

int Character::getAttackDamage() { return attackDamage; }

int Character::getDefense() { return defense; }

int Character::getExperience() { return 0; }

int Character::getMaxMana() { return maxMana; }

char Character::getIcon() { return '@'; }

Chest::Loot Character::openChest(Chest* chest)
{
    Chest::Loot loot = chest->getLoot();
    increaseAttackDamage(chest->getAttackDamage());
    increaseDefense(chest->getDefense());
    increaseHealth(chest->getHealth());
    increaseMana(chest->getMaxMana());
    return loot;
}
