#include "GameManager.h"
#include "System.h"
#include "Input.h"

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
