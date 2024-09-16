#include "System.h"


System::System()
	: hConsoleWindow(NULL)
{

}

void System::initialize()
{
	hConsoleWindow = GetConsoleWindow();

	// Disable maximize & resizing.
	LONG style = GetWindowLong(hConsoleWindow, GWL_STYLE);
	SetWindowLong(hConsoleWindow, GWL_STYLE, style & ~(WS_MAXIMIZEBOX | WS_THICKFRAME));

	// Set the console buffer size for the fixed-size interface.
	COORD size = { 160, 30 };
	HANDLE consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(consoleOutput, size);
}
