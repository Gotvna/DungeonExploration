#include <Windows.h>

#include <iostream>

#include "System.h"
#include "Input.h"
#include "Map.h"



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
