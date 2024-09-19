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

#include <iostream>
void Ghost::update()
{
    Map& map = Map::getInstance();
    Character* player = map.getPlayer();

    int startX = getPosX();
    int startY = getPosY();
    int playerX = player->getPosX();
    int playerY = player->getPosY();

    int movementPoints = this->getMovementPoint();

    // Calculer la distance actuelle entre le Ghost et le joueur
    int distanceToPlayer = std::abs(startX - playerX) + std::abs(startY - playerY);

    AStarPathfinder pathfinder(false);  // false pour fuir (maximiser la distance)
    std::vector<AStarPathfinder::Node*> path = pathfinder.findPath(startX, startY, playerX, playerY, map);

    if (!path.empty() && path.size() > 1) {
        int steps = std::min(movementPoints, (int)path.size() - 1);
        AStarPathfinder::Node* nextStep = path[steps];
        GameManager::getInstance().moveEnemyTo(this, nextStep->x, nextStep->y);
    }
    else {

        // Essayer de se déplacer localement
        std::vector<std::pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        bool canMove = false;
        int bestX = startX, bestY = startY;

        for (auto dir : directions) {
            int newX = startX + dir.first;
            int newY = startY + dir.second;

            if (newX >= 0 && newX < map.getWidth() && newY >= 0 && newY < map.getHeight()) {
                if (!map.isTileOccupied(newX, newY)) {
                    bestX = newX;
                    bestY = newY;
                    canMove = true;
                }
            }
        }

        if (canMove) {
            GameManager::getInstance().moveEnemyTo(this, bestX, bestY);
        }
        else {
            if (distanceToPlayer == 1) {
                GameManager::getInstance().notifyEnemyAttack(this, player);
            }
        }
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
