#include "GameManager.h"
#include "System.h"
#include "Input.h"

#include <stdlib.h>
#include <time.h>


int main()
{
    srand(time(0));

    // Init.
    System::getInstance().initialize(); //faire une fonction static directement
    Input::getInstance().initialize();

    // Enter main loop right now.
    GameManager::getInstance().run(); //faire une fonction static directement

    return 0;
}
