#include "System.h"

#include "Renderer.h"


#define TITLE "Dungeon Exploration"


System::System()
	: hConsoleWindow(NULL)
{

}

void System::initialize()
{
	hConsoleWindow = GetConsoleWindow();
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	// Disable maximize & resizing.
	LONG style = GetWindowLong(hConsoleWindow, GWL_STYLE);
	SetWindowLong(hConsoleWindow, GWL_STYLE, style & ~(WS_MAXIMIZEBOX | WS_THICKFRAME));

	// Hide blinking cursor.
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsoleOutput, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsoleOutput, &cursorInfo);

	SetConsoleTitleA(TITLE);
}

void System::resizeForGridSize(int gridWidth, int gridHeight)
{
	// Win32 hack : first resize to impossible size, then shrink down.
	COORD size = { 260, 50 }; // HARDCODE FAIRE UN DEFINE
	SetConsoleScreenBufferSize(hConsoleOutput, size);

	int width, height;
	Renderer::getConsoleSizeForGrid(width, height, gridWidth, gridHeight);
	SetConsoleScreenBufferSize(hConsoleOutput, { (SHORT) width, (SHORT) height });

	SMALL_RECT rect = { 0, 0, width - 1, height - 1 };
	SetConsoleWindowInfo(hConsoleOutput, true, &rect);
}

void System::setTitle(const char *title)
{
	std::string s = TITLE;
	s += " - ";
	s += title;
}
