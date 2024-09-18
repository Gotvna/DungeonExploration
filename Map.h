#pragma once

#include "Character.h"

#include <vector>
#include <string>

class Chest;
class Entity;


class Map
{
public:

	static inline Map& getInstance();

	// Reset the entire map, including the player's stats.
	void reset();

	// Reset the contents of the map, but keep the player.
	void clear();

	void restorePlayerState();

	bool load(const char* path);

	// Removing enemies and chests from the map.
	// This also destroys them, so be sure to never access them after calling remove.
	void removeEnemy(Entity* e);
	void removeChest(Chest* c);

	bool isTileOccupied(int x, int y) const;

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
	Character savedPlayerState;
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
