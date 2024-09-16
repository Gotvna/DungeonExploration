#pragma once

#include <Windows.h>


class Input
{
public:

    static Input &getInstance() { static Input g_instance; return g_instance; }

    Input();

    void initialize();

    WORD waitForInput();

private:

    HANDLE hConsoleInput;
};
