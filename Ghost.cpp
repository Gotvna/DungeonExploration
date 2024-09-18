#include "Ghost.h"

#include "Map.h"
#include "Character.h"
#include "GameManager.h"
#include "AStarPathfinder.h"

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

    AStarPathfinder pathfinder(false);
    std::vector<AStarPathfinder::Node*> path = pathfinder.findPath(startX, startY, playerX, playerY, map);

    if (!path.empty() && path.size() > 1) {
        int steps = std::min(movementPoints, (int)path.size() - 1);
        AStarPathfinder::Node* nextStep = path[steps];
        GameManager::getInstance().moveEnemyTo(this, nextStep->x, nextStep->y);
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
