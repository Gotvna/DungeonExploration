#include "GameManager.h"

#include "System.h"
#include "Input.h"
#include "Map.h"
#include "Character.h"


GameManager::GameManager()
{

}

void GameManager::run()
{
    loadMap();

    while (1)
    {
        playerActionMove();

        enemyAction();
    }
}

void GameManager::loadMap()
{
    Map::getInstance().clear();
    Map::getInstance().load("Map.txt");

    Map &map = Map::getInstance();
    System::getInstance().resizeForGridSize(map.getWidth(), map.getHeight());

    // Setup renderer.
    renderer.setGridSize(map.getWidth(), map.getHeight());
}

void GameManager::redrawAll()
{
    Map &map = Map::getInstance();

    // Redraw grid (forces contents to be cleared & redrawn).
    renderer.drawGrid();

    // Draw entities.
    Entity *p = map.getPlayer();
    renderer.drawEntity(p->getIcon(), p->getPosX(), p->getPosY());
    for (Entity *e : map.getEnemies())
    {
        renderer.drawEntity(e->getIcon(), e->getPosX(), e->getPosY());
    }
}

void GameManager::playerActionMove()
{
    Map &map = Map::getInstance();

    Entity *p = map.getPlayer();

    playerRemainingMP = p->getMovementPoint();

    // Player move loop.
    int cursorX = p->getPosX(), cursorY = p->getPosY();
    int newX = cursorX, newY = cursorY;
    while (playerRemainingMP > 0)
    {
        redrawAll();

        renderer.drawRange(p->getPosX(), p->getPosY(), playerRemainingMP);
        renderer.drawColor(0x2F, cursorX, cursorY);

        WORD key = Input::getInstance().waitForInput();

        // Erase.
        renderer.drawColor(0x70, cursorX, cursorY);

        // Listen to action.
        switch (key)
        {
        case VK_UP:    newY--; break;
        case VK_DOWN:  newY++; break;
        case VK_LEFT:  newX--; break;
        case VK_RIGHT: newX++; break;
        case VK_SPACE:
            playerRemainingMP -= getDistance(p, cursorX, cursorY);
            p->posX = cursorX;
            p->posY = cursorY;
            break;
        case VK_RETURN:
            return;
        }

        // Move cursor.
        if (isMoveValid(p, playerRemainingMP, newX, newY)) {
            cursorX = newX;
            cursorY = newY;
        }
        else {
            newX = cursorX;
            newY = cursorY;
        }
    }
}

void GameManager::playerActionAttack()
{

}

void GameManager::enemyAction()
{
    for (Entity *enemy : Map::getInstance().getEnemies())
    {
        enemy->move();
    }
}


int GameManager::getDistance(Entity *entity, int x, int y)
{
    return abs(x - entity->getPosX()) + abs(y - entity->getPosY());
}

bool GameManager::isMoveValid(Entity *entity, int mp, int desiredX, int desiredY)
{
    int distance = getDistance(entity, desiredX, desiredY);
    return distance <= mp;
}
