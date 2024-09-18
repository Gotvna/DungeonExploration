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

static int sign(int i)
{
    if (i > 0) return 1;
    if (i < 0) return -1;
    return 0;
}

void Reaper::update()
{
    Map& map = Map::getInstance();
    Character *p = map.getPlayer();

    //if (GameManager::getDistance(this, p->getPosX(), p->getPosY()) <= 4)
    {
        // move away from player
        int dx = p->getPosX() - getPosX();
        int dy = p->getPosY() - getPosY();
        if (abs(dx) > abs(dy)) {
            dx = sign(dx) * this->getMovementPoint();
            dy = 0;
        }
        else {
            dx = 0;
            dy = sign(dy) * this->getMovementPoint();
        }

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
        if (map.getEnemies()[i] != this) {
            map.getEnemies()[i]->takeDamageIgnoreDefense(1);
        }
    }
}

int Reaper::getMaxHealth()
{
    return 2;
}

int Reaper::getMovementPoint()
{
    return 3;
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
