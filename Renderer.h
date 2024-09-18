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

	void drawGrid();

	void drawEntity(char icon, int posX, int posY);

	void drawColor(uint16_t color, int posX, int posY);

	void drawPlayerStats(const std::string& name, int health, int maxHealth, int attackDamage, int defense, int mana, int level, int xp, int xpToLevelUp);
	void drawEnemyStats(const std::string &name, int health, int maxHealth, int attackDamage, int defense);

	void drawRange(uint16_t color, int centerX, int centerY, int range);

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
