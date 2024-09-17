#pragma once

#include <string>


class Renderer
{
public: // Utilities.

	static void getConsoleSizeForGrid(int& outWidth, int& outHeight, int gridWidth, int gridHeight);

public: // Drawing functions.

	void drawGrid(int width, int height);

	void drawEntity(char icon, int posX, int posY);

	void drawPlayerStats(const std::string& name, int health, int attackDamage);

	void drawEnemyStats(const std::string &name, int health, int attackDamage);

	void drawRange(int centerX, int centerY, int range);

	void drawMessage(const std::string& msg);
};
