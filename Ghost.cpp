#include "Ghost.h"

#include "Map.h"
#include "Character.h"
#include "GameManager.h"
#include "FleePathfinder.h"

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
    Map& map = Map::getInstance();
    Character* player = map.getPlayer();

    int startX = getPosX();
    int startY = getPosY();
    int playerX = player->getPosX();
    int playerY = player->getPosY();
    int movementPoints = this->getMovementPoint();

    if (std::abs(startX - playerX) + std::abs(startY - playerY) == 1) {
        GameManager::getInstance().notifyEnemyAttack(this, player);
        return;
    }

    FleePathfinder fleePathfinder;
    std::vector<FleePathfinder::Node*> path = fleePathfinder.findFleePath(startX, startY, playerX, playerY, movementPoints, map);

    if (!path.empty()) {
        FleePathfinder::Node* destination = path.back();
        GameManager::getInstance().moveEnemyTo(this, destination->x, destination->y);
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
    return 3;
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
