#include "Golem.h"

#include "Map.h"
#include "Character.h"
#include "GameManager.h"

Golem::Golem()
{
    health = this->getMaxHealth();
}

Golem::~Golem()
{
}

void Golem::update()
{
    Map& map = Map::getInstance();
    Character* p = map.getPlayer();

    if (GameManager::getDistance(this, p->getPosX(), p->getPosY()) == 1) {
        GameManager::getInstance().notifyEnemyAttack(this, p);
    }
}

void Golem::die()
{
    health = 0;
    
    Character *p = Map::getInstance().getPlayer();
    p->increaseExperience(3);
    p->increaseAttackDamage(rand() % 4 + 1);
}

int Golem::getMaxHealth()
{
    return 25;
}

int Golem::getMovementPoint()
{
    return 0;
}

int Golem::getAttackDamage()
{
    return 5;
}

int Golem::getDefense()
{
    return 10;
}

char Golem::getIcon()
{
    return 'G';
}

float Golem::getBlockChance()
{
    return 0.1f;
}
