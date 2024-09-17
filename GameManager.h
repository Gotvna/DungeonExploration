#pragma once

#include "Renderer.h"

class Entity;


class GameManager
{
public:

	GameManager();

	void run();

private:

	void loadMap();

	void redrawAll();

	void playerActionMove();
	void playerActionAttack();

	void enemyAction();

	int getDistance(Entity *entity, int x, int y);
	bool isMoveValid(Entity *entity, int mp, int desiredX, int desiredY);


private:

	Renderer renderer;

	// Remaining movement points for the player during their turn.
	int playerRemainingMP;
};
