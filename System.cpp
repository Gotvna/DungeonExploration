#include "System.h"

#include "Renderer.h"


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
}

void System::resizeForGridSize(int gridWidth, int gridHeight)
{
	// Win32 hack : first resize to impossible size, then shrink down.
	COORD size = { 260, 50 };
	SetConsoleScreenBufferSize(hConsoleOutput, size);

	int width, height;
	Renderer::getConsoleSizeForGrid(width, height, gridWidth, gridHeight);
	SetConsoleScreenBufferSize(hConsoleOutput, { (SHORT) width, (SHORT) height });

	SMALL_RECT rect = { 0, 0, width - 1, height - 1 };
	SetConsoleWindowInfo(hConsoleOutput, true, &rect);
}
