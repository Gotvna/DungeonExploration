#pragma once

#include <vector>
#include <string>

class Chest;
class Entity;
class Character;


class Map
{
public:

	static inline Map& getInstance();

	void clear();

	bool load(const char* path);

	std::string generateEnemiesName(int length);
	inline std::string getRandomName() { return characterNames[rand() % characterNames.size()]; }

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

	inline Character* getPlayer() const { return player; }
	inline const std::vector<Chest*>& getChests() const { return chests; }
	inline const std::vector<Entity*>& getEnemies() const { return enemies; }


private: // Parsing utils.

	bool checkLines(int& outMapWidth, int& outMapHeight, const std::vector<std::string>& lines);
	bool readFirstLine(int& outMapWidth, const std::string& line);


private:

	Character* player;
	std::vector<Chest*> chests;
	std::vector<Entity*> enemies;

	int width;
	int height;

	std::vector<std::string> characterNames = {
	"Ezio", "Mario", "Luigi", "Dante", "Enzo",
	"Giovanni", "Riccardo", "Stefano", "Vittorio", "Salvatore"
	};
};


inline Map &Map::getInstance()
{
	static Map instance;
	return instance;
}
