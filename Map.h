#pragma once

#include <vector>
#include <string>

class Entity;
class Character;


class Map
{
public:

	static inline Map& getInstance();

	void clear();

	bool load(const char* path);


private: // Parsing utils.

	bool checkLines(int& outMapWidth, int& outMapHeight, const std::vector<std::string>& lines);
	bool readFirstLine(int& outMapWidth, const std::string& line);


private:

	std::vector<Entity*> enemies;
	Character* player;

	int width;
	int height;
};


inline Map &Map::getInstance()
{
	static Map instance;
	return instance;
}
