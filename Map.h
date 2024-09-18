#pragma once

#include "Character.h"

#include <vector>
#include <string>

class Chest;


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

	void addWall(int x, int y);
	void removeWall(int x, int y);

	bool isTileOccupied(int x, int y) const;

	std::string generateEnemiesName(int length);
	inline const std::string& getRandomName() { return characterNames[rand() % characterNames.size()]; }

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

	inline Character* getPlayer() const { return player; }
	inline const std::vector<Chest*>& getChests() const { return chests; }
	inline const std::vector<Entity*>& getEnemies() const { return enemies; }
	inline const uint8_t* getWalls() const { return walls; }

private:

	template<class EnemyClass>
	EnemyClass *spawnEnemy(int x, int y)
	{
		EnemyClass *enemy = new EnemyClass();
		enemy->posX = x;
		enemy->posY = y;
		enemy->setName(generateEnemiesName(10));
		enemies.push_back(enemy);

		addWall(x, y);
		return enemy;
	}

	Chest *spawnChest(int x, int y);


private: // Parsing utils.

	bool checkLines(int& outMapWidth, int& outMapHeight, const std::vector<std::string>& lines);
	bool readFirstLine(int& outMapWidth, const std::string& line);


private:

	Character* player;
	Character savedPlayerState;
	std::vector<Chest*> chests;
	std::vector<Entity*> enemies;

	uint8_t* walls;

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
