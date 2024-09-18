#pragma once

#include <Windows.h>


class System
{
public:

	static inline System& getInstance();

	System();

	void initialize();

	void resizeForGridSize(int gridWidth, int gridHeight);

	void setTitle(const char* title);

private:

	HWND hConsoleWindow;
	HANDLE hConsoleOutput;
};


inline System &System::getInstance()
{
	static System instance;
	return instance;
}
