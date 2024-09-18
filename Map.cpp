#include "Map.h"

#include "Entity.h"
#include "Golem.h"
#include "Reaper.h"
#include "Ghost.h"
#include "Character.h"
#include "Chest.h"

#include <iostream>
#include <fstream>
#include <string>


void Map::reset()
{
	clear();

	restorePlayerState();
}

void Map::clear()
{
	for (Entity* e : enemies)
	{
		delete e;
	}
	enemies.clear();

	for (Chest *c : chests)
	{
		delete c;
	}
	chests.clear();

	width = 0;
	height = 0;

	if (walls) {
		free(walls);
		walls = 0;
	}
}

void Map::restorePlayerState()
{
	if (player) {
		*player = savedPlayerState;
	}
}

bool Map::load(const char *path)
{
	std::ifstream file(path);

	if (!file) {
		return false;
	}

	std::vector<std::string> lines;
	std::string line;
	while (std::getline(file, line)) {
		lines.push_back(line);
	}

	if (!checkLines(width, height, lines)) {
		return false;
	}

	walls = reinterpret_cast<uint8_t*>(malloc(width * height));
	memset(walls, 0, width * height);

	int x = 0, y = 0;

	for (int i = 1; i < lines.size() - 1; i++)
	{
		const std::string& line = lines[i];

		if (line[0] != '#' || line[line.size() - 1] != '#') {
			std::cout << "Invalid line\n";
			return false;
		}

		x = 0;
		for (int j = 1; j < line.size() - 1; j++)
		{
			char c = line[j];

			switch (c) {
			case '@':
				if (!player) {
					player = new Character();
					player->setName(getRandomName());
				}
				player->posX = x;
				player->posY = y;
				savedPlayerState = *player;
				break;
			case 'G':
				spawnEnemy<Golem>(x, y);
				break;
			case 'S':
				spawnEnemy<Ghost>(x, y);
				break;
			case 'F':
				spawnEnemy<Reaper>(x, y);
				break;
			case 'c':
				spawnChest(x, y);
				break;
			case '#':
				addWall(x, y);
				break;
			}

			x++;
		}

		y++;
	}

	file.close();
	return true;
}

void Map::removeEnemy(Entity *e)
{
	removeWall(e->getPosX(), e->getPosY());
	enemies.erase(std::remove(enemies.begin(), enemies.end(), e));
	delete e;
}

void Map::removeChest(Chest *c)
{
	removeWall(c->getPosX(), c->getPosY());
	chests.erase(std::remove(chests.begin(), chests.end(), c));
	delete c;
}

void Map::addWall(int x, int y)
{
	walls[y * width + x] = 1;
}

void Map::removeWall(int x, int y)
{
	walls[y * width + x] = 0;
}

bool Map::isTileOccupied(int x, int y) const
{
	if (walls[y * width + x] == 1) {
		return true;
	}

	for (Entity *enemy : enemies) {
		if (enemy->getPosX() == x && enemy->getPosY() == y) {
			return true;
		}
	}

	for (Chest *chest : chests) {
		if (chest->getPosX() == x && chest->getPosY() == y) {
			return true;
		}
	}

	return false;
}

std::string Map::generateEnemiesName(int length)
{
	std::vector<std::string> syllabes = {
		   "al", "an", "gio", "ma", "ri", "lu", "ca", "vi", "li", "ta", "le", "no", "ro", "si", "ni", "fi", "do", "sa"
	};
	std::vector<std::string> ending = { "a", "o", "i", "e" };
	std::string name;

	name += (char)(rand() % 26 + 'A');

	int nameLength = 1; 

	while (nameLength < length - 1) {
		std::string syllabe = syllabes[rand() % syllabes.size()];
		if (nameLength + syllabe.size() >= length - 1) {
			break;
		}
		name += syllabe;
		nameLength += syllabe.size();
	}

	name += ending[rand() % ending.size()];

	return name;
}


Chest* Map::spawnChest(int x, int y)
{
	Chest *chest = new Chest();
	chest->posX = x;
	chest->posY = y;
	chests.push_back(chest);

	addWall(x, y);
	return chest;
}


bool Map::checkLines(int &outMapWidth, int &outMapHeight, const std::vector<std::string> &lines)
{
	if (lines.empty()) {
		return false;
	}

	int lineLength = lines[0].size();
	if (lineLength == 0) {
		return false;
	}

	for (int i = 1; i < lines.size(); i++) {
		const std::string& line = lines[i];
		if (line[0] != '#' || line[line.size() - 1] != '#' || line.size() != lineLength) {
			std::cout << "Invalid line : " << i << '\n';
			return false;
		}
	}

	outMapWidth = lines[0].size() - 2;
	outMapHeight = lines.size() - 2;

	return true;
}

bool Map::readFirstLine(int &outMapWidth, const std::string &line)
{
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] != '#') {
			std::cout << "Invalid first line\n";
			return false;
		}
	}

	outMapWidth = line.size() - 2;
	return true;
}
