#include "GameManager.h"
#include "System.h"
#include "Input.h"


int main()
{
    // Init.
    System::getInstance().initialize();
    Input::getInstance().initialize();

    // Enter main loop right now.
    GameManager gameManager;    
    gameManager.run();

    return 0;
}
