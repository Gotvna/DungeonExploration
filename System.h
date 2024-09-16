#pragma once

#include <Windows.h>


class System
{
public:

	static inline System& getInstance();

	System();

	void initialize();

private:

	HWND hConsoleWindow;
};


inline System &System::getInstance()
{
	static System instance;
	return instance;
}
