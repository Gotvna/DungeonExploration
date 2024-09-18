#pragma once

#include <string>


class Renderer
{
public: // Utilities.

	static void getConsoleSizeForGrid(int& outWidth, int& outHeight, int gridWidth, int gridHeight);

	static void calculateConsolePosition(int& outX, int& outY, int gridX, int gridY);

	static const int MARGIN_TOP = 5;
	static const int MARGIN_BOTTOM = 5;

public: // States.

	void setGridSize(int width, int height);

public: // Drawing functions.

	void drawGrid(const uint8_t* walls);

	// Draw an entity. This essentially prints a character inside the grid tile at (posX, posY).
	void drawEntity(char icon, int posX, int posY);

	void drawColor(uint16_t color, int posX, int posY);

	// Draw stats. Each character category has their designated area (above and below the grid).
	void drawPlayerStats(const std::string& name, int health, int maxHealth, int attackDamage, int defense, int mana, int level, int xp, int xpToLevelUp);
	void drawEnemyStats(const std::string &name, int health, int maxHealth, int attackDamage, int defense);

	// Plots colors depending on a 2D boolean array.
	// "x" and "y" define the top-left corner position in the console.
	void drawBitmap(uint16_t color, const bool* map, int x, int y, int w, int h);

	// Draws a diamond pattern around a given center.
	void drawRange(uint16_t color, int centerX, int centerY, int range, const uint8_t* walls);

	void clearPlayerRegion();
	void clearEnemyRegion();
	void drawMessage(const std::string& msg);
	void drawAction(const std::string& msg, int row);

private:

	void drawHealthBar(int x, int y, int hp, int maxhp);


private:

	int gridWidth;
	int gridHeight;
};
