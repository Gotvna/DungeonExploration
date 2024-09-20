#pragma once

#include "Renderer.h"

#include <vector>

class Entity;
class Chest;


class GameManager
{
public:

	static inline GameManager& getInstance();

	static const char* defaultMaps[];

	GameManager();

	static void run();

	static int getDistance(Entity *entity, int x, int y);

	void notifyEnemyAttack(Entity* attacker, Entity* target);

	void moveEnemyTo(Entity* entity, int x, int y);
	bool isEnemyMoveValid(Entity* entity, int desiredX, int desiredY);

private:

	void _run();

	void reloadMap();
	void loadNextMap();

	void redrawAll();

	void playerActionMove();
	void playerActionAttack();
	void playerActionCollect();

	void enemyAction();

	bool checkPlayerWin();
	void checkPlayerDeath();

	void updateNearbyEnemyAndChest();

	void movePlayerTo(int x, int y);

	void killEnemy(Entity* e);
	void removeChest(Chest* c);

	void waitForEnter();

	bool hasPlayerWon() const;

	bool isMoveValid(Entity *entity, int mp, int desiredX, int desiredY);
	


private:

	Renderer m_renderer;

	// Remaining movement points for the player during their turn.
	int m_playerRemainingMP;

	int m_currentMap;

	std::vector<Entity*> m_nearbyEnemies;
	std::vector<Chest*> m_nearbyChests;
};


inline GameManager &GameManager::getInstance()
{
	static GameManager instance;
	return instance;
}
