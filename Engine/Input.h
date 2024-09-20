#pragma once

#include <Windows.h>


class Input
{
public:

    static inline Input& getInstance();

    Input();

    static void initialize();

    WORD waitForInput();

private:

    void _initialize();

private:

    HANDLE hConsoleInput;
};


inline Input& Input::getInstance()
{
    static Input instance;
    return instance;
}
