#include <Windows.h>

#include <iostream>

#include "System.h"
#include "Input.h"
#include "Map.h"
#include "Entity.h"

#include "Renderer.h"



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

    Renderer r;
    r.setGridSize(map.getWidth(), map.getHeight());
    r.drawGrid();

    while (1)
    {
        Entity *p = reinterpret_cast<Entity *>(map.getPlayer());
        r.drawEntity(p->getIcon(), p->getPosX(), p->getPosY());
        for (Entity *e : map.getEnemies())
        {
            r.drawEntity(e->getIcon(), e->getPosX(), e->getPosY());
        }

        int cursorX = p->getPosX();
        int cursorY = p->getPosY();
        while (1)
        {
            WORD key = Input::getInstance().waitForInput();

            // Erase.
            r.drawEntity(' ', cursorX, cursorY);

            switch (key)
            {
            case VK_UP:
                cursorY--;
                break;
            case VK_DOWN:
                cursorY++;
                break;
            case VK_LEFT:
                cursorX--;
                break;
            case VK_RIGHT:
                cursorX++;
                break;
            }

            p->move();

            // Erase.
            r.drawEntity(p->getIcon(), cursorX, cursorY);
        }

    }

    return 0;
}
