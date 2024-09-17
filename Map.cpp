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

	if (player)
	{
		delete player;
		player = 0;
	}

	width = 0;
	height = 0;
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
				{
					if (player) {
						std::cout << "Map contains more than one player spawn\n";
					}
					else {
						player = new Character();
						player->posX = x;
						player->posY = y;
					}
				}
				break;
			case 'G':
				{
					Entity* enemy = new Golem();
					enemy->posX = x;
					enemy->posY = y;
					enemies.push_back(enemy);
				}
				break;
			case 'S':
				{
					Entity* enemy = new Ghost();
					enemy->posX = x;
					enemy->posY = y;
					enemies.push_back(enemy);
				}
				break;
			case 'F':
				{
					Entity* enemy = new Reaper();
					enemy->posX = x;
					enemy->posY = y;
					enemies.push_back(enemy);
				}
				break;
			case 'c':
				{
					Chest* chest = new Chest();
					chest->posX = x;
					chest->posY = y;
					chests.push_back(chest);
				}
				break;
			}

			x++;
		}

		y++;
	}

	file.close();
	return true;
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
