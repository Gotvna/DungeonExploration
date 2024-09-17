#include "Renderer.h"

#include <Windows.h>


static void blitLine(uint8_t *line, int numChars, int posX, int posY)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { posX, posY };
	DWORD numWritten;

	WriteConsoleOutputCharacterA(h, (LPCSTR) line, numChars, pos, &numWritten);
}

static void color(WORD color, int length, int posX, int posY)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { posX, posY };
	DWORD numWritten;

	WORD colors[2048];
	for (int i = 0; i < length; i++) {
		colors[i] = color;
	}

	WriteConsoleOutputAttribute(h, colors, length, pos, &numWritten);
}


static uint8_t gridTop[4]    = { 218, 196, 194, 191 };
static uint8_t gridCells[4]  = { 179, ' ', 179, 179 };
static uint8_t gridDelims[4] = { 195, 196, 197, 180 };
static uint8_t gridBottom[4] = { 192, 196, 193, 217 };


static void fillGridBuffer(uint8_t *buf, uint8_t *linePattern, int numCharsPerLine)
{
	buf[0] = linePattern[0];
	for (int i = 1; i < numCharsPerLine - 1; i++)
	{
		buf[i] = (i % 2 == 0) ? linePattern[2] : linePattern[1];
	}
	buf[numCharsPerLine - 1] = linePattern[3];
}


void Renderer::setGridSize(int width, int height)
{
	gridWidth = width;
	gridHeight = height;
}


void Renderer::drawGrid()
{
	uint8_t line[256];

	const int numCharsPerLine = gridWidth * 2 + 1;

	int baseY = MARGIN_TOP;

	// Grid top.
	fillGridBuffer(line, gridTop, numCharsPerLine);
	blitLine(line, numCharsPerLine, 0, baseY);
	color(0x80, numCharsPerLine, 0, baseY);

	// Grid cells.
	fillGridBuffer(line, gridCells, numCharsPerLine);
	for (int i = 0; i < gridHeight; i++) {
		blitLine(line, numCharsPerLine, 0, baseY + 1 + i * 2);
		color(0x80, numCharsPerLine, 0, baseY + 1 + i * 2);
	}

	// Horizontal delimiters.
	fillGridBuffer(line, gridDelims, numCharsPerLine);
	for (int i = 0; i < gridHeight - 1; i++) {
		blitLine(line, numCharsPerLine, 0, baseY + 2 + i * 2);
		color(0x80, numCharsPerLine, 0, baseY + 2 + i * 2);
	}

	// Grid bottom.
	fillGridBuffer(line, gridBottom, numCharsPerLine);
	blitLine(line, numCharsPerLine, 0, baseY + 2 + (gridHeight - 1) * 2);
	color(0x80, numCharsPerLine, 0, baseY + 2 + (gridHeight - 1) * 2);
}

void Renderer::drawEntity(char icon, int posX, int posY)
{
	int cx, cy;
	calculateConsolePosition(cx, cy, posX, posY);

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { cx, cy };
	DWORD numWritten;

	WORD color = 0x8F;
	WriteConsoleOutputCharacterA(h, &icon, 1, pos, &numWritten);
	WriteConsoleOutputAttribute(h, &color, 1, pos, &numWritten);
}

void Renderer::drawColor(uint16_t color, int posX, int posY)
{
	int cx, cy;
	calculateConsolePosition(cx, cy, posX, posY);

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { cx, cy };
	DWORD numWritten;

	WriteConsoleOutputAttribute(h, &color, 1, pos, &numWritten);
}

void Renderer::drawPlayerStats(const std::string &name, int health, int attackDamage)
{

}

void Renderer::drawEnemyStats(const std::string &name, int health, int attackDamage)
{

}

void Renderer::drawRange(int centerX, int centerY, int range)
{
	int cx, cy;

	for (int y = max(0, centerY - range), i = 0; y <= min(gridHeight, centerY + range); y++, i++) {
		int d = (range - abs(y - centerY));
		for (int x = max(0, centerX - d); min(gridWidth, x <= centerX + d); x++) {
			calculateConsolePosition(cx, cy, x, y);
			color(0x1F, 1, cx, cy);
		}
	}
}

void Renderer::drawMessage(const std::string &msg)
{
	size_t offset = 0;
	size_t lineBreak = msg.find('\n', offset);
	//int y = ??;

	//blitLine(msg.c_str() + offset, lineBreak - offset, );
}



void Renderer::getConsoleSizeForGrid(int &outWidth, int &outHeight, int gridWidth, int gridHeight)
{
	outWidth = gridWidth * 2 + 1;
	outHeight = gridHeight * 2 + 1 + MARGIN_TOP + MARGIN_BOTTOM;
}

void Renderer::calculateConsolePosition(int &outX, int &outY, int gridX, int gridY)
{
	outX = gridX * 2 + 1;
	outY = gridY * 2 + 1 + MARGIN_TOP;
}
