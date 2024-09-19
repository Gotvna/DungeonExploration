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

    // Si le Ghost est à une case du joueur et ne peut pas fuir, il attaque
    if (std::abs(startX - playerX) + std::abs(startY - playerY) == 1) {
        std::cout << "Ghost attaque le joueur." << std::endl;
        GameManager::getInstance().notifyEnemyAttack(this, player);
        return;
    }

    // Utiliser le FleePathfinder pour fuir
    FleePathfinder fleePathfinder;
    std::vector<FleePathfinder::Node*> path = fleePathfinder.findFleePath(startX, startY, playerX, playerY, movementPoints, map);

    if (!path.empty()) {
        // Se déplacer vers la meilleure destination possible en utilisant les points de mouvement
        FleePathfinder::Node* destination = path.back();
        std::cout << "Ghost fuit vers (" << destination->x << ", " << destination->y << ")" << std::endl;
        GameManager::getInstance().moveEnemyTo(this, destination->x, destination->y);
    }
    else {
        std::cout << "Aucun chemin trouvé pour fuir, Ghost reste sur place." << std::endl;
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
