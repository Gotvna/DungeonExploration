#include "Character.h"
#include "Chest.h"

Character::Character()
{
    health = getMaxHealth();
    attackDamage = getAttackDamage();
    defense = getDefense();
    mana = getMana();
    xp = 0;
    xpToLevelUp = 10;
    level = 1;
}

Character::~Character() {}

void Character::move() {}

void Character::specialAttack(Entity* target)
{
    if (mana < 10)
    {
        printf("Pas assez de mana !\n");
        return;
    }
    target->takeDamage(target->getDefense(), attackDamage * 2);
    mana -= 10;
}

void Character::die()
{
    printf("Vous êtes mort !\n");
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
    health += amount;
    return health;
}

int Character::increaseMana(int amount)
{
    mana += amount;
    return mana;
}

void Character::levelUp()
{
    level++;
    xp = 0;
    xpToLevelUp += static_cast<int>(xpToLevelUp * 0.1);

    int random = rand() % 4;
    switch (random)
    {
    case 0:
        increaseAttackDamage(rand() % 3 + 1);
        break;
    case 1:
        increaseHealth((rand() % 3 + 1) * 5);
        break;
    case 2:
        increaseDefense(rand() % 3 + 1);
        break;
    case 3:
        increaseMana((rand() % 3 + 1) * 5);
        break;
    }
}

int Character::getMaxHealth() { return 5; }

int Character::getMovementPoint() { return 5; }

int Character::getAttackDamage() { return 5; }

int Character::getDefense() { return 5; }

int Character::getExperience() { return 0; }

int Character::getMana() { return 25; }

char Character::getIcon() { return '@'; }

void Character::openChest()
{
    Chest chest;
    chest.openChest();
    increaseAttackDamage(chest.getAttackDamage());
    increaseDefense(chest.getDefense());
    increaseHealth(chest.getHealth());
    increaseMana(chest.getMana());
}
