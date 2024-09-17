#include <Windows.h>

#include <iostream>

#include "System.h"
#include "Input.h"
#include "Map.h"
#include "Entity.h"

#include "Renderer.h"



int main()
{
    System::getInstance().initialize();
    Input::getInstance().initialize();

    Map::getInstance().clear();
    Map::getInstance().load("Map.txt");

    Map& map = Map::getInstance();

    while (1)
    {
        WORD key = Input::getInstance().waitForInput();

        Renderer r;
        r.drawGrid(map.getWidth(), map.getHeight());

        Entity* p = reinterpret_cast<Entity*>(map.getPlayer());
        r.drawEntity(p->getIcon(), p->getPosX(), p->getPosY());
        for (Entity *e : map.getEnemies())
        {
            r.drawEntity(e->getIcon(), e->getPosX(), e->getPosY());
        }


        switch (key)
        {
        case VK_UP:
            std::cout << "up!\n";
            break;
        case VK_DOWN:
            std::cout << "down!\n";
            break;
        }
    }

    return 0;
}
