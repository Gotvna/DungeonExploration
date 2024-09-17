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
    Map& map = Map::getInstance();

    loadMap();

    while (1)
    {
        // Redraw grid (forces contents to be cleared & redrawn).
        renderer.drawGrid();

        // Draw entities.
        Entity *p = map.getPlayer();
        renderer.drawEntity(p->getIcon(), p->getPosX(), p->getPosY());
        for (Entity *e : map.getEnemies())
        {
            renderer.drawEntity(e->getIcon(), e->getPosX(), e->getPosY());
        }

        playerAction();
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

void GameManager::playerAction()
{
    Map &map = Map::getInstance();

    Entity *p = map.getPlayer();

    // Player move loop.
    int cursorX = p->getPosX(), cursorY = p->getPosY();
    int newX = cursorX, newY = cursorY;
    while (1)
    {
        renderer.drawRange(p->getPosX(), p->getPosY(), p->getMovementPoint());
        renderer.drawColor(0x2F, cursorX, cursorY);

        WORD key = Input::getInstance().waitForInput();

        // Erase.
        renderer.drawColor(0x70, cursorX, cursorY);

        switch (key)
        {
        case VK_UP:
            newY--;
            break;
        case VK_DOWN:
            newY++;
            break;
        case VK_LEFT:
            newX--;
            break;
        case VK_RIGHT:
            newX++;
            break;
        case VK_SPACE:
            p->posX = cursorX;
            p->posY = cursorY;
            return;
        }

        if (isMoveValid(p, newX, newY)) {
            cursorX = newX;
            cursorY = newY;
        }
        else {
            newX = cursorX;
            newY = cursorY;
        }
    }
}


bool GameManager::isMoveValid(Entity *entity, int desiredX, int desiredY)
{
    int distance = abs(desiredX - entity->getPosX()) + abs(desiredY - entity->getPosY());
    return distance <= entity->getMovementPoint();
}
