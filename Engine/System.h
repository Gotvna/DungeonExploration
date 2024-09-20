#pragma once

#include <Windows.h>


class System
{
public:

	static inline System& getInstance();

	System();

	static void initialize();

	void resizeForGridSize(int gridWidth, int gridHeight);

	void setTitle(const char* title);

private:

	void _initialize();

private:

	HWND hConsoleWindow;
	HANDLE hConsoleOutput;
};


inline System& System::getInstance()
{
	static System instance;
	return instance;
}
