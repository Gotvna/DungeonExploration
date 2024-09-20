#include "Map.h"

#include "Entity.h"
#include "Game/Enemy/Golem.h"
#include "Game/Enemy/Reaper.h"
#include "Game/Enemy/Ghost.h"
#include "Game/Character/Character.h"
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
	for (Entity* e : m_enemies)
	{
		delete e;
	}
	m_enemies.clear();

	for (Chest *c : m_chests)
	{
		delete c;
	}
	m_chests.clear();

	m_width = 0;
	m_height = 0;

	if (m_walls) {
		free(m_walls);
		m_walls = 0;
	}
}

void Map::resetPlayerState()
{
	if (m_player) {
		delete m_player;
		m_player = 0;
	}
}

void Map::restorePlayerState()
{
	if (m_player) {
		*m_player = m_savedPlayerState;
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

	if (!checkLines(m_width, m_height, lines)) {
		return false;
	}

	m_walls = reinterpret_cast<uint8_t*>(malloc(m_width * m_height));
	memset(m_walls, 0, m_width * m_height);

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
				if (!m_player) {
					m_player = new Character();
					m_player->setName(getRandomName());
				}
				m_player->posX = x;
				m_player->posY = y;
				m_savedPlayerState = *m_player;
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
	m_enemies.erase(std::remove(m_enemies.begin(), m_enemies.end(), e));
	delete e;
}

void Map::removeChest(Chest *c)
{
	removeWall(c->getPosX(), c->getPosY());
	m_chests.erase(std::remove(m_chests.begin(), m_chests.end(), c));
	delete c;
}

void Map::addWall(int x, int y)
{
	m_walls[y * m_width + x] = 1;
}

void Map::removeWall(int x, int y)
{
	m_walls[y * m_width + x] = 0;
}

bool Map::isTileOccupied(int x, int y) const
{
	if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
		return true;
	}

	if (m_walls[y * m_width + x] == 1) {
		return true;
	}

	for (Entity* enemy : m_enemies) {
		if (enemy->getPosX() == x && enemy->getPosY() == y) {
			return true;
		}
	}

	for (Chest* chest : m_chests) {
		if (chest->getPosX() == x && chest->getPosY() == y) {
			return true;
		}
	}

	if (m_player && m_player->getPosX() == x && m_player->getPosY() == y) {
		return true;
	}

	return false;
}


#include <Windows.h>
void Map::findDistanceToTilesRect(uint32_t* distance, int cx, int cy, int d) const
{
	bool visited[17 * 17]; // TODO : Hardcoded, ideally this is a "maximum supported map size".
	std::vector<int> stack;
	int rx, ry, dist;

	const int row = d * 2 + 1;

	memset(visited,  0,    row * row);
	memset(distance, 0xFF, row * row * 4);

	// Center tile.
	int i = (d) * row + (d);
	distance[i] = 0;
	stack.push_back(i);

	while (!stack.empty()) {
		i = stack.front();
		stack.erase(stack.begin());

		visited[i] = true;
		dist = distance[i];

		rx = (i % row);
		ry = (i / row);

		if (rx+cx-d > 0 && rx > 0) {
			i = (ry) * row + (rx - 1);
			if (!isTileOccupied(rx+cx-d-1, ry+cy-d)) {
				if (distance[i] > dist + 1) distance[i] = dist + 1;
				if (!visited[i]) stack.push_back(i);
			}
		}
		if (ry+cy-d > 0 && ry > 0) {
			i = (ry - 1) * row + (rx);
			if (!isTileOccupied(rx+cx-d, ry+cy-d-1)) {
				if (distance[i] > dist + 1) distance[i] = dist + 1;
				if (!visited[i]) stack.push_back(i);
			}
		}
		if (rx+cx-d < m_width - 1 && rx < row - 1) {
			i = (ry) * row + (rx + 1);
			if (!isTileOccupied(rx+cx-d+1, ry+cy-d)) {
				if (distance[i] > dist + 1) distance[i] = dist + 1;
				if (!visited[i]) stack.push_back(i);
			}
		}
		if (ry+cy-d < m_height - 1 && ry < row - 1) {
			i = (ry + 1) * row + (rx);
			if (!isTileOccupied(rx+cx-d, ry+cy-d+1)) {
				if (distance[i] > dist + 1) distance[i] = dist + 1;
				if (!visited[i]) stack.push_back(i);
			}
		}

		/*SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
		i = 0;
		for (int y = 0; y < row; y++) {
			for (int x = 0; x < row; x++) {
				if (distance[i] == 0xFFFFFFFF) std::cout << "u  ";
				else std::cout << distance[i] << "  ";
				i++;
			}

			std::cout << '\n';
		}*/
	}
}

void Map::getReachableTiles(bool* outReachable, const uint32_t* distances, int d) const
{
	const int row = d * 2 + 1;

	int i = 0;
	for (int y = 0; y < row; y++) {
		for (int x = 0; x < row; x++) {
			outReachable[i] = (distances[i] <= d);
			i++;
		}
	}
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
	chest->m_posX = x;
	chest->m_posY = y;
	m_chests.push_back(chest);

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
