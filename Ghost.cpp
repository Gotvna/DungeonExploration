#include "Ghost.h"

#include "Map.h"
#include "Character.h"
#include "GameManager.h"

Ghost::Ghost()
{
    health = this->getMaxHealth();
}

Ghost::~Ghost()
{
}

int sign(int i);

void Ghost::update()
{
    Map &map = Map::getInstance();
    Character *p = map.getPlayer();

    // move towards player
    int distanceToPlayer = GameManager::getDistance(this, p->getPosX(), p->getPosY());
    if (distanceToPlayer == 1) {
        GameManager::getInstance().notifyEnemyAttack(this, p);
    }
    else if (distanceToPlayer <= this->getMovementPoint()) {
        int newX = p->getPosX();
        int newY = p->getPosY();
        int dx = p->getPosX() - getPosX();
        int dy = p->getPosY() - getPosY();
        if (abs(dx) > abs(dy)) {
            if (dx > 0) newX--;
            else        newX++;
        }
        else {
            if (dy > 0) newY--;
            else        newY++;
        }

        GameManager::getInstance().moveEnemyTo(this, newX, newY);
        GameManager::getInstance().notifyEnemyAttack(this, p);
    }
    else {
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

        GameManager::getInstance().moveEnemyTo(this, getPosX() + dx, getPosY() + dy);
    }
}

void Ghost::die()
{
    health = 0;

    Character* p = Map::getInstance().getPlayer();
    p->increaseExperience(1);
    p->fillHealth();
}

int Ghost::getMaxHealth()
{
    return 5;
}

int Ghost::getMovementPoint()
{
    return 5;
}

int Ghost::getAttackDamage()
{
    return 3;
}

int Ghost::getDefense()
{
    return 5;
}

int Ghost::getMana()
{
    return 0;
}

char Ghost::getIcon()
{
    return 'S';
}
