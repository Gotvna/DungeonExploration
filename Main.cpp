#include "GameManager.h"
#include "System.h"
#include "Input.h"

#include <stdlib.h>
#include <time.h>


int main()
{
    srand(time(0));

    // Init.
    System::getInstance().initialize();
    Input::getInstance().initialize();

    // Enter main loop right now.
    GameManager::getInstance().run();

    return 0;
}
