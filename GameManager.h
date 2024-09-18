#pragma once

#include "Renderer.h"

#include <vector>

class Entity;
class Chest;


class GameManager
{
public:

	static inline GameManager& getInstance();

	GameManager();

	void run();

	static int getDistance(Entity *entity, int x, int y);

	void notifyEnemyAttack(Entity* attacker, Entity* target);

private:

	void loadMap();

	void redrawAll();

	void playerActionMove();
	void playerActionAttack();
	void playerActionCollect();

	void enemyAction();

	void updateNearbyEnemyAndChest();

	void movePlayerTo(int x, int y);

	void killEnemy(Entity* e);
	void removeChest(Chest* c);

	void waitForEnter();

	bool isMoveValid(Entity *entity, int mp, int desiredX, int desiredY);


private:

	Renderer renderer;

	// Remaining movement points for the player during their turn.
	int playerRemainingMP;

	std::vector<Entity*> nearbyEnemies;
	std::vector<Chest*> nearbyChests;
};


inline GameManager &GameManager::getInstance()
{
	static GameManager instance;
	return instance;
}
