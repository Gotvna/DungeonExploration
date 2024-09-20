#include "Game/GameManager.h"
#include "Engine/System.h"
#include "Engine/Input.h"

#include <stdlib.h>
#include <time.h>


int main()
{
    srand(time(0));

    // Init.
    System::initialize();
    Input::initialize();

    // Enter main loop right now.
    GameManager::run();

    return 0;
}
