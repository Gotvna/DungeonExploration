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
#include <iostream>

void Reaper::update()
{
    Map& map = Map::getInstance();
    Character* player = map.getPlayer();

    int startX = getPosX();
    int startY = getPosY();
    int playerX = player->getPosX();
    int playerY = player->getPosY();

    int movementPoints = this->getMovementPoint();  // Récupérer les points de mouvement du Reaper

    int distanceToPlayer = std::abs(startX - playerX) + std::abs(startY - playerY);

    // Si le Reaper est à une case du joueur, il attaque
    if (distanceToPlayer == 1) {
        GameManager::getInstance().notifyEnemyAttack(this, player);
        return;
    }

    // Calculer les quatre cases adjacentes au joueur
    std::vector<std::pair<int, int>> adjacentPositions = {
        {playerX + 1, playerY},  // Droite
        {playerX - 1, playerY},  // Gauche
        {playerX, playerY + 1},  // Bas
        {playerX, playerY - 1}   // Haut
    };

    // Trouver la meilleure case adjacente disponible
    std::pair<int, int> bestPosition = { startX, startY };
    int minDistance = std::numeric_limits<int>::max();

    for (auto& pos : adjacentPositions) {
        int newX = pos.first;
        int newY = pos.second;

        // Vérifie si la case est libre et dans les limites de la carte
        if (newX >= 0 && newX < map.getWidth() && newY >= 0 && newY < map.getHeight()) {
            std::cout << "Reaper vérifie la case (" << newX << ", " << newY << ")" << std::endl;

            if (!map.isTileOccupied(newX, newY)) {
                std::cout << "Case (" << newX << ", " << newY << ") est libre." << std::endl;

                // Calculer la distance entre le Reaper et cette case
                int distance = std::abs(startX - newX) + std::abs(startY - newY);
                if (distance < minDistance) {
                    minDistance = distance;
                    bestPosition = { newX, newY };  // Mettre à jour la meilleure position
                }
            }
            else {
                std::cout << "Case (" << newX << ", " << newY << ") est occupée." << std::endl;
            }
        }
    }

    // Déplacer le Reaper vers la meilleure position trouvée
    if (bestPosition != std::make_pair(startX, startY)) {
        std::cout << "Reaper se déplace vers (" << bestPosition.first << ", " << bestPosition.second << ")" << std::endl;
        GameManager::getInstance().moveEnemyTo(this, bestPosition.first, bestPosition.second);
    }
    else {
        std::cout << "Reaper: Pas de mouvement possible." << std::endl;
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
