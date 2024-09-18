#include "Reaper.h"
#include "Map.h"
#include "Character.h"
#include "GameManager.h"
#include "AStarPathfinder.h"

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
    Character* player = map.getPlayer();

    int startX = getPosX();
    int startY = getPosY();
    int playerX = player->getPosX();
    int playerY = player->getPosY();

    int movementPoints = this->getMovementPoint();

    AStarPathfinder pathfinder(true);
    std::vector<AStarPathfinder::Node*> path = pathfinder.findPath(startX, startY, playerX, playerY, map);

    if (!path.empty() && path.size() > 1) {
        int steps = std::min(movementPoints, (int)path.size() - 1);
        AStarPathfinder::Node* nextStep = path[steps];
        GameManager::getInstance().moveEnemyTo(this, nextStep->x, nextStep->y);
    }
}

void Reaper::die()
{
    health = 0;

    Map& map = Map::getInstance();
    Character* p = map.getPlayer();
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
