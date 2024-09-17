#pragma once

#include <string>


class Renderer
{
public: // Utilities.

	static void getConsoleSizeForGrid(int& outWidth, int& outHeight, int gridWidth, int gridHeight);

	static void calculateConsolePosition(int& outX, int& outY, int gridX, int gridY);

	static const int MARGIN_TOP = 3;
	static const int MARGIN_BOTTOM = 3;

public: // States.

	void setGridSize(int width, int height);

public: // Drawing functions.

	void drawGrid();

	void drawEntity(char icon, int posX, int posY);

	void drawPlayerStats(const std::string& name, int health, int attackDamage);

	void drawEnemyStats(const std::string &name, int health, int attackDamage);

	void drawRange(int centerX, int centerY, int range);

	void drawMessage(const std::string& msg);


private:

	int gridWidth;
	int gridHeight;
};
