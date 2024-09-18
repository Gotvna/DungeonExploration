#include "Reaper.h"

#include "Map.h"
#include "Character.h"
#include "GameManager.h"

Reaper::Reaper()
{
    health = this->getMaxHealth();
}

Reaper::~Reaper()
{
}

void Reaper::update()
{
    Map& map = Map::getInstance();
    Character *p = map.getPlayer();

    if (GameManager::getDistance(this, p->getPosX(), p->getPosY() <= 2))
    {
        // move away from player
        int dx = p->getPosX() - getPosX();
        int dy = p->getPosY() - getPosY();
        GameManager::getInstance().moveEnemyTo(this, getPosX() - dx, getPosY() - dy);
    }
}

void Reaper::die()
{
    health = 0;

    Map& map = Map::getInstance();
    Character *p = map.getPlayer();
    p->increaseExperience(2);

    for (int i = 0; i < map.getEnemies().size(); i++)
    {
        map.getEnemies()[i]->takeDamageIgnoreDefense(1);
    }
}

int Reaper::getMaxHealth()
{
    return 2;
}

int Reaper::getMovementPoint()
{
    return 6;
}

int Reaper::getAttackDamage()
{
    return 3;
}

int Reaper::getDefense()
{
    return 1;
}

int Reaper::getMana()
{
    return 0;
}

char Reaper::getIcon()
{
    return 'F';
}
