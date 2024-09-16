#include "Input.h"

Input::Input()
    : hConsoleInput(INVALID_HANDLE_VALUE)
{

}

void Input::initialize()
{
    hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
}

WORD Input::waitForInput()
{
    INPUT_RECORD inp;
    DWORD num_of_events;

    do {
        ReadConsoleInput(hConsoleInput, &inp, 1, &num_of_events);
    } while (!(inp.EventType == KEY_EVENT && !inp.Event.KeyEvent.bKeyDown));

    return inp.Event.KeyEvent.wVirtualKeyCode;
}
