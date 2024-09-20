#include "Reaper.h"

#include "Game/Map/Map.h"
#include "Game/Character/Character.h"
#include "Game/GameManager.h"
#include "Game/Algorithm/AStarPathFinder.h"

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

    int distanceToPlayer = std::abs(startX - playerX) + std::abs(startY - playerY);

    if (distanceToPlayer == 1) {
        GameManager::getInstance().notifyEnemyAttack(this, player);
        return;
    }

    std::vector<std::pair<int, int>> adjacentPositions = {
        {playerX + 1, playerY},
        {playerX - 1, playerY},
        {playerX, playerY + 1},
        {playerX, playerY - 1}
    };

    std::pair<int, int> bestPosition = { startX, startY };
    int minDistance = std::numeric_limits<int>::max();

    for (auto& pos : adjacentPositions) {
        int adjX = pos.first;
        int adjY = pos.second;

        if (adjX >= 0 && adjX < map.getWidth() && adjY >= 0 && adjY < map.getHeight() && !map.isTileOccupied(adjX, adjY)) {
            int distance = std::abs(startX - adjX) + std::abs(startY - adjY);
            if (distance < minDistance) {
                minDistance = distance;
                bestPosition = { adjX, adjY };
            }
        }
    }

    AStarPathfinder pathfinder(true);
    std::vector<AStarPathfinder::Node*> path = pathfinder.findPath(startX, startY, bestPosition.first, bestPosition.second, map);

    // Vérification du chemin trouvé
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
    return 5;
}

int Reaper::getMovementPoint()
{
    return 4;
}

int Reaper::getAttackDamage()
{
    return 10;
}

int Reaper::getDefense()
{
    return 3;
}

char Reaper::getIcon()
{
    return 'F';
}
