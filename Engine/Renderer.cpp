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
	m_gridWidth = width;
	m_gridHeight = height;
}


void Renderer::drawGrid(uint16_t backColor, uint16_t wallColor, const uint8_t *walls)
{
	uint8_t line[256];

	const int numCharsPerLine = m_gridWidth * 2 + 1;

	int baseY = MARGIN_TOP;

	// Grid top.
	fillGridBuffer(line, gridTop, numCharsPerLine);
	blitLine(line, numCharsPerLine, 0, baseY);
	color(backColor, numCharsPerLine, 0, baseY);

	// Grid cells.
	fillGridBuffer(line, gridCells, numCharsPerLine);
	for (int i = 0; i < m_gridHeight; i++) {
		blitLine(line, numCharsPerLine, 0, baseY + 1 + i * 2);
		color(backColor, numCharsPerLine, 0, baseY + 1 + i * 2);
		for (int x = 0; x < m_gridWidth; x++) {
			if (walls[i * m_gridWidth + x] == 1) {
				drawColor(wallColor, x, i);
			}
		}
	}

	// Horizontal delimiters.
	fillGridBuffer(line, gridDelims, numCharsPerLine);
	for (int i = 0; i < m_gridHeight - 1; i++) {
		blitLine(line, numCharsPerLine, 0, baseY + 2 + i * 2);
		color(backColor, numCharsPerLine, 0, baseY + 2 + i * 2);
	}

	// Grid bottom.
	fillGridBuffer(line, gridBottom, numCharsPerLine);
	blitLine(line, numCharsPerLine, 0, baseY + 2 + (m_gridHeight - 1) * 2);
	color(backColor, numCharsPerLine, 0, baseY + 2 + (m_gridHeight - 1) * 2);
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

void Renderer::drawPlayerStats(const std::string &name, int health, int maxHealth, int attackDamage, int defense, int mana, int level, int xp, int xpToLevelUp)
{
	int w, h;
	Renderer::getConsoleSizeForGrid(w, h, m_gridWidth, m_gridHeight);

	blitLine((uint8_t*) name.c_str(), name.size(), 2, h - 4);
	color(0x07, name.size(), 2, h - 4);

	drawHealthBar(2, h - 3, health, maxHealth);

	std::string maxHP = "HP: " + std::to_string(health) + " " + " Max HP: " + std::to_string(maxHealth);
	blitLine((uint8_t*) maxHP.c_str(), maxHP.size(), 30, h - 4);
	
	std::string levelString = "Level: " + std::to_string(level);
	blitLine((uint8_t*) levelString.c_str(), levelString.size(), 35, h - 3);

	levelString = std::to_string(xp) + " / " + std::to_string(xpToLevelUp);
	blitLine((uint8_t *)levelString.c_str(), levelString.size(), 45, h - 3);

	std::string statsString = " Attack: " + std::to_string(attackDamage) + " " + " Defense: " + std::to_string(defense) + " " + "Mana: " + std::to_string(mana);
	blitLine((uint8_t *)statsString.c_str(), statsString.size(), 2, h - 2);
}

void Renderer::drawEnemyStats(const std::string &name, int health, int maxHealth, int attackDamage, int defense)
{
	blitLine((uint8_t *)name.c_str(), name.size(), 2, 1);
	color(0x07, name.size(), 2, 1);

	drawHealthBar(2, 2, health, maxHealth);

	std::string maxHP = "HP: " + std::to_string(health) + " " + " Max HP: " + std::to_string(maxHealth);
	blitLine((uint8_t *)maxHP.c_str(), maxHP.size(), 30, 2);

	std::string statsString = " Attack: " + std::to_string(attackDamage) + " " + "Defense: " + std::to_string(defense);
	blitLine((uint8_t *)statsString.c_str(), statsString.size(), 2, 3);

}

void Renderer::drawBitmap(uint16_t color, const bool* map, int x, int y, int w, int h)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (map[i * w + j]) {
				int cx, cy;
				calculateConsolePosition(cx, cy, j + x, i + y);

				COORD pos = { cx, cy };
				DWORD numWritten;

				WriteConsoleOutputAttribute(hConsole, &color, 1, pos, &numWritten);
			}
		}
	}
}

void Renderer::drawRange(uint16_t c, int centerX, int centerY, int range)
{
	int cx, cy;

	for (int y = max(0, centerY - range), i = 0; y <= min(m_gridHeight - 1, centerY + range); y++, i++) {
		int d = (range - abs(y - centerY));
		for (int x = max(0, centerX - d); min(m_gridWidth - 1, x <= centerX + d); x++) {
			calculateConsolePosition(cx, cy, x, y);
			color(c, 1, cx, cy);
		}
	}
}

void Renderer::clearPlayerRegion()
{
	uint8_t line[256];

	int w, h;
	Renderer::getConsoleSizeForGrid(w, h, m_gridWidth, m_gridHeight);

	memset(line, ' ', w);

	for (int y = h - MARGIN_BOTTOM; y < h; y++) {
		blitLine(line, w, 0, y);
		color(0x07, w, 0, y);
	}
}

void Renderer::clearEnemyRegion()
{
	uint8_t line[256];

	int w, h;
	Renderer::getConsoleSizeForGrid(w, h, m_gridWidth, m_gridHeight);

	memset(line, ' ', w);

	for (int y = 0; y < MARGIN_TOP; y++) {
		blitLine(line, w, 0, y);
		color(0x07, w, 0, y);
	}
}

void Renderer::drawMessage(const std::string &msg)
{
	//size_t offset = 0;
	//size_t lineBreak = msg.find('\n', offset);
	//int y = ??;

	//blitLine(msg.c_str() + offset, lineBreak - offset, );

	int w, h;
	Renderer::getConsoleSizeForGrid(w, h, m_gridWidth, m_gridHeight);

	blitLine((uint8_t*) msg.c_str(), msg.size(), 2, h - 4);
}

void Renderer::drawAction(const std::string &msg, int row)
{
	int w, h;
	Renderer::getConsoleSizeForGrid(w, h, m_gridWidth, m_gridHeight);

	blitLine((uint8_t *)msg.c_str(), msg.size(), w - 3 - msg.length(), h - 4 + row);
}


void Renderer::drawHealthBar(int x, int y, int hp, int maxhp)
{
	uint8_t line[256];
	line[0] = '[';
	line[26] = ']';
	int i = 1;
	for (i; i <= hp * 25 / maxhp; i++) {
		line[i] = 254;
	}
	for (i; i < 26; i++) {
		line[i] = ' ';
	}
	blitLine(line, 27, x, y);
	color(0x02, 25, x + 1, y);
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
