#include <Windows.h>

#include <iostream>

#include "System.h"
#include "Input.h"
#include "Map.h"
#include "Entity.h"
#include "Character.h"

#include "Renderer.h"


bool isMoveValid(Entity* entity, int desiredX, int desiredY)
{
    int distance = abs(desiredX - entity->getPosX()) + abs(desiredY - entity->getPosY());
    return distance <= entity->getMovementPoint();
}


int main()
{
    // Init.
    System::getInstance().initialize();
    Input::getInstance().initialize();

    // Load map & inform subsystems.
    Map::getInstance().clear();
    Map::getInstance().load("Map.txt");

    Map &map = Map::getInstance();
    System::getInstance().resizeForGridSize(map.getWidth(), map.getHeight());

    // Setup renderer.
    Renderer r;
    r.setGridSize(map.getWidth(), map.getHeight());
    r.drawGrid();

    // Main game loop.
    while (1)
    {
        Entity *p = reinterpret_cast<Entity *>(map.getPlayer());
        r.drawEntity(p->getIcon(), p->getPosX(), p->getPosY());
        for (Entity *e : map.getEnemies())
        {
            r.drawEntity(e->getIcon(), e->getPosX(), e->getPosY());
        }

        // Player move loop.
        int cursorX = p->getPosX(), cursorY = p->getPosY();
        int newX = cursorX, newY = cursorY;
        bool validatedMovement = false;
        while (!validatedMovement)
        {
            r.drawRange(p->getPosX(), p->getPosY(), p->getMovementPoint());
            r.drawColor(0x2F, cursorX, cursorY);

            WORD key = Input::getInstance().waitForInput();

            // Erase.
            r.drawColor(0x70, cursorX, cursorY);

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
                validatedMovement = true;
                break;
            }

            if (validatedMovement) {

            }

            if (isMoveValid(p, newX, newY)) {
                cursorX = newX;
                cursorY = newY;
            }
            else {
                newX = cursorX;
                newY = cursorY;
            }

            //p->move();
        }

    }

    return 0;
}
